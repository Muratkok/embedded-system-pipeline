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
TaskHandle_t imu_task_handle;
QueueHandle_t sensorQueue;

extern I2C_HandleTypeDef hi2c1;

extern void IMU_Send_NMEA(IMU_Attitude_t *attitude);

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
	Kalman_Init(&rollKalman, 0.0f);
	Kalman_Init(&pitchKalman, 0.0f);

	float dt = 0.01f; // 100 Hz sampling
	float Q = 0.001f;
	float R = 0.03f;

    TickType_t lastWake = xTaskGetTickCount();

    for (;;)
    {

        MPU6050_Read(&hi2c1, &imuRaw);

        IMU_ComputeRollPitch(&imuRaw, &attitude);
        attitude.roll  = Kalman_Update(&rollKalman, attitude.roll, imuRaw.gx, dt, Q, R);
        attitude.pitch = Kalman_Update(&pitchKalman, attitude.pitch, imuRaw.gy, dt, Q, R);
        IMU_Send_NMEA(&attitude);
    //    // Örnek: UART ile gönder
     //   printf("Roll: %.2f Pitch: %.2f\r\n",
      //         attitude.roll,
      //         attitude.pitch);

        vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(10)); // 100 Hz
    }
}

void IMU_Init(void)
{
    /* Queue create (32 elemanlık, her eleman 1 byte) */
   sensorQueue = xQueueCreate(32, sizeof(uint8_t));
   //MPU6050_Init(&hi2c1);
   //BME280_Init(&hi2c1);
    /* BSP I2C Task */
   imu_task_handle = osThreadNew(IMU_Task, NULL, &IMUTask_attributes);
}
