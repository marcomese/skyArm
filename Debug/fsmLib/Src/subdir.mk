################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fsmLib/Src/fsm.c \
../fsmLib/Src/inputFSM.c 

OBJS += \
./fsmLib/Src/fsm.o \
./fsmLib/Src/inputFSM.o 

C_DEPS += \
./fsmLib/Src/fsm.d \
./fsmLib/Src/inputFSM.d 


# Each subdirectory must supply rules for building sources it contributes
fsmLib/Src/fsm.o: C:/Users/mames/Documents/progetti_stm32/skyArm/fsmLib/Src/fsm.c fsmLib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mames/Documents/progetti_stm32/skyArm/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/core" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/sh1106" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/fsmLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/bitmaps" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fsmLib/Src/inputFSM.o: C:/Users/mames/Documents/progetti_stm32/skyArm/fsmLib/Src/inputFSM.c fsmLib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mames/Documents/progetti_stm32/skyArm/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/core" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/sh1106" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/fsmLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/bitmaps" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-fsmLib-2f-Src

clean-fsmLib-2f-Src:
	-$(RM) ./fsmLib/Src/fsm.d ./fsmLib/Src/fsm.o ./fsmLib/Src/fsm.su ./fsmLib/Src/inputFSM.d ./fsmLib/Src/inputFSM.o ./fsmLib/Src/inputFSM.su

.PHONY: clean-fsmLib-2f-Src

