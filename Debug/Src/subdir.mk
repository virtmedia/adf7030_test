################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Adafruit_GFX.c \
../Src/adc.c \
../Src/adf7030.c \
../Src/crc.c \
../Src/glcdfont.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/iwdg.c \
../Src/main.c \
../Src/oled.c \
../Src/rtc.c \
../Src/spi.c \
../Src/ssd1306.c \
../Src/stm32f1xx_hal_msp.c \
../Src/stm32f1xx_it.c \
../Src/system_stm32f1xx.c \
../Src/test.c \
../Src/usb_device.c \
../Src/usbd_cdc_if.c \
../Src/usbd_conf.c \
../Src/usbd_desc.c 

OBJS += \
./Src/Adafruit_GFX.o \
./Src/adc.o \
./Src/adf7030.o \
./Src/crc.o \
./Src/glcdfont.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/iwdg.o \
./Src/main.o \
./Src/oled.o \
./Src/rtc.o \
./Src/spi.o \
./Src/ssd1306.o \
./Src/stm32f1xx_hal_msp.o \
./Src/stm32f1xx_it.o \
./Src/system_stm32f1xx.o \
./Src/test.o \
./Src/usb_device.o \
./Src/usbd_cdc_if.o \
./Src/usbd_conf.o \
./Src/usbd_desc.o 

C_DEPS += \
./Src/Adafruit_GFX.d \
./Src/adc.d \
./Src/adf7030.d \
./Src/crc.d \
./Src/glcdfont.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/iwdg.d \
./Src/main.d \
./Src/oled.d \
./Src/rtc.d \
./Src/spi.d \
./Src/ssd1306.d \
./Src/stm32f1xx_hal_msp.d \
./Src/stm32f1xx_it.d \
./Src/system_stm32f1xx.d \
./Src/test.d \
./Src/usb_device.d \
./Src/usbd_cdc_if.d \
./Src/usbd_conf.d \
./Src/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -std=c11 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"D:/stm32/adf7030_test_hsi/Inc" -I"D:/stm32/adf7030_test_hsi/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/stm32/adf7030_test_hsi/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"D:/stm32/adf7030_test_hsi/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"D:/stm32/adf7030_test_hsi/Drivers/CMSIS/Include" -I"D:/stm32/adf7030_test_hsi/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/stm32/adf7030_test_hsi/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


