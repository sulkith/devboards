################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../UserCode/usermain.cpp 

OBJS += \
./UserCode/usermain.o 

CPP_DEPS += \
./UserCode/usermain.d 


# Each subdirectory must supply rules for building sources it contributes
UserCode/usermain.o: ../UserCode/usermain.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0plus -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32L053xx -DDEBUG -c -I"/home/sulkith/git/devboards/NUCLEO-L053R8/Software/FirstTest/FirstTest/UserCode/SSD1306-AVR" -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"UserCode/usermain.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

