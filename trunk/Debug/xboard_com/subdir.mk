################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xboard_com/xboard_com.c 

OBJS += \
./xboard_com/xboard_com.o 

C_DEPS += \
./xboard_com/xboard_com.d 


# Each subdirectory must supply rules for building sources it contributes
xboard_com/%.o: ../xboard_com/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


