################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/croutine.c \
../Src/event_groups.c \
../Src/heap_3.c \
../Src/list.c \
../Src/port.c \
../Src/queue.c \
../Src/stream_buffer.c \
../Src/tasks.c \
../Src/timers.c 

OBJS += \
./Src/croutine.o \
./Src/event_groups.o \
./Src/heap_3.o \
./Src/list.o \
./Src/port.o \
./Src/queue.o \
./Src/stream_buffer.o \
./Src/tasks.o \
./Src/timers.o 

C_DEPS += \
./Src/croutine.d \
./Src/event_groups.d \
./Src/heap_3.d \
./Src/list.d \
./Src/port.d \
./Src/queue.d \
./Src/stream_buffer.d \
./Src/tasks.d \
./Src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/croutine.cyclo ./Src/croutine.d ./Src/croutine.o ./Src/croutine.su ./Src/event_groups.cyclo ./Src/event_groups.d ./Src/event_groups.o ./Src/event_groups.su ./Src/heap_3.cyclo ./Src/heap_3.d ./Src/heap_3.o ./Src/heap_3.su ./Src/list.cyclo ./Src/list.d ./Src/list.o ./Src/list.su ./Src/port.cyclo ./Src/port.d ./Src/port.o ./Src/port.su ./Src/queue.cyclo ./Src/queue.d ./Src/queue.o ./Src/queue.su ./Src/stream_buffer.cyclo ./Src/stream_buffer.d ./Src/stream_buffer.o ./Src/stream_buffer.su ./Src/tasks.cyclo ./Src/tasks.d ./Src/tasks.o ./Src/tasks.su ./Src/timers.cyclo ./Src/timers.d ./Src/timers.o ./Src/timers.su

.PHONY: clean-Src

