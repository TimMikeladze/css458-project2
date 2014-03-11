################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CampusCabV3.cpp \
../drawBuilding0.cpp \
../drawBuilding1.cpp \
../drawBuilding10.cpp \
../drawBuilding11.cpp \
../drawBuilding12.cpp \
../drawBuilding13.cpp \
../drawBuilding14.cpp \
../drawBuilding15.cpp \
../drawBuilding16.cpp \
../drawBuilding17.cpp \
../drawBuilding18.cpp \
../drawBuilding19.cpp \
../drawBuilding2.cpp \
../drawBuilding20.cpp \
../drawBuilding21.cpp \
../drawBuilding22.cpp \
../drawBuilding23.cpp \
../drawBuilding24.cpp \
../drawBuilding25.cpp \
../drawBuilding26.cpp \
../drawBuilding28.cpp \
../drawBuilding29.cpp \
../drawBuilding3.cpp \
../drawBuilding30.cpp \
../drawBuilding4.cpp \
../drawBuilding5.cpp \
../drawBuilding6.cpp \
../drawBuilding7.cpp \
../drawBuilding9.cpp \
../textureFileReader.cpp 

OBJS += \
./CampusCabV3.o \
./drawBuilding0.o \
./drawBuilding1.o \
./drawBuilding10.o \
./drawBuilding11.o \
./drawBuilding12.o \
./drawBuilding13.o \
./drawBuilding14.o \
./drawBuilding15.o \
./drawBuilding16.o \
./drawBuilding17.o \
./drawBuilding18.o \
./drawBuilding19.o \
./drawBuilding2.o \
./drawBuilding20.o \
./drawBuilding21.o \
./drawBuilding22.o \
./drawBuilding23.o \
./drawBuilding24.o \
./drawBuilding25.o \
./drawBuilding26.o \
./drawBuilding28.o \
./drawBuilding29.o \
./drawBuilding3.o \
./drawBuilding30.o \
./drawBuilding4.o \
./drawBuilding5.o \
./drawBuilding6.o \
./drawBuilding7.o \
./drawBuilding9.o \
./textureFileReader.o 

CPP_DEPS += \
./CampusCabV3.d \
./drawBuilding0.d \
./drawBuilding1.d \
./drawBuilding10.d \
./drawBuilding11.d \
./drawBuilding12.d \
./drawBuilding13.d \
./drawBuilding14.d \
./drawBuilding15.d \
./drawBuilding16.d \
./drawBuilding17.d \
./drawBuilding18.d \
./drawBuilding19.d \
./drawBuilding2.d \
./drawBuilding20.d \
./drawBuilding21.d \
./drawBuilding22.d \
./drawBuilding23.d \
./drawBuilding24.d \
./drawBuilding25.d \
./drawBuilding26.d \
./drawBuilding28.d \
./drawBuilding29.d \
./drawBuilding3.d \
./drawBuilding30.d \
./drawBuilding4.d \
./drawBuilding5.d \
./drawBuilding6.d \
./drawBuilding7.d \
./drawBuilding9.d \
./textureFileReader.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


