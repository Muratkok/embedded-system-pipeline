################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AppCore/App/imu_talks.c \
../AppCore/App/system_talks.c 

OBJS += \
./AppCore/App/imu_talks.o \
./AppCore/App/system_talks.o 

C_DEPS += \
./AppCore/App/imu_talks.d \
./AppCore/App/system_talks.d 


# Each subdirectory must supply rules for building sources it contributes
AppCore/App/%.o AppCore/App/%.su AppCore/App/%.cyclo: ../AppCore/App/%.c AppCore/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/App" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/BSP" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/Drivers" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/Services" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-AppCore-2f-App

clean-AppCore-2f-App:
	-$(RM) ./AppCore/App/imu_talks.cyclo ./AppCore/App/imu_talks.d ./AppCore/App/imu_talks.o ./AppCore/App/imu_talks.su ./AppCore/App/system_talks.cyclo ./AppCore/App/system_talks.d ./AppCore/App/system_talks.o ./AppCore/App/system_talks.su

.PHONY: clean-AppCore-2f-App

