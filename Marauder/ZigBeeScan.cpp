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
#include <HardwareSerial.h>


#ifdef HAS_ZIGBEE
// Этот колбэк вызывается драйвером при успешном приеме
void esp_ieee802154_receive_done(uint8_t *frame, esp_ieee802154_frame_info_t *frame_info) {
    // frame - это указатель на сырые данные (начиная с заголовка MAC)
    // frame[0] - первый байт длины кадра (PHR)
    
    // Передаем данные в твой парсер маяков
    pZigBeeScan->parse(frame, frame_info);
}
#endif

ZigBeeScan::ZigBeeScan()
{
}


void ZigBeeScan::selectChannel(uint8_t channel)
{
    if (this->channel != channel)
    {
        esp_ieee802154_set_channel(channel) ;
        delay(1) ;
        this->channel = channel ;
    }
}

uint8_t ZigBeeScan::getChannel()
{
    return channel ;
}

/*
 * Prepare to scanning ZigBee channels
 */
void ZigBeeScan::start(uint32_t currentTime, uint32_t type)
{
    esp_ieee802154_enable();

    selectChannel(ZIGBEE_FIRST_CHANNEL) ;

    // Слушаем всё подряд
    esp_ieee802154_set_promiscuous(true);

    // Не выключаем приемник
    esp_ieee802154_set_rx_when_idle(true);

    esp_ieee802154_receive() ;

    this->type = type ;

    if(type & ZIGBEE_SCAN_COORDINATORS)
    {
        if (pCoordinatorList)
        {
            delete pCoordinatorList ;
        }
        pCoordinatorList = new LinkedList<ZigBee_Coordinator_t> ;
    }

    startTime = currentTime ;
}


void ZigBeeScan::loop(uint32_t currentTime)
{
    if (type & ZIGBEE_SCAN_COORDINATORS)
    {
        // Switch channel if time is out
        if(currentTime - startTime > 1000)
        {
            startTime = currentTime ;
            int RSSI = esp_ieee802154_get_recent_rssi();
            Serial.printf("CH%i, RSS=%d\n\r", channel, RSSI) ;

            if (channel < ZIGBEE_LAST_CHANNEL)
            {
                selectChannel(channel + 1) ;
            }
            else
            {
                selectChannel(ZIGBEE_FIRST_CHANNEL) ;
            }
        }
    }
}


void ZigBeeScan::parse(uint8_t *frame, uint8_t length)
{
    // Минимум: FCF(2) + Seq(1) + PANID(2) + Addr(2) = 7 байт
    if (length < 7) return; 

    Serial.printf("FRAME: %X %X %X\n\r", frame[0], frame[1], frame[2]) ;
}
