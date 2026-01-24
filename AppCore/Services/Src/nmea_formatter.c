/*
 * nmea_formatter.c
 *
 *  Created on: Jan 20, 2026
 *      Author: murad
 */
#include "main.h"
#include "imu_fusion.h"
#include "ring_buffer.h"

extern UART_HandleTypeDef huart2;
extern osSemaphoreId_t uartTxSem;
uint8_t nmea_buffer[128];

// XOR checksum
static uint8_t NMEA_Checksum(const char *s) {
    uint8_t cs = 0;
    while(*s) {
        cs ^= *s++;
    }
    return cs;
}

void IMU_Send_NMEA(char *payload)
{
    uint8_t cs = NMEA_Checksum(payload);
    sprintf((char*)nmea_buffer, "$%s*%02X\r\n", payload, cs);
    RingBuffer_Write(&txRingBuffer,nmea_buffer);
    osSemaphoreRelease(uartTxSem);
}
