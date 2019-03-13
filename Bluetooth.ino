#include "base_includes.h"

#ifdef WIRELESS_BLUETOOTH

#define _wireless_destroy_packet buffer_destroy
#define _wireless_write_packet(p,msg) buffer_write(p,msg)

W1GDevice device;
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
