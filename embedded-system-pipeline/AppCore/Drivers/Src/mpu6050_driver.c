/*
 * mpu6050_driver.c
 *
 *  Created on: Jan 20, 2026
 *      Author: murad
 */
#include "main.h"
#include "mpu6050_driver.h"
#include "FreeRTOS.h"
#include "task.h"

void MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t data;

    // Wake up
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_PWR_MGMT_1, 1, &data, 1, 100);
__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    // Accel ±2g
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_ACCEL_CFG, 1, &data, 1, 100);

    // Gyro ±250 dps
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_GYRO_CFG, 1, &data, 1, 100);
}


void MPU6050_Read(I2C_HandleTypeDef *hi2c, MPU6050_Data_t *data)
{
    uint8_t buf[14] = {0};

    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_DATA_REG, 1, buf, 14, 100);

    data->ax = (buf[0] << 8) | buf[1];
    data->ay = (buf[2] << 8) | buf[3];
    data->az = (buf[4] << 8) | buf[5];

    data->gx = (buf[8] << 8) | buf[9];
    data->gy = (buf[10] << 8) | buf[11];
    data->gz = (buf[12] << 8) | buf[13];

    data->timestamp = xTaskGetTickCount();
}
