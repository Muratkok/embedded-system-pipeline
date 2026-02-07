/*
 * com_talks.c
 *
 *  Created on: Jan 24, 2026
 *      Author: murad
 */
#include "main.h"
#include "uart_port.h"
#include "system_talks.h"
#include "ring_buffer.h"
#include "nmea_formatter.h"
#include "com_talks.h"

//QueueHandle_t uartRxQueue;
TaskHandle_t bsp_uart_rx_task_handle = NULL;
TaskHandle_t bsp_uart_tx_task_handle = NULL;
osSemaphoreId_t uartTxSem;
osSemaphoreId_t uartBusySem;
osTimerId_t uartTimer;
StreamBufferHandle_t uartRxStream;


bool timeoutEnable;
__attribute__((aligned(32))) uint8_t uart_rx_dma_buf[UART_RX_DMA_BUF_SIZE];
uint8_t uart_received_data[UART_RX_DMA_BUF_SIZE];
uint16_t uart_received_data_size = 0;
uint8_t uart_tx_dma_buf[UART_TX_DMA_BUF_SIZE];
uint16_t uart_tx_dma_buf_size = 0;

uart_msg_t receivedMessageQueue;
volatile bool huart2IsBusy = false;
extern void uartTimeoutCallback(void *argument);
const osThreadAttr_t BSPUARTTask_attributes = {
  .name = "bsp_uart",
  .stack_size = 1024,
  .priority = (osPriority_t) osPriorityHigh,
};

/* ================= BSP UART TASK ================= */
uint16_t last_rx_pos = 0;
static void ComTaskRx(void *argument)
{
    for(;;)
     {
#ifdef IWDG_ENABLE
        SystemTaskNotify(TASK_COMM);
#endif
        memset(uart_received_data,0,sizeof(uart_received_data));
		uart_received_data_size = xStreamBufferReceive(uartRxStream,uart_received_data,sizeof(uart_received_data),portMAX_DELAY);
		if(uart_received_data_size)
		 {
			 processData(&huart2,uart_received_data, uart_received_data_size);
		 }

     }
}

static void ComTaskTx(void *argument)
{

    for(;;)
     {
    	TickType_t lastWake = xTaskGetTickCount();
#ifdef IWDG_ENABLE
        SystemTaskNotify(TASK_COMM);
#endif
         if(osSemaphoreAcquire(uartTxSem, osWaitForever) == osOK)
         {
        	memset(uart_tx_dma_buf,0,sizeof(uart_tx_dma_buf));
        	uart_tx_dma_buf_size = UART_Send_DMA_FromRingBuffer(uart_tx_dma_buf);
        	if(uart_tx_dma_buf_size>0)
        	{
        		char *ptr = (char*)uart_tx_dma_buf;
        		uart_tx_dma_buf_size = Convert_Data_NMEA_Format(&ptr);
				processData(&huart2,(uint8_t*)ptr, uart_tx_dma_buf_size);
        	}
        	vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(10));
         }

     }
}


static void UART_InitCountingSemaphore(void)
{
    const osSemaphoreAttr_t semTxAttr = { .name = "UART_TX_Sem" };
    uartTxSem = osSemaphoreNew(10, 0, &semTxAttr); // max count 10, initial 0
    uartBusySem = osSemaphoreNew(10, 0, &semTxAttr); // max count 10, initial 0
}

static void UART_Timer_Init(void)
{
    uartTimer = osTimerNew(uartTimeoutCallback, osTimerOnce, NULL, NULL);  // tek seferlik timer

}
void Com_Talks_Init(void)
{
	BSP_UART_Init();
    UART_InitCountingSemaphore();
    // 5️⃣ Timer create
    UART_Timer_Init();
    uartRxStream = xStreamBufferCreate( UART_RX_DMA_BUF_SIZE, 1);
    /* BSP UART Tasks creat */
    bsp_uart_rx_task_handle = osThreadNew(ComTaskRx, NULL, &BSPUARTTask_attributes);
    bsp_uart_tx_task_handle = osThreadNew(ComTaskTx, NULL, &BSPUARTTask_attributes);
    RingBuffer_Init(&txRingBuffer);

}
