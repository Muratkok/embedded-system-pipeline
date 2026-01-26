/*
 * ring_buffer.c
 *
 *  Created on: Jan 20, 2026
 *      Author: murad
 */
#include "main.h"
#include "cmsis_os.h"
#include "imu_fusion.h"
#include "ring_buffer.h"
#include "semphr.h"

SemaphoreHandle_t ringTxBufWriteMutex;
SemaphoreHandle_t ringTxBufReadMutex;
RingBuffer txRingBuffer;
extern volatile bool huart2IsBusy;
void RingBuffer_Init(RingBuffer *rb) {
	 rb->head = 0;
	 rb->tail = 0;
	 memset(rb->buf, 0, UART_BUF_SIZE);
	 ringTxBufWriteMutex = xSemaphoreCreateMutex();
	 ringTxBufReadMutex = xSemaphoreCreateMutex();
}

static uint16_t RingBuffer_Available(RingBuffer *rb) {
    return (rb->head + UART_BUF_SIZE - rb->tail) % UART_BUF_SIZE;
}

static uint16_t RingBuffer_Space(RingBuffer *rb) {
    return (UART_BUF_SIZE - 1 - RingBuffer_Available(rb));
}

static uint8_t RingByte_Write(RingBuffer *rb, uint8_t data) {
    if (RingBuffer_Space(rb) == 0) return 0; // Buffer dolu
    rb->buf[rb->head] = data;
    rb->head = (rb->head + 1) % UART_BUF_SIZE;
    return 1;
}
void RingBuffer_Write(RingBuffer *rb, uint8_t* data)
{
	if(huart2IsBusy) return;
    xSemaphoreTake(ringTxBufWriteMutex, portMAX_DELAY);
	uint8_t writtenData = 0;
	while(*data)
	{
		if(RingByte_Write(rb,(*data)++))
		{
			writtenData++;
		}
		else break;
		data++;
	}
    xSemaphoreGive(ringTxBufWriteMutex);
}
uint8_t RingBuffer_Read(RingBuffer *rb, uint8_t *data) {
    if (RingBuffer_Available(rb) == 0) return 0; // Buffer boş
    *data = rb->buf[rb->tail];
    rb->tail = (rb->tail + 1) % UART_BUF_SIZE;
    return 1;
}

uint16_t UART_Send_DMA_FromRingBuffer(uint8_t* dmaBuf)
{
	uint16_t dmaBufSize = 0;
    if(HAL_UART_GetState(&huart2) == HAL_UART_STATE_BUSY_TX) return 0;
    xSemaphoreTake(ringTxBufReadMutex, portMAX_DELAY);
    if(RingBuffer_Available(&txRingBuffer) == 0) return 0;

    uint16_t i = 0;

    while(i < UART_BUF_SIZE && RingBuffer_Read(&txRingBuffer, &dmaBuf[i])) {
        i++;
    }
    dmaBufSize = i;
    xSemaphoreGive(ringTxBufReadMutex);
    return dmaBufSize;
}


