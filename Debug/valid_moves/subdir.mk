################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../valid_moves/valid_moves.c 

OBJS += \
./valid_moves/valid_moves.o 

C_DEPS += \
./valid_moves/valid_moves.d 


# Each subdirectory must supply rules for building sources it contributes
valid_moves/%.o: ../valid_moves/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


