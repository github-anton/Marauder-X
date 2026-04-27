## Build & Install Guide: ESP32Marauder for ESP32-C5-DevKit ##


## 1. Environment Setup

  Arduino IDE: Install version 2.x here.
  ESP32 Arduino Core: Version 3.0.0+ is required for C5 support.

    cd ~/Arduino/hardware/espressif
    git clone https://github.com/espressif/arduino-esp32.git
    cd ~/Arduino/hardware/espressif/arduino-esp32/tools
    python3 get.py


## 2. Setup required Libraries ##
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


## 3. Patch system libraries

 The binary patching script is located in Marauder-X/tools.
 Look at the script and setuip the path to libnet80211.a
 Then run it:

    python3 libnet_patcher.py

You should see:

    Patch successully applied!


## 4. Select required settings.
    Tools:
        Board Selection: ESP32C5 Dev Module.
        Partition Scheme: Use Huge APP (3MB No OTA).
        USB CDC On Boot: enabled
        Flash Mode: DIO
        CPU Frequency: 80 MHz (WiFi)
        Port: /dev/ttyACMx or /dev/ttyUSBx depend on which port you connected the board.

## Compile & upload firmware on the board (ESP32-C5-DevKit1)
    Select Tools/Upload and wait.


Best wishes,
    Anton
