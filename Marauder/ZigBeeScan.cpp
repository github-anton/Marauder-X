/*
 * ZigBeeScan.cpp file
 * ZigBee network scanner.
 * 
 * Author: Anton Ermakov, 2026
 */

 // Program includes
 #include "ZigBeeScan.h"
 
 // System includes
 #include <esp_ieee802154.h>


 ZigBeeScan::ZigBeeScan()
 {
  
 }

 void ZigBeeScan::start() {
    esp_ieee802154_enable();
    esp_ieee802154_set_promiscuous(true);  // Слушаем всё подряд
    esp_ieee802154_set_rx_when_idle(true); // Не выключаем приемник
}