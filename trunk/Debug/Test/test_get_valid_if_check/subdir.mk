################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Test/test_get_valid_if_check/test_get_valid_if_check.c 

OBJS += \
./Test/test_get_valid_if_check/test_get_valid_if_check.o 

C_DEPS += \
./Test/test_get_valid_if_check/test_get_valid_if_check.d 


# Each subdirectory must supply rules for building sources it contributes
Test/test_get_valid_if_check/%.o: ../Test/test_get_valid_if_check/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


