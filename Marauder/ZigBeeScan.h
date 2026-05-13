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

#define ZIGBEE_PHY_LEN            0
#define ZIGBEE_PHY_MAC            1
#define ZIGBEE_MAC_FCF            0
#define ZIGBEE_MAC_SEQ_NUM        2
#define ZIGBEE_MAC_DEST_PAN_ID    3
#define ZIGBEE_MAC_DEST_SADDR     5
#define ZIGBEE_MAC_SRC_SADDR      7


typedef union
{
  struct
  {
    uint16_t  type: 2 ;
    uint16_t  unused0: 4 ;
    uint16_t  PAN_ID_Compression : 1 ;
    uint16_t  unused1: 3 ;
    uint16_t  dest_mode:  2;
    uint16_t  unused2:  1 ;
    uint16_t  src_mode:  2 ;
  } ;
  uint16_t  w ;
}
ZigBee_FCF_t ;


typedef struct
{
  bool selected ;
  uint8_t channel;
  int8_t RSSI;
  uint16_t PAN_ID ;
  uint16_t short_addr ;
  uint32_t addr ;
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
  static void sendBeaconRequest() ;

private:
  LinkedList<ZigBee_Coordinator_t> *pCoordinatorList = NULL ;
  uint8_t channel = ZIGBEE_LAST_CHANNEL ;
  uint32_t startTime = 0 ;
  uint32_t type = 0 ;
} ;

#endif