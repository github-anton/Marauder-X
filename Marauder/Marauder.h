/*
 * Marauder.h
 */
 #ifndef MARAUDER_H_
 #define MARAUDER_H_

#include "configs.h"
#include "Settings.h"
#include "WiFiScan.h"
#include "SDInterface.h"
#include "BatteryInterface.h"
#include "Buffer.h"
#include "LedInterface.h"
#include "GpsInterface.h"
#include "Display.h"


#ifdef HAS_BT
  extern NimBLEScan* pBLEScan ;
#endif

extern Settings *settings ;
extern WiFiScan *wifi_scan_obj;
extern Buffer *buffer_obj;
extern EvilPortal *evil_portal_obj;

#ifdef HAS_SD
  extern SDInterface sd_obj;
#endif

#ifdef HAS_BATTERY
  extern BatteryInterface battery_obj;
#endif

#ifdef HAS_NEOPIXEL_LED
  extern Adafruit_NeoPixel *strip;
  extern LedInterface *led_obj;
#endif

#ifdef HAS_GPS
  extern GpsInterface gps_obj;
#endif

#ifdef HAS_SCREEN
  extern Display display_obj;
#endif

 #endif