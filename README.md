# Embedded System Module

The **Embedded System Module** is responsible for reading sensor data from microcontrollers (MCUs), processing it, and preparing it for further communication or integration with other systems. This module is designed to be modular, lightweight, and easy to extend with additional sensors.

## Features

- Collect data from sensors such as:
- IMU (e.g., MPU6050, BNO055)
- Process and filter raw data (e.g., using a Kalman filter)
- Format sensor data in NMEA or other serial protocols
- UART-based communication for downstream systems
- Modular structure for adding new sensors or processing steps

## Requirements

- MCU platform (STM32, HC32, or similar) (The project is on the STM32f407.ıf you use a different chip, you need to change the BSP port layer)
- Sensors:
  - IMU (mandatory)
  - MPU6050 or others (optional) (If you use a different sensor, you can add the driver sensor in the Driver/src.Also add the suitable function in the imu_talk.c)
- UART communication with DMA support
- Embedded C/C++ toolchain compatible with your MCU

## Folder Structure

AppCore/
├── App/
│   ├── Inc/
│   │   ├── com_talks.h
│   │   ├── imu_talks.h
│   │   └── system_talks.h
│   └── Src/
│       ├── com_talks.c
│       ├── imu_talks.c
│       └── system_talks.c
├── BSP/
│   ├── Inc/
│   │   ├── i2c_port.h
│   │   └── uart_port.h
│   └── Src/
│       ├── i2c_port.c
│       └── uart_port.c
├── Drivers/
│   ├── Inc/
│   │   └── mpu6050_driver.h
│   └── Src/
│       └── mpu6050_driver.c
└── Services/
    ├── Inc/
    │   ├── imu_fusion.h
    │   ├── iwdg_service.h
    │   ├── nmea_formatter.h
    │   └── ring_buffer.h
    └── Src/
        ├── imu_fusion.c
        ├── iwdg_service.c
        ├── nmea_formatter.c
        └── ring_buffer.c


        




