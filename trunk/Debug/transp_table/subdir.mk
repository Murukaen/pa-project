################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../transp_table/transp_table.c 

OBJS += \
./transp_table/transp_table.o 

C_DEPS += \
./transp_table/transp_table.d 


# Each subdirectory must supply rules for building sources it contributes
transp_table/%.o: ../transp_table/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


