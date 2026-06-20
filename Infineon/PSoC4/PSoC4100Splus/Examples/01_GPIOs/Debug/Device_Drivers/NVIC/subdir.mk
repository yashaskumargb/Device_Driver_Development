################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Device_Drivers/NVIC/Driver_nvic.c

OBJS += \
./Device_Drivers/NVIC/Driver_nvic.o

# Each subdirectory must supply rules for building sources it contributes
Device_Drivers/NVIC/%.o: ../Device_Drivers/NVIC/%.c
	@echo 'Building file: $^'
	@echo 'Invoking: ARM-GCC C Compiler'
	$(CC) $(CFLAGS) -c -o $@ $^ 
	@echo 'Finished building: $^'

