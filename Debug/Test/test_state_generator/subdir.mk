################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Test/test_state_generator/test_state_generator.c 

OBJS += \
./Test/test_state_generator/test_state_generator.o 

C_DEPS += \
./Test/test_state_generator/test_state_generator.d 


# Each subdirectory must supply rules for building sources it contributes
Test/test_state_generator/%.o: ../Test/test_state_generator/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


