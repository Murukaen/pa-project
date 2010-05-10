################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../state_generator/state_generator.c 

OBJS += \
./state_generator/state_generator.o 

C_DEPS += \
./state_generator/state_generator.d 


# Each subdirectory must supply rules for building sources it contributes
state_generator/%.o: ../state_generator/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


