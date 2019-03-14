#include "base_includes.h"

#ifdef WIRELESS_NRF905
#include <nRF905.h>

#define _wireless_create_packet(msg,s) wireless_create_packet(msg,s)
#define _wireless_create_packet(msg) wireless_create_packet(msg)
#define _wireless_create_empty_packet() wireless_create_empty_packet()
#define _wireless_destroy_packet(p) buffer_destroy(p)
#define _wireless_write_packet(p,msg) buffer_write(p,msg)
 
void _wireless_init()
{
  nRF905_init();
  switch(RF_FREQ)
  {
    case 915:
      nRF905_setBand(NRF905_BAND_915);
      break;
    case 868:
      nRF905_setBand(NRF905_BAND_868);
      break;
    case 433:
      nRF905_setBand(NRF905_BAND_433);
      break;
  }
  nRF905_setChannel(RF_CHANNEL);
}

void _wireless_send_packet(const wireless_packet& data)
{
  for(size_t i = 0; i < data.s; i++)
  {
    nRF905_TX(NRF905_DEFAULT_TXADDR, (uint8_t*)data.buff[i], 1, NRF905_NEXTMODE_STANDBY);
  }
}

wireless_packet _wireless_rcv_packet()
{
  wireless_packet p = _wireless_create_empty_packet();
  nRF905_RX();
  for(size_t i = 0; i < p.s; i++)
  {
    nRF905_read((uint8_t*)p.buff[i], 1);
  }
  return p;
}

byte _wireless_get_rssi()
{
  console("nRF905 library does not report the RSSI");
  return 0;
}


#endif
