/*
 * ring_buffer.h
 *
 *  Created on: Jan 21, 2026
 *      Author: murad
 */

#ifndef SERVICES_RING_BUFFER_H_
#define SERVICES_RING_BUFFER_H_



#define UART_BUF_SIZE 1024

#pragma pack(push,1)

typedef struct
{
    uint8_t buf[UART_BUF_SIZE];
    uint16_t head;
    uint16_t tail;
} RingBuffer;

#pragma pack(pop)

void RingBuffer_Init(RingBuffer *rb);
uint16_t RingBuffer_Available(RingBuffer *rb);
uint16_t RingBuffer_Space(RingBuffer *rb);
uint8_t RingByte_Read(RingBuffer *rb, uint8_t *data);
void RingBuffer_Write(RingBuffer *rb, uint8_t* data);
uint16_t UART_Send_DMA_FromRingBuffer(uint8_t* dmaBuf);
extern RingBuffer txRingBuffer;

#endif /* SERVICES_RING_BUFFER_H_ */
