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

// XOR checksum hesaplama
uint8_t NMEA_Checksum(const char *s) {
    uint8_t cs = 0;
    while(*s) {
        cs ^= *s++;
    }
    return cs;
}

void IMU_Send_NMEA(IMU_Attitude_t *attitude)
{
    char payload[64];
    sprintf(payload, "IMU,ROLL,%.2f,PITCH,%.2f", attitude->roll, attitude->pitch);

    uint8_t cs = NMEA_Checksum(payload);

    sprintf((char*)nmea_buffer, "$%s*%02X\r\n", payload, cs);

    RingBuffer_Write(&txRingBuffer,nmea_buffer);
    osSemaphoreRelease(uartTxSem);
    //HAL_UART_Transmit_DMA(&huart2, nmea_buffer, len);
}
