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
char nmea_buffer[128];

// XOR checksum
static uint8_t NMEA_Checksum(const char *s) {
    uint8_t cs = 0;
    while(*s) {
        cs ^= *s++;
    }
    return cs;
}

uint32_t Convert_Data_NMEA_Format(char **payload)
{
	uint32_t payloadSize;
    uint8_t cs = NMEA_Checksum(*payload);
    memset(nmea_buffer,0,sizeof(nmea_buffer));
    sprintf(nmea_buffer, "$%s*%02X\r\n", *payload, cs);
    *payload = nmea_buffer;
    payloadSize = strlen(nmea_buffer);
    return  payloadSize;
}
