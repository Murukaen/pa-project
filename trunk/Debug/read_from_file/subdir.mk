################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../read_from_file/read_from_file.c 

OBJS += \
./read_from_file/read_from_file.o 

C_DEPS += \
./read_from_file/read_from_file.d 


# Each subdirectory must supply rules for building sources it contributes
read_from_file/%.o: ../read_from_file/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


