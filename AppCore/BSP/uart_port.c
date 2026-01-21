/*
 * uart_port.c
 *
 *  Created on: Jan 20, 2026
 *      Author: murad
 */

#include "main.h"
#include "uart_port.h"
#include "bsp_event.h"
#include "cmsis_os.h"
#include "queue.h"

/* ================= CONFIG ================= */
#define UART_TIMEOUT_MS 50

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

uint8_t uart_rx_dma_buf[UART_RX_DMA_BUF_SIZE];
uint8_t uart_tx_dma_buf[UART_TX_DMA_BUF_SIZE];
uint16_t uart_tx_dma_buf_size = 0;
QueueHandle_t uartRxQueue;
TaskHandle_t bsp_uart_rx_task_handle = NULL;
TaskHandle_t bsp_uart_tx_task_handle = NULL;
osSemaphoreId_t uartRxSem;
osSemaphoreId_t uartTxSem;
osTimerId_t uartTimer;
bool timeoutEnable;

const osThreadAttr_t BSPUARTTask_attributes = {
  .name = "bsp_uart",
  .stack_size = 1024,
  .priority = (osPriority_t) osPriorityHigh,
};


void processData(UART_HandleTypeDef *huart,uint8_t *data, size_t len)
{
    if(len == 0) return;
    HAL_UART_Transmit_DMA(huart, data, len);
}
/* ================= BSP UART TASK ================= */
uint16_t last_rx_pos = 0;
static void BSP_UART_RX_Task(void *arg)
{

    for(;;)
     {
         if(osSemaphoreAcquire(uartRxSem, osWaitForever) == osOK)
         {
        	 if(timeoutEnable)
        	 {
        		 osTimerStart(uartTimer, 50);  // timeout 50ms
        	 }
             // DMA pointer ile veri uzunluğunu hesapla
        	 if(timeoutEnable == false)
        	 {
				 size_t currentRxPos = UART_RX_DMA_BUF_SIZE - __HAL_DMA_GET_COUNTER(huart2.hdmarx);
				 if(currentRxPos != last_rx_pos)
				 {
					 if(currentRxPos > last_rx_pos)
					 {
						 //processData(&huart2,&uart_rx_dma_buf[last_rx_pos], currentRxPos - last_rx_pos);
						 memcpy(uart_tx_dma_buf,&uart_rx_dma_buf[last_rx_pos], currentRxPos - last_rx_pos);
						 uart_tx_dma_buf_size = currentRxPos - last_rx_pos;
					 }
					 else
					 {
						 // circular wrap-around
						 //processData(&huart2,&uart_rx_dma_buf[last_rx_pos], UART_RX_DMA_BUF_SIZE - last_rx_pos);
						 memcpy(uart_tx_dma_buf,&uart_rx_dma_buf[last_rx_pos], UART_RX_DMA_BUF_SIZE - last_rx_pos);
						 if(currentRxPos > 0)
							 //processData(&huart2,&uart_rx_dma_buf[0], currentRxPos);
							 memcpy(uart_tx_dma_buf,&uart_rx_dma_buf[0], currentRxPos);
						 uart_tx_dma_buf_size = UART_RX_DMA_BUF_SIZE - last_rx_pos + currentRxPos;
					 }
					 last_rx_pos = currentRxPos;
					 osSemaphoreRelease(uartTxSem); // counting semaphore
				 }
        	 }
         }
     }
}

static void BSP_UART_TX_Task(void *arg)
{

    for(;;)
     {
         if(osSemaphoreAcquire(uartTxSem, osWaitForever) == osOK)
         {
        	 processData(&huart2,uart_tx_dma_buf, uart_tx_dma_buf_size);
         }
     }
}

void UART_InitCountingSemaphore(void)
{
    const osSemaphoreAttr_t semRxAttr = { .name = "UART_RX_Sem" };
    const osSemaphoreAttr_t semTxAttr = { .name = "UART_TX_Sem" };
    uartRxSem = osSemaphoreNew(10, 0, &semRxAttr); // max count 10, initial 0
    uartTxSem = osSemaphoreNew(10, 0, &semTxAttr); // max count 10, initial 0
}
extern void uartTimeoutCallback(void *argument);
void UART_Timer_Init(void)
{
    uartTimer = osTimerNew(uartTimeoutCallback, osTimerOnce, NULL, NULL);  // tek seferlik timer

}
/* ================= INIT ================= */
void BSP_UART_Init(void)
{
    /* UART IDLE interrupt aktif et */
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);

    /* RX DMA başlat */
    HAL_UART_Receive_DMA(&huart2, uart_rx_dma_buf, UART_RX_DMA_BUF_SIZE);
    /* Queue oluştur (32 elemanlık, her eleman 1 byte) */
   // uartRxQueue = xQueueCreate(32, sizeof(uint8_t));
    UART_InitCountingSemaphore();
    // 5️⃣ Timer oluştur
    UART_Timer_Init();
    /* BSP UART Task oluştur */
    bsp_uart_rx_task_handle = osThreadNew(BSP_UART_RX_Task, NULL, &BSPUARTTask_attributes);
    bsp_uart_tx_task_handle = osThreadNew(BSP_UART_TX_Task, NULL, &BSPUARTTask_attributes);


}
