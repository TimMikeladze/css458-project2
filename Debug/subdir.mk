################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CampusCabV2.cpp \
../drawBuilding0.cpp \
../drawBuilding10.cpp \
../drawBuilding15.cpp \
../drawBuilding22.cpp \
../drawBuilding30.cpp \
../textureFileReader.cpp 

OBJS += \
./CampusCabV2.o \
./drawBuilding0.o \
./drawBuilding10.o \
./drawBuilding15.o \
./drawBuilding22.o \
./drawBuilding30.o \
./textureFileReader.o 

CPP_DEPS += \
./CampusCabV2.d \
./drawBuilding0.d \
./drawBuilding10.d \
./drawBuilding15.d \
./drawBuilding22.d \
./drawBuilding30.d \
./textureFileReader.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


