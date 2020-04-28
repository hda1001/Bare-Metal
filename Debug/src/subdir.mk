################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/60.\ SPI_Master.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/60.\ SPI_Master.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/60.\ SPI_Master.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/60.\ SPI_Master.o: ../src/60.\ SPI_Master.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"D:/Project files/STM Workspace/Driver/StdPeriph_Driver/inc" -I"D:/Project files/STM Workspace/Driver/inc" -I"D:/Project files/STM Workspace/Driver/CMSIS/device" -I"D:/Project files/STM Workspace/Driver/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"src/60. SPI_Master.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"D:/Project files/STM Workspace/Driver/StdPeriph_Driver/inc" -I"D:/Project files/STM Workspace/Driver/inc" -I"D:/Project files/STM Workspace/Driver/CMSIS/device" -I"D:/Project files/STM Workspace/Driver/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


