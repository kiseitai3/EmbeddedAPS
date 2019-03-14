#include "base_includes.h"

#ifdef WIRELESS_RFM95_SX1272
#include <LoRaLib.h>


/*! \brief Definition of actual device. This is done purely as part of the LoRaLib interface.
 * It's a bit messy with all of the MACROs, but that should do for now
 */
#ifdef WIRELESS_RFM95
#define W1GDevice RFM95
#elif defined(WIRELESS_RFM96)
#define W1GDevice RFM96
#elif defined(WIRELESS_RFM97)
#define W1GDevice RFM97
#elif defined(WIRELESS_RFM98)
#define W1GDevice RFM98
#elif defined(WIRELESS_SX1272)
#define W1GDevice SX1272
#elif defined(WIRELESS_SX1273)
#define W1GDevice SX1273
#elif defined(WIRELESS_SX1276)
#define W1GDevice SX1276
#elif defined(WIRELESS_SX1277)
#define W1GDevice SX1277
#elif defined(WIRELESS_SX1278)
#define W1GDevice SX1278
#elif defined(WIRELESS_SX1279)
#define W1GDevice SX1279
#endif

#define _wireless_create_packet(msg,s) wireless_create_packet(msg,s)
#define _wireless_create_packet(msg) wireless_create_packet(msg)
#define _wireless_create_empty_packet() wireless_create_empty_packet()
#define _wireless_destroy_packet(p) buffer_destroy(p)
#define _wireless_write_packet(p,msg) buffer_write(p,msg)
 
W1GDevice lora_device = new LoRa(PINLAYOUT::rfm_ss, PINLAYOUT::rfm_dio0, PINLAYOUT::rfm_dio1);
int16_t state;

void _wireless_init()
{
  lora_device.beginFSK(RF_FREQ);
  #ifdef RF_MODULATION_OOK
  lora_device.changeModulation(SX127X_MODULATION_OOK);
  #endif
}

void _wireless_send_packet(const wireless_packet& data)
{
  lora_device.transmit((uint8_t*)data.buff, data.s);
}

wireless_packet _wireless_rcv_packet()
{
  wireless_packet p = _wireless_create_empty_packet();
  state = lora_device.receive((uint8_t*)p.buff, p.s);
  return p;
}

byte _wireless_get_rssi()
{
  return lora_device.getRSSI();
}

#endif
