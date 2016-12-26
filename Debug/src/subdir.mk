################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ArrangementNode.cpp \
../src/ParkingPanic.cpp \
../src/Vehicle.cpp \
../src/VehicleStartDataTxt.cpp 

OBJS += \
./src/ArrangementNode.o \
./src/ParkingPanic.o \
./src/Vehicle.o \
./src/VehicleStartDataTxt.o 

CPP_DEPS += \
./src/ArrangementNode.d \
./src/ParkingPanic.d \
./src/Vehicle.d \
./src/VehicleStartDataTxt.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


