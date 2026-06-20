################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Device_Drivers/GPIOS/Driver_gpio.c

OBJS += \
./Device_Drivers/GPIOS/Driver_gpio.o

# Each subdirectory must supply rules for building sources it contributes
Device_Drivers/GPIOS/%.o: ../Device_Drivers/GPIOS/%.c
	@echo 'Building file: $^'
	@echo 'Invoking: ARM-GCC C Compiler'
	$(CC) $(CFLAGS) -c -o $@ $^ 
	@echo 'Finished building: $^'

