/*
 * ZigBeeScan.cpp file
 * ZigBee network scanner.
 * 
 * Author: Anton Ermakov, 2026
 */

// Program includes
#include "ZigBeeScan.h"
#include "Marauder.h"
 
 // System includes
#include <esp_ieee802154.h>
#include <HardwareSerial.h>


#ifdef HAS_ZIGBEE
// Этот колбэк вызывается драйвером при успешном приеме
extern "C" void esp_ieee802154_receive_done(uint8_t *frame, esp_ieee802154_frame_info_t *frame_info) {
    // frame - это указатель на сырые данные (начиная с заголовка MAC)
    // frame[0] - первый байт длины кадра (PHR)

    // Передаем данные в твой парсер маяков
    pZigBeeScan->parse(frame, frame_info->rssi);
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


void ZigBeeScan::stop()
{
    if (this->type != ZIGBEE_SCAN_NOTHING)
    {
        Serial.printf("Stopping ZigBee tran/recv\n\r") ;

        this->type = ZIGBEE_SCAN_NOTHING ;
        esp_ieee802154_disable();
    }
}


void ZigBeeScan::loop(uint32_t currentTime)
{
    if (type & ZIGBEE_SCAN_COORDINATORS)
    {
        // Switch channel if time is out
        if(currentTime - startTime > 2000)
        {
            startTime = currentTime ;
            int RSSI = esp_ieee802154_get_recent_rssi() ;
            Serial.printf("CH%i, RSSI=%d\n\r", channel, RSSI) ;

            if (channel < ZIGBEE_LAST_CHANNEL)
            {
                selectChannel(channel + 1) ;
            }
            else
            {
                selectChannel(ZIGBEE_FIRST_CHANNEL) ;
            }

            sendBeaconRequest() ;
        }
    }
}


void ZigBeeScan::parse(uint8_t *frame, int RSSI)
{
    // Минимум: FCF(2) + Seq(1) + PANID(2) + Addr(2) = 7 байт
    if (frame[0] < 7) return; 

    Serial.printf("FRAME %d, L=%d:", RSSI, frame[0]) ;
    for (int i = 1; i < frame[0] + 1; i++)
    {
        Serial.printf(" %X", frame[i]) ;
    }
    Serial.printf("\n\r") ;
}


void ZigBeeScan::sendBeaconRequest() {
    static uint8_t seq_num = 0;
    
    // Буфер пакета: PHR (длина) + MHR (данные)
    // Первый байт [0] - это длина всех последующих байт (7 байт)
    uint8_t packet[9] = {
        0x08,          // Длина пакета (8 байт после этого байта)
        0x03, 0x08,    // FCF (Frame Control)
        seq_num++,     // Номер последовательности
        0xFF, 0xFF,    // Dest PAN ID (Broadcast)
        0xFF, 0xFF,    // Dest Address (Broadcast)
        0x07           // Command Identifier: Beacon Request
    };

    // Отправляем сырой пакет
    esp_ieee802154_transmit(packet, false);
}