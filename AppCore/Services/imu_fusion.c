/*
 * imu_fusion.c
 *
 *  Created on: Jan 20, 2026
 *      Author: murad
 */
#include "imu_fusion.h"
#include <math.h>

#define ACC_LSB_2G 16384.0f
#define DEG_PER_RAD 57.2957795f

void IMU_ComputeRollPitch(const MPU6050_Data_t *raw,
                          IMU_Attitude_t *att)
{
    float ax = raw->ax / ACC_LSB_2G;
    float ay = raw->ay / ACC_LSB_2G;
    float az = raw->az / ACC_LSB_2G;

    att->roll  = atan2f(ay, az) * DEG_PER_RAD;
    att->pitch = atan2f(-ax, sqrtf(ay*ay + az*az)) * DEG_PER_RAD;
}



void Kalman_Init(KalmanFilter *kf, float initAngle) {
    kf->angle = initAngle;
    kf->P = 1.0f;
}

float Kalman_Update(KalmanFilter *kf, float accAngle, float gyroRate, float dt, float Q, float R) {
    // 1. Predict
    kf->angle += gyroRate * dt;
    kf->P += Q;

    // 2. Compute Kalman Gain
    float K = kf->P / (kf->P + R);

    // 3. Update
    kf->angle = kf->angle + K * (accAngle - kf->angle);
    kf->P = (1 - K) * kf->P;

    return kf->angle;
}
