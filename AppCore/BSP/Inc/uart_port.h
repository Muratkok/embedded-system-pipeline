/*
 * uart_port.h
 *
 *  Created on: Jan 20, 2026
 *      Author: murad
 */

#ifndef APPCORE_BSP_UART_PORT_H_
#define APPCORE_BSP_UART_PORT_H_

#define UART_RX_DMA_BUF_SIZE 1024
#define UART_TX_DMA_BUF_SIZE 2048

extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;

extern void BSP_UART_Init(void);
extern void processData(UART_HandleTypeDef *huart,uint8_t *data, size_t len);


#endif /* APPCORE_BSP_UART_PORT_H_ */
