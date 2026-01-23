################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AppCore/Services/imu_fusion.c \
../AppCore/Services/iwdg_service.c \
../AppCore/Services/nmea_formatter.c \
../AppCore/Services/ring_buffer.c 

OBJS += \
./AppCore/Services/imu_fusion.o \
./AppCore/Services/iwdg_service.o \
./AppCore/Services/nmea_formatter.o \
./AppCore/Services/ring_buffer.o 

C_DEPS += \
./AppCore/Services/imu_fusion.d \
./AppCore/Services/iwdg_service.d \
./AppCore/Services/nmea_formatter.d \
./AppCore/Services/ring_buffer.d 


# Each subdirectory must supply rules for building sources it contributes
AppCore/Services/%.o AppCore/Services/%.su AppCore/Services/%.cyclo: ../AppCore/Services/%.c AppCore/Services/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/App" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/BSP" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/Drivers" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/Services" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-AppCore-2f-Services

clean-AppCore-2f-Services:
	-$(RM) ./AppCore/Services/imu_fusion.cyclo ./AppCore/Services/imu_fusion.d ./AppCore/Services/imu_fusion.o ./AppCore/Services/imu_fusion.su ./AppCore/Services/iwdg_service.cyclo ./AppCore/Services/iwdg_service.d ./AppCore/Services/iwdg_service.o ./AppCore/Services/iwdg_service.su ./AppCore/Services/nmea_formatter.cyclo ./AppCore/Services/nmea_formatter.d ./AppCore/Services/nmea_formatter.o ./AppCore/Services/nmea_formatter.su ./AppCore/Services/ring_buffer.cyclo ./AppCore/Services/ring_buffer.d ./AppCore/Services/ring_buffer.o ./AppCore/Services/ring_buffer.su

.PHONY: clean-AppCore-2f-Services

