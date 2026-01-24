/*
 * i2c_port.c
 *
 *  Created on: Jan 20, 2026
 *      Author: murad
 */
#include "main.h"

extern I2C_HandleTypeDef hi2c1;



/* ================= INIT ================= */
void BSP_I2C_Init(void)
{
   MPU6050_Init(&hi2c1);
}

void BSP_I2C_Read(MPU6050_Data_t *data)
{
   MPU6050_Read(&hi2c1, data);
}

