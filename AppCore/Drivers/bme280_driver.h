/*
 * bme280_driver.h
 *
 *  Created on: Jan 21, 2026
 *      Author: murad
 */

#ifndef DRIVERS_BME280_DRIVER_H_
#define DRIVERS_BME280_DRIVER_H_

#ifndef __BME280_DRIVER_H
#define __BME280_DRIVER_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

/* BME280 I2C address (SDO = GND) */
#define BME280_ADDR        (0x76 << 1)

/* Registers */
#define BME280_ID_REG      0xD0
#define BME280_RESET_REG   0xE0
#define BME280_CTRL_HUM    0xF2
#define BME280_STATUS      0xF3
#define BME280_CTRL_MEAS   0xF4
#define BME280_CONFIG      0xF5
#define BME280_DATA_REG    0xF7

typedef struct
{
    int32_t temperature;   // °C * 100
    uint32_t pressure;     // Pa
    uint32_t humidity;     // %RH * 1024
} BME280_Data_t;

void BME280_Init(I2C_HandleTypeDef *hi2c);
void BME280_Read(I2C_HandleTypeDef *hi2c, BME280_Data_t *data);

#endif


#endif /* DRIVERS_BME280_DRIVER_H_ */
