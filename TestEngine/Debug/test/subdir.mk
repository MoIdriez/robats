################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/gamepad.cpp \
../test/main.cpp 

OBJS += \
./test/gamepad.o \
./test/main.o 

CPP_DEPS += \
./test/gamepad.d \
./test/main.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/midries/Projects/robats/TestEngine/external/include" -I"/home/midries/Projects/robats/Robats/include" -I"/home/midries/Projects/robats/Robats" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


