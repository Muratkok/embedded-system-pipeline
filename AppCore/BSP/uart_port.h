/*
 * uart_port.h
 *
 *  Created on: Jan 20, 2026
 *      Author: murad
 */

#ifndef APPCORE_BSP_UART_PORT_H_
#define APPCORE_BSP_UART_PORT_H_

#define UART_RX_DMA_BUF_SIZE 2048
#define UART_TX_DMA_BUF_SIZE 2048

void BSP_UART_Init(void);

extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;

#endif /* APPCORE_BSP_UART_PORT_H_ */
