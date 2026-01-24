/*
 * imu_talks.c
 *
 *  Created on: Jan 20, 2026
 *      Author: murad
 */
#include "main.h"
#include "imu_fusion.h"
#include "mpu6050_driver.h"
#include "ring_buffer.h"
#include "imu_talks.h"
#include "system_talks.h"
#include "i2c_port.h"
#include "nmea_formatter.h"

TaskHandle_t imu_task_handle;

const osThreadAttr_t IMUTask_attributes = {
  .name = "bsp_uart",
  .stack_size = 1024,
  .priority = (osPriority_t) osPriorityAboveNormal7,
};

void IMU_Task(void *arg)
{
    MPU6050_Data_t imuRaw;
    IMU_Attitude_t attitude;

	KalmanFilter rollKalman, pitchKalman;
	IMU_Kalman_Init(&rollKalman, 0.0f);
	IMU_Kalman_Init(&pitchKalman, 0.0f);

	float dt = 0.01f; // 100 Hz sampling
	float Q = 0.001f;
	float R = 0.03f;

    TickType_t lastWake = xTaskGetTickCount();

    for (;;)
    {
        char payload[64] = {0};
        //MPU6050_Read(&hi2c1, &imuRaw);
        BSP_I2C_Read(&imuRaw);
        IMU_ComputeRollPitch(&imuRaw, &attitude);
        attitude.roll  = IMU_Kalman_Update(&rollKalman, attitude.roll, imuRaw.gx, dt, Q, R);
        attitude.pitch = IMU_Kalman_Update(&pitchKalman, attitude.pitch, imuRaw.gy, dt, Q, R);
        sprintf(payload, "IMU,ROLL,%.2f,PITCH,%.2f", attitude.roll, attitude.pitch);
        IMU_Send_NMEA(payload);
#ifdef IWDG_ENABLE
        SystemTaskNotify(TASK_IMU);
#endif
        vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(100)); // 10 Hz
    }
}

void IMU_Talks_Init(void)
{
    BSP_I2C_Init();
    /* BSP I2C Task */
   imu_task_handle = osThreadNew(IMU_Task, NULL, &IMUTask_attributes);
}
