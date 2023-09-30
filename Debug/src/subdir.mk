################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Crc.cpp \
../src/Dfa.cpp \
../src/MainProductionCycle.cpp \
../src/Observer.cpp \
../src/Platform.cpp \
../src/Production.cpp \
../src/RadiusTestServer.cpp \
../src/Rte.cpp \
../src/Task.cpp \
../src/Timer.cpp 

CPP_DEPS += \
./src/Crc.d \
./src/Dfa.d \
./src/MainProductionCycle.d \
./src/Observer.d \
./src/Platform.d \
./src/Production.d \
./src/RadiusTestServer.d \
./src/Rte.d \
./src/Task.d \
./src/Timer.d 

OBJS += \
./src/Crc.o \
./src/Dfa.o \
./src/MainProductionCycle.o \
./src/Observer.o \
./src/Platform.o \
./src/Production.o \
./src/RadiusTestServer.o \
./src/Rte.o \
./src/Task.o \
./src/Timer.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"D:\Projects\CurrentProjects\RadiusAutomatic\RadiusTestServer\RadiusTestServer\src" -I"D:\Projects\CurrentProjects\RadiusAutomatic\RadiusTestServer\RadiusTestServer\src\Modbus" -I"D:\Projects\CurrentProjects\RadiusAutomatic\RadiusTestServer\RadiusTestServer\src\Goose" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Crc.d ./src/Crc.o ./src/Dfa.d ./src/Dfa.o ./src/MainProductionCycle.d ./src/MainProductionCycle.o ./src/Observer.d ./src/Observer.o ./src/Platform.d ./src/Platform.o ./src/Production.d ./src/Production.o ./src/RadiusTestServer.d ./src/RadiusTestServer.o ./src/Rte.d ./src/Rte.o ./src/Task.d ./src/Task.o ./src/Timer.d ./src/Timer.o

.PHONY: clean-src

