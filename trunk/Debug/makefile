################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include xboard_com/subdir.mk
-include valid_moves/subdir.mk
-include update_state/subdir.mk
-include transp_table/subdir.mk
-include state_generator/subdir.mk
-include state/subdir.mk
-include san_conv/subdir.mk
-include read_from_file/subdir.mk
-include move_handler/subdir.mk
-include move_conv/subdir.mk
-include move/subdir.mk
-include main/subdir.mk
-include list/subdir.mk
-include decision/subdir.mk
-include cur_state/subdir.mk
-include command/subdir.mk
-include bitmap/subdir.mk
-include Util/subdir.mk
-include Log/subdir.mk
-include Init/subdir.mk
-include Flags/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Repository_Shit

# Tool invocations
Repository_Shit: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o"Repository_Shit" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) Repository_Shit
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
