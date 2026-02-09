/*
 * i2c_port.c
 *
 *  Created on: Jan 20, 2026
 *      Author: murad
 */
#include "main.h"
#include "imu_fusion.h"

extern I2C_HandleTypeDef hi2c1;


/* ================= INIT ================= */
void BSP_I2C_Init(void)
{
   MPU6050_Init(&hi2c1);

/*#ifdef CALIBRATION_SENSOR
static bool firstStartInit = true;
if(firstStartInit)
{
	firstStartInit = false;
	calibrationIMUSensor();
}
#endif*/
}


void BSP_I2C_Read(MPU6050_Data_t *data)
{
	HAL_StatusTypeDef ret =  MPU6050_Read(&hi2c1, data);
	if(ret != HAL_OK)
    {
		MPU6050_Init(&hi2c1);
    }
}

