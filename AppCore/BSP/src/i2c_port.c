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
   if(data->ax == 0 && data->ay == 0 && data->az == 0 && data->gx == 0 && data->gy == 0 && data->gz == 0)
   {
	   BSP_I2C_Init();
   }
}

