################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cur_state/cur_state.c 

OBJS += \
./cur_state/cur_state.o 

C_DEPS += \
./cur_state/cur_state.d 


# Each subdirectory must supply rules for building sources it contributes
cur_state/%.o: ../cur_state/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


