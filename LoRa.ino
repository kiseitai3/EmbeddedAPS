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

#define _wireless_destroy_packet buffer_destroy
#define _wireless_write_packet(p,msg) buffer_write(p,msg)
 
W1GDevice device = new LoRa(PINLAYOUT::rfm_ss, PINLAYOUT::rfm_dio0, PINLAYOUT::rfm_dio1);
int16_t state;

void _wireless_init()
{
  device.beginFSK(RF_FREQ);
  device.changeModulation(SX127X_MODULATION_OOK);
}

void _wireless_send_packet(const wireless_packet& data)
{
  device.transmit((uint8_t*)data.buff, data.s);
}

wireless_packet _wireless_rcv_packet()
{
  wireless_packet p = _wireless_create_empty_packet();
  state = device.receive((uint8_t*)p.buff, p.s);
  return p;
}

wireless_packet _wireless_create_packet(const String& msg = "")
{
  wireless_packet p = buffer_create(WIRELESS_1G_PACKETSIZE + 1);
  if(msg.length() > WIRELESS_1G_PACKETSIZE + 1)
    console("Error constructing packet! Packet exceeds max size!");
  _wireless_write_packet(p, msg);
  return p;
}

wireless_packet _wireless_create_packet(const char* msg, size_t s)
{
  String str;
  for(size_t i = 0; i < s; i++)
  {
    str[i] = msg[i];
  }
  return _wireless_create_packet(str);
}

wireless_packet _wireless_create_empty_packet()
{
  return _wireless_create_packet("\0", 1);
}
#endif
