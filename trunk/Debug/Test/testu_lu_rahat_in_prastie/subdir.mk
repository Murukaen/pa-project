################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Test/testu_lu_rahat_in_prastie/testu_lu_rahat_in_prastie.c 

OBJS += \
./Test/testu_lu_rahat_in_prastie/testu_lu_rahat_in_prastie.o 

C_DEPS += \
./Test/testu_lu_rahat_in_prastie/testu_lu_rahat_in_prastie.d 


# Each subdirectory must supply rules for building sources it contributes
Test/testu_lu_rahat_in_prastie/%.o: ../Test/testu_lu_rahat_in_prastie/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


