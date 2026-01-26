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
#include "ring_buffer.h"

TaskHandle_t imu_task_handle;

extern osSemaphoreId_t uartBusySem;
const osThreadAttr_t IMUTask_attributes = {
  .name = "bsp_uart",
  .stack_size = 1024,
  .priority = (osPriority_t) osPriorityAboveNormal7,
};

extern osSemaphoreId_t uartTxSem;

void IMU_Task(void *arg)
{
    MPU6050_Data_t imuRaw;
    IMU_Attitude_t attitude;
    static bool firstStart = false;
	KalmanFilter rollKalman, pitchKalman,headingKalman;
	IMU_Kalman_Init(&rollKalman, 0.0f);
	IMU_Kalman_Init(&pitchKalman, 0.0f);
	IMU_Kalman_Init(&headingKalman, 0.0f);

	float dt = 0.01f; // 10 Hz sampling
	float Q; //  gyro noise
	float R;  //  accek noise

    TickType_t lastWake = xTaskGetTickCount();

    for (;;)
    {
    	 if(firstStart == false || osSemaphoreAcquire(uartBusySem, osWaitForever) == osOK)
    	 {
    		 firstStart = true;
			char payload[64] = {0};
			//MPU6050_Read(&hi2c1, &imuRaw);
			BSP_I2C_Read(&imuRaw);
			IMU_ComputeRollPitchHeading(&imuRaw, &attitude);
			Q = 0.003f;
			R = 0.03f;
			attitude.roll  = IMU_Kalman_Update(&rollKalman, attitude.roll, imuRaw.gx, dt, Q, R);
			attitude.pitch = IMU_Kalman_Update(&pitchKalman, attitude.pitch, imuRaw.gy, dt, Q, R);
			Q = 0.005f;
			R = 0.001f;
			attitude.heading = IMU_Kalman_Update(&headingKalman, attitude.heading, imuRaw.gz, dt, Q, R);
			sprintf(payload, "IMU,ROLL,%.2f,PITCH,%.2f,YAW,%.2f", attitude.roll, attitude.pitch,attitude.heading);
			//sprintf(payload, "HCHDG,%.2f", attitude.heading);
			//IMU_Send_NMEA(payload);
			RingBuffer_Write(&txRingBuffer,(uint8_t*)payload);
			osSemaphoreRelease(uartTxSem);
	#ifdef IWDG_ENABLE
			SystemTaskNotify(TASK_IMU);
	#endif
			vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(10)); // 10 Hz
    	 }
    }
}

void IMU_Talks_Init(void)
{
    BSP_I2C_Init();
    /* BSP I2C Task */
   imu_task_handle = osThreadNew(IMU_Task, NULL, &IMUTask_attributes);
}
