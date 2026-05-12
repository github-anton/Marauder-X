/*
 * ZigBeeScan.h file
 * ZigBee network scanner.
 * 
 * Author: Anton Ermakov, 2026
 */
#ifndef ZIGBEE_SCAN_H_
#define ZIGBEE_SCAN_H_

// Standard headers
#include <stdint.h>

// Library includes
#include <LinkedList.h>


#define ZIGBEE_FIRST_CHANNEL      11 
#define ZIGBEE_LAST_CHANNEL       26

#define ZIGBEE_SCAN_NOTHING       0x0
#define ZIGBEE_SCAN_COORDINATORS  0x1


typedef struct
{
  uint16_t PAN_ID ;
  uint16_t short_addr ;
  uint8_t channel;
  int8_t RSSI;
  bool selected;
}
ZigBee_Coordinator_t;

class ZigBeeScan
{
public:
  ZigBeeScan() ;
  ~ZigBeeScan() ;
  void start(uint32_t currentTime, uint32_t type) ;
  void stop() ;
  void loop(uint32_t currentTime) ;
  void parse(uint8_t *frame, int RSSI) ;
  uint8_t getChannel() ;
  void selectChannel(uint8_t channel) ;

private:
  LinkedList<ZigBee_Coordinator_t> *pCoordinatorList = NULL ;
  uint8_t channel = ZIGBEE_LAST_CHANNEL ;
  uint32_t startTime = 0 ;
  uint32_t type = 0 ;
} ;

#endif