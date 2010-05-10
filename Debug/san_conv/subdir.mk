################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../san_conv/san_conv.c 

OBJS += \
./san_conv/san_conv.o 

C_DEPS += \
./san_conv/san_conv.d 


# Each subdirectory must supply rules for building sources it contributes
san_conv/%.o: ../san_conv/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


