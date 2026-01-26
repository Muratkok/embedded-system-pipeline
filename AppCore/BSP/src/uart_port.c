/*
 * uart_port.c
 *
 *  Created on: Jan 20, 2026
 *      Author: murad
 */

#include "main.h"

#include "com_talks.h"
/* ================= CONFIG ================= */
#define UART_TIMEOUT_MS 50

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;


void processData(UART_HandleTypeDef *huart,uint8_t *data, size_t len)
{
    if(len == 0) return;
    HAL_UART_Transmit_DMA(huart, data, len);
}

/* ================= INIT ================= */
void BSP_UART_Init(void)
{
    /* UART IDLE interrupt active */
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);

    /* RX DMA start */
    HAL_UART_Receive_DMA(&huart2, uart_rx_dma_buf, UART_RX_DMA_BUF_SIZE);



}
