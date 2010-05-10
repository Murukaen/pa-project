################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Test/test_xboard_com/test_xboard_com.c 

OBJS += \
./Test/test_xboard_com/test_xboard_com.o 

C_DEPS += \
./Test/test_xboard_com/test_xboard_com.d 


# Each subdirectory must supply rules for building sources it contributes
Test/test_xboard_com/%.o: ../Test/test_xboard_com/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


