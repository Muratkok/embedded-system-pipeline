/*
 * imu_fusion.h
 *
 *  Created on: Jan 21, 2026
 *      Author: murad
 */

#ifndef SERVICES_IMU_FUSION_H_
#define SERVICES_IMU_FUSION_H_


#include "mpu6050_driver.h"

typedef struct
{
    float roll;
    float pitch;
} IMU_Attitude_t;

typedef struct {
    float angle;
    float P;
} KalmanFilter;

void IMU_ComputeRollPitch(const MPU6050_Data_t *raw,IMU_Attitude_t *att);
void Kalman_Init(KalmanFilter *kf, float initAngle);
float Kalman_Update(KalmanFilter *kf, float accAngle, float gyroRate, float dt, float Q, float R);

#endif /* SERVICES_IMU_FUSION_H_ */
