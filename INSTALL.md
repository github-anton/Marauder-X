## Build & Install Guide: ESP32Marauder for ESP32-C5-DevKit ##


## 1. Setup compilded firmware with [esptool]

1.1 Download esp32_C5-DevKit-marauder.merged.bin.
1.2 Erase target device.

    esptool --chip esp32c5 --port /dev/ttyUSB0 erase_flash

1.3 Flash firmware

    esptool --port /dev/ttyACM0 write_flash 0x0 esp32_C5-DevKit-marauder.merged.bin


## 2. Compile firmware from sources and upload it to device.

## 2.1. Environment Setup

  Arduino IDE: Install version 2.x here.
  ESP32 Arduino Core: Version 3.0.0+ is required for C5 support.

    cd ~/Arduino/hardware/espressif
    git clone https://github.com/espressif/arduino-esp32.git
    cd ~/Arduino/hardware/espressif/arduino-esp32/tools
    python3 get.py


## 2.2. Setup required Libraries ##
    SoftwareSerial Conflict: Remove the default AVR SoftwareSerial from /libraries/ to avoid compilation errors.
    EspSoftwareSerial: Install the version by Dirk Kaar (optimized for ESP32).
    ghostl: Required dependency for Software Serial queues.

    All dependencies:

        ghostl
        EspSoftwareSerial
        Adafruit_BusIO,
        Adafruit_MAX1704X,
        Adafruit_NeoPixel
        Arduino-Queue.h,
        ArduinoJson (7.x)
        AsyncTCP,
        ESPAsyncWebServer
        ESP32Ping,
        LinkedList,
        MicroNMEA,
        NimBLE-Arduino


## 2.3. Patch system libraries

 The binary patching script is located in Marauder-X/tools.
 Look at the script and setuip the path to libnet80211.a
 Then run it:

    python3 libnet_patcher.py

You should see:

    Patch successully applied!


## 2.4. Select required settings.
    Tools:
        Board Selection: ESP32C5 Dev Module.
        Partition Scheme: Use Huge APP (3MB No OTA).
        USB CDC On Boot: enabled
        Flash Mode: DIO
        CPU Frequency: 80 MHz (WiFi)
        Port: /dev/ttyACMx or /dev/ttyUSBx depend on which port you connected the board.

## 2.5 Compile & upload firmware on the board (ESP32-C5-DevKit1)
    Select Tools/Upload.


Best wishes,
    Anton
