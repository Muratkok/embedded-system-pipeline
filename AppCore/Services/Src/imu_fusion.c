/*
 * imu_fusion.c
 *
 *  Created on: Jan 20, 2026
 *      Author: murad
 */
#include "imu_fusion.h"
#include "mpu6050_driver.h"
#include <math.h>

#define ACC_LSB_2G 16384.0f
#define GYRO_LSB_PER_DPS 131.0f   // ±250 dps
#define DEG_PER_RAD 57.2957795f


extern I2C_HandleTypeDef hi2c1;

void IMU_ComputeRollPitchHeading(const MPU6050_Data_t *raw,
                                IMU_Attitude_t *att)
{
    /* 1️⃣ float’a düzgün çevir */
    float ax = (float)raw->ax / ACC_LSB_2G;
    float ay = (float)raw->ay / ACC_LSB_2G;
    float az = (float)raw->az / ACC_LSB_2G;

    /* 2️⃣ norm kontrolü (tam NaN killer) */
    float acc_norm = sqrtf(ax*ax + ay*ay + az*az);
    if (acc_norm < 1e-6f)
        return;

    /* 3️⃣ normalize */
    ax /= acc_norm;
    ay /= acc_norm;
    az /= acc_norm;

    /* 4️⃣ trig hesaplar */
    att->roll  = atan2f(ay, az) * DEG_PER_RAD;

    float denom = sqrtf(ay*ay + az*az);
    if (denom < 1e-6f)
        return;

    att->pitch = atan2f(-ax, denom) * DEG_PER_RAD;

    att->heading = atan2f(ay, ax) * DEG_PER_RAD;

    /* 5️⃣ NaN guard (son emniyet) */
    if (att->roll != att->roll ||
        att->pitch != att->pitch ||
        att->heading != att->heading)
    {
        att->roll = att->pitch = att->heading = 0.0f;
    }
}




void IMU_Kalman_Init(KalmanFilter *kf, float initAngle) {
    kf->angle = initAngle;
    kf->P = 1.0f;
}

float IMU_Kalman_Update(KalmanFilter *kf, float accAngle, float gyroRate, float dt, float Q, float R) {
	//gyrorate full scale
	gyroRate /=  GYRO_LSB_PER_DPS;
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
QStruct Q = {
    .qx = 0.002f,
    .qy = 0.002f,
    .qz = 0.005f
};

RStruct R = {
    .rx = 0.03f,
    .ry = 0.03f,
    .rz = 999.0f
};
#ifdef CALIBRATION_SENSOR


static float calculate_variance(float *samples, uint16_t n)
{
    float mean = 0.0f;
    float var  = 0.0f;

    // mean
    for(uint16_t i = 0; i < n; i++)
        mean += samples[i];
    mean /= n;

    // variance
    for(uint16_t i = 0; i < n; i++)
    {
        float diff = samples[i] - mean;
        var += diff * diff;
    }

    var /= n;

    return var;
}
float accSamples[3][SAMPLE_COUNT];
float gyroSamples[3][SAMPLE_COUNT];
void calibrationIMUSensor(void)
{
    for (uint16_t i = 0; i < SAMPLE_COUNT; i++)
    {
        MPU6050_Data_t data = {0};
        MPU6050_Read(&hi2c1, &data);

        accSamples[0][i] = data.ax / ACC_LSB_2G;
        accSamples[1][i] = data.ay / ACC_LSB_2G;
        accSamples[2][i] = data.az / ACC_LSB_2G;

        gyroSamples[0][i] = data.gx / GYRO_LSB_PER_DPS;
        gyroSamples[1][i] = data.gy / GYRO_LSB_PER_DPS;
        gyroSamples[2][i] = data.gz / GYRO_LSB_PER_DPS;

        vTaskDelay(pdMS_TO_TICKS(10));
    }

    R.rx = calculate_variance(accSamples[0], SAMPLE_COUNT);
    R.ry = calculate_variance(accSamples[1], SAMPLE_COUNT);
    R.rz = calculate_variance(accSamples[2], SAMPLE_COUNT);

    Q.qx = calculate_variance(gyroSamples[0], SAMPLE_COUNT);
    Q.qy = calculate_variance(gyroSamples[1], SAMPLE_COUNT);
    Q.qz = calculate_variance(gyroSamples[2], SAMPLE_COUNT);

}


#endif
