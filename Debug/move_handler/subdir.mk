################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../move_handler/move_handler.c 

OBJS += \
./move_handler/move_handler.o 

C_DEPS += \
./move_handler/move_handler.d 


# Each subdirectory must supply rules for building sources it contributes
move_handler/%.o: ../move_handler/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


