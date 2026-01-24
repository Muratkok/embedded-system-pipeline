################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AppCore/Services/Src/imu_fusion.c \
../AppCore/Services/Src/iwdg_service.c \
../AppCore/Services/Src/nmea_formatter.c \
../AppCore/Services/Src/ring_buffer.c 

OBJS += \
./AppCore/Services/Src/imu_fusion.o \
./AppCore/Services/Src/iwdg_service.o \
./AppCore/Services/Src/nmea_formatter.o \
./AppCore/Services/Src/ring_buffer.o 

C_DEPS += \
./AppCore/Services/Src/imu_fusion.d \
./AppCore/Services/Src/iwdg_service.d \
./AppCore/Services/Src/nmea_formatter.d \
./AppCore/Services/Src/ring_buffer.d 


# Each subdirectory must supply rules for building sources it contributes
AppCore/Services/Src/%.o AppCore/Services/Src/%.su AppCore/Services/Src/%.cyclo: ../AppCore/Services/Src/%.c AppCore/Services/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/App/Inc" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/Services/Inc" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/Drivers/Inc" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/BSP/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-AppCore-2f-Services-2f-Src

clean-AppCore-2f-Services-2f-Src:
	-$(RM) ./AppCore/Services/Src/imu_fusion.cyclo ./AppCore/Services/Src/imu_fusion.d ./AppCore/Services/Src/imu_fusion.o ./AppCore/Services/Src/imu_fusion.su ./AppCore/Services/Src/iwdg_service.cyclo ./AppCore/Services/Src/iwdg_service.d ./AppCore/Services/Src/iwdg_service.o ./AppCore/Services/Src/iwdg_service.su ./AppCore/Services/Src/nmea_formatter.cyclo ./AppCore/Services/Src/nmea_formatter.d ./AppCore/Services/Src/nmea_formatter.o ./AppCore/Services/Src/nmea_formatter.su ./AppCore/Services/Src/ring_buffer.cyclo ./AppCore/Services/Src/ring_buffer.d ./AppCore/Services/Src/ring_buffer.o ./AppCore/Services/Src/ring_buffer.su

.PHONY: clean-AppCore-2f-Services-2f-Src

