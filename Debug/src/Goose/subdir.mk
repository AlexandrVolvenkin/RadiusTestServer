################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Goose/Goose.cpp \
../src/Goose/GooseEthernet.cpp 

CPP_DEPS += \
./src/Goose/Goose.d \
./src/Goose/GooseEthernet.d 

OBJS += \
./src/Goose/Goose.o \
./src/Goose/GooseEthernet.o 


# Each subdirectory must supply rules for building sources it contributes
src/Goose/%.o: ../src/Goose/%.cpp src/Goose/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"D:\Projects\CurrentProjects\RadiusAutomatic\RadiusTestServer\RadiusTestServer\src" -I"D:\Projects\CurrentProjects\RadiusAutomatic\RadiusTestServer\RadiusTestServer\src\Modbus" -I"D:\Projects\CurrentProjects\RadiusAutomatic\RadiusTestServer\RadiusTestServer\src\Goose" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Goose

clean-src-2f-Goose:
	-$(RM) ./src/Goose/Goose.d ./src/Goose/Goose.o ./src/Goose/GooseEthernet.d ./src/Goose/GooseEthernet.o

.PHONY: clean-src-2f-Goose

