/*
 * mpu6050_driver.h
 *
 *  Created on: Jan 21, 2026
 *      Author: murad
 */

#ifndef DRIVERS_MPU6050_DRIVER_H_
#define DRIVERS_MPU6050_DRIVER_H_
#include "main.h"

#define MPU6050_ADDR        (0x68 << 1)
#define MPU6050_PWR_MGMT_1  0x6B
#define MPU6050_ACCEL_CFG  	0x1C
#define MPU6050_GYRO_CFG   	0x1B
#define MPU6050_DATA_REG 	0x3B

typedef struct
{
    int16_t ax;
    int16_t ay;
    int16_t az;

    int16_t gx;
    int16_t gy;
    int16_t gz;

    uint32_t timestamp;
} MPU6050_Data_t;

extern void MPU6050_Init(I2C_HandleTypeDef *hi2c);
extern HAL_StatusTypeDef  MPU6050_Read(I2C_HandleTypeDef *hi2c, MPU6050_Data_t *data);
extern void MPU6050_Reset(I2C_HandleTypeDef *hi2c);
#endif /* DRIVERS_MPU6050_DRIVER_H_ */
