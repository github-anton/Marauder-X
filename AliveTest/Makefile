# Путь к твоему скачанному ядру v3
ARDUINO_ESP32 = /home/anton/Arduino/hardware/espressif/arduino-esp32

INCLUDES = \
	-I$(ARDUINO_ESP32)/cores/esp32 \
	-I$(ARDUINO_ESP32)/variants/esp32c5 \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/dio_qspi/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/esp_system/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/esp_common/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/esp_hw_support/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/hal/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/soc/esp32c5/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/freertos/FreeRTOS-Kernel/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/freertos/config/include/freertos \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/freertos/config/riscv/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/freertos/FreeRTOS-Kernel/portable/riscv/include/freertos \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/freertos/config/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/riscv/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/soc/esp32c5/register \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/esp_rom/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/heap/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/newlib/platform_include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/esp_timer/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/esp_rom/esp32c5/include/esp32c5 \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/log/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32/include/esp_driver_gpio/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32/include/esp_driver_gptimer/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32/include/esp_event/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32/include/esp_driver_usb_serial_jtag/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32/include/lwip/lwip/src/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/lwip/port/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/lwip/port/freertos/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/lwip/port/esp32xx/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/esp_partition/include \
	-I$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/include/esp_netif/include \
	-ISources

# Твоя пропатченная libnet (путь к хидерам)
INCLUDES += -I$(ARDUINO_ESP32)/tools/sdk/esp32c5/include/esp_wifi/include

SOURCES = ../../Sources/*.c*


# Флаги для C6 (RISC-V)
CC  = riscv32-esp-elf-gcc
CXX = riscv32-esp-elf-g++
AR  = riscv32-esp-elf-ar

AUTOINCLUDE = -include $(ARDUINO_ESP32)/cores/esp32/Arduino.h 

CFLAGS = -march=rv32imc -mabi=ilp32 -Os -g -Wall \
         -DCONFIG_IDF_TARGET_ESP32C5 -DARDUINO=10810 -DESP32 -DARDUINO_ARCH_ESP32 \
         $(AUTOINCLUDE)

CPPFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -std=gnu++17 $(AUTOINCLUDE)

# Линковка — тут ESP32 требует много бинарных библиотек
LDFLAGS = -march=rv32imc -mabi=ilp32 -nostdlib \
          -Wl,--gc-sections -Wl,-static \
          -L$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/ld \
          -L$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/lib \
          -L$(ARDUINO_ESP32)/tools/esp32-arduino-libs/esp32c5/dio_qspi

LDSCRIPTS = -T esp32c5.rom.ld -T esp32c5.rom.systimer.ld \
          	-T esp32c5.rom.newlib.ld -T esp32c5.rom.heap.ld -T esp32c5.rom.api.ld \
          	-T memory.ld -T sections.ld

# Required libraries
LDLIBS = -lesp_system -lspi_flash -lbootloader_support -lesp_mm -lesp_hw_support \
		 -lesp_driver_uart -lriscv -lfreertos -llog -lhal -lsoc -lfreertos

BUILDS = Builds


SRCFILES := $(wildcard $(SOURCES))
OBJFILES := $(addprefix $(BUILDS)/,$(notdir $(patsubst %.c,%.o,$(SRCFILES))))
OBJFILES := $(patsubst %.s,%.o,$(OBJFILES))
OBJFILES := $(patsubst %.cpp,%.o,$(OBJFILES))


# Правила сборки
all: $(BUILDS)/main.bin

$(BUILDS)/main.bin: $(BUILDS)/main.elf
	# Creating BIN file with esptool.py 
	python3 $(ARDUINO_ESP32)/tools/esptool.py --chip esp32c5 elf2image -o $@ $<

$(BUILDS)/main.elf: $(OBJFILES) | $(BUILDS)
	# Link the program into ELF file
	$(CXX) $(LDFLAGS) $(LDSCRIPTS) -o $@ $^ $(LDLIBS)

$(BUILDS)/%.o: ../../Sources/%.cpp | $(BUILDS)
	# Compile .cpp source file
	$(CXX) $(INCLUDES) $(CPPFLAGS) -o $@ -c $<

$(BUILDS):
	mkdir -p $(BUILDS)

clean:
	rm -rf $(BUILDS)

# Прошивка через родной esptool
flash: all
	python3 $(ARDUINO_ESP32)/tools/esptool.py --chip esp32c5 --port /dev/ttyACM0 --baud 921600 write_flash 0x0 $(BUILDS)/main.bin
