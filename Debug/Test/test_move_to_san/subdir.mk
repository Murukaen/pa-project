################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Test/test_move_to_san/test_move_to_san.c 

OBJS += \
./Test/test_move_to_san/test_move_to_san.o 

C_DEPS += \
./Test/test_move_to_san/test_move_to_san.d 


# Each subdirectory must supply rules for building sources it contributes
Test/test_move_to_san/%.o: ../Test/test_move_to_san/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

