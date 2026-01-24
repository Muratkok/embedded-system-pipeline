################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AppCore/App/src/com_talks.c \
../AppCore/App/src/imu_talks.c \
../AppCore/App/src/system_talks.c 

OBJS += \
./AppCore/App/src/com_talks.o \
./AppCore/App/src/imu_talks.o \
./AppCore/App/src/system_talks.o 

C_DEPS += \
./AppCore/App/src/com_talks.d \
./AppCore/App/src/imu_talks.d \
./AppCore/App/src/system_talks.d 


# Each subdirectory must supply rules for building sources it contributes
AppCore/App/src/%.o AppCore/App/src/%.su AppCore/App/src/%.cyclo: ../AppCore/App/src/%.c AppCore/App/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/App/Inc" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/Services/Inc" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/Drivers/Inc" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/BSP/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-AppCore-2f-App-2f-src

clean-AppCore-2f-App-2f-src:
	-$(RM) ./AppCore/App/src/com_talks.cyclo ./AppCore/App/src/com_talks.d ./AppCore/App/src/com_talks.o ./AppCore/App/src/com_talks.su ./AppCore/App/src/imu_talks.cyclo ./AppCore/App/src/imu_talks.d ./AppCore/App/src/imu_talks.o ./AppCore/App/src/imu_talks.su ./AppCore/App/src/system_talks.cyclo ./AppCore/App/src/system_talks.d ./AppCore/App/src/system_talks.o ./AppCore/App/src/system_talks.su

.PHONY: clean-AppCore-2f-App-2f-src

