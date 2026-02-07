/*
 * com_talks.h
 *
 *  Created on: Jan 24, 2026
 *      Author: murad
 */

#ifndef APP_COM_TALKS_H_
#define APP_COM_TALKS_H_
#include "stream_buffer.h"

extern void Com_Talks_Init(void);
extern uint8_t uart_rx_dma_buf[UART_RX_DMA_BUF_SIZE];
#define UART_CHUNK_SIZE   (UART_RX_DMA_BUF_SIZE / 2)

typedef struct
{
    uint16_t len;
    uint8_t  data[UART_CHUNK_SIZE];
} uart_msg_t;

extern uart_msg_t receivedMessageQueue;
extern osMessageQueueId_t uartRxQueue;
extern StreamBufferHandle_t uartRxStream;
#endif /* APP_COM_TALKS_H_ */
