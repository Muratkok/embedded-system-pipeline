/*
 * bme280_driver.c
 *
 *  Created on: Jan 21, 2026
 *      Author: murad
 */


#include "bme280_driver.h"

/* Calibration data */
static uint16_t dig_T1;
static int16_t  dig_T2, dig_T3;
static uint16_t dig_P1;
static int16_t  dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
static uint8_t  dig_H1;
static int16_t  dig_H2;
static uint8_t  dig_H3;
static int16_t  dig_H4, dig_H5;
static int8_t   dig_H6;

static int32_t t_fine;

/* ------------------------------------------------------------ */

static void BME280_ReadCalibration(I2C_HandleTypeDef *hi2c)
{
    uint8_t buf[26];

    HAL_I2C_Mem_Read(hi2c, BME280_ADDR, 0x88, 1, buf, 26, 100);

    dig_T1 = (buf[1] << 8) | buf[0];
    dig_T2 = (buf[3] << 8) | buf[2];
    dig_T3 = (buf[5] << 8) | buf[4];

    dig_P1 = (buf[7] << 8) | buf[6];
    dig_P2 = (buf[9] << 8) | buf[8];
    dig_P3 = (buf[11] << 8) | buf[10];
    dig_P4 = (buf[13] << 8) | buf[12];
    dig_P5 = (buf[15] << 8) | buf[14];
    dig_P6 = (buf[17] << 8) | buf[16];
    dig_P7 = (buf[19] << 8) | buf[18];
    dig_P8 = (buf[21] << 8) | buf[20];
    dig_P9 = (buf[23] << 8) | buf[22];

    dig_H1 = buf[25];

    HAL_I2C_Mem_Read(hi2c, BME280_ADDR, 0xE1, 1, buf, 7, 100);

    dig_H2 = (buf[1] << 8) | buf[0];
    dig_H3 = buf[2];
    dig_H4 = (buf[3] << 4) | (buf[4] & 0x0F);
    dig_H5 = (buf[5] << 4) | (buf[4] >> 4);
    dig_H6 = (int8_t)buf[6];
}

/* ------------------------------------------------------------ */

void BME280_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t data;

    /* Soft reset */
    data = 0xB6;
    HAL_I2C_Mem_Write(hi2c, BME280_ADDR, BME280_RESET_REG, 1, &data, 1, 100);
    //HAL_Delay(100);
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    BME280_ReadCalibration(hi2c);

    /* Humidity oversampling x1 */
    data = 0x01;
    HAL_I2C_Mem_Write(hi2c, BME280_ADDR, BME280_CTRL_HUM, 1, &data, 1, 100);

    /* Temp & Pressure oversampling x1, normal mode */
    data = 0x27;
    HAL_I2C_Mem_Write(hi2c, BME280_ADDR, BME280_CTRL_MEAS, 1, &data, 1, 100);

    /* Standby 1000ms, filter off */
    data = 0xA0;
    HAL_I2C_Mem_Write(hi2c, BME280_ADDR, BME280_CONFIG, 1, &data, 1, 100);
}

/* ------------------------------------------------------------ */

void BME280_Read(I2C_HandleTypeDef *hi2c, BME280_Data_t *data)
{
    uint8_t buf[8];

    HAL_I2C_Mem_Read(hi2c, BME280_ADDR, BME280_DATA_REG, 1, buf, 8, 100);

    int32_t adc_P = (buf[0] << 12) | (buf[1] << 4) | (buf[2] >> 4);
    int32_t adc_T = (buf[3] << 12) | (buf[4] << 4) | (buf[5] >> 4);
    int32_t adc_H = (buf[6] << 8)  |  buf[7];

    /* Temperature compensation */
    int32_t var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * dig_T2) >> 11;
    int32_t var2 = (((((adc_T >> 4) - (int32_t)dig_T1) *
                      ((adc_T >> 4) - (int32_t)dig_T1)) >> 12) * dig_T3) >> 14;
    t_fine = var1 + var2;
    data->temperature = (t_fine * 5 + 128) >> 8;

    /* Pressure & humidity hesapları datasheet’e birebir uzun,
       projede istersek sadeleştiririz 😉 */
}
