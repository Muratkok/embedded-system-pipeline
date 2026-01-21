################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AppCore/BSP/i2c_port.c \
../AppCore/BSP/uart_port.c 

OBJS += \
./AppCore/BSP/i2c_port.o \
./AppCore/BSP/uart_port.o 

C_DEPS += \
./AppCore/BSP/i2c_port.d \
./AppCore/BSP/uart_port.d 


# Each subdirectory must supply rules for building sources it contributes
AppCore/BSP/%.o AppCore/BSP/%.su AppCore/BSP/%.cyclo: ../AppCore/BSP/%.c AppCore/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/App" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/BSP" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/Drivers" -I"C:/Users/murad/Desktop/CubeMx_Project/freertos_projects/embedded-system-pipeline/AppCore/Services" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-AppCore-2f-BSP

clean-AppCore-2f-BSP:
	-$(RM) ./AppCore/BSP/i2c_port.cyclo ./AppCore/BSP/i2c_port.d ./AppCore/BSP/i2c_port.o ./AppCore/BSP/i2c_port.su ./AppCore/BSP/uart_port.cyclo ./AppCore/BSP/uart_port.d ./AppCore/BSP/uart_port.o ./AppCore/BSP/uart_port.su

.PHONY: clean-AppCore-2f-BSP

