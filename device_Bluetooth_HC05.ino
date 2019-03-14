#include "base_includes.h"

#ifdef WIRELESS_BLUETOOTH_HC05
#include <SoftwareSerial.h>
#define _bluetooth_create_packet(msg,s) wireless_create_packet(msg,s)
#define _bluetooth_create_packet(msg) wireless_create_packet(msg)
#define _bluetooth_create_empty_packet() wireless_create_empty_packet()
#define _bluetooth_destroy_packet(p) buffer_destroy(p)
#define _bluetooth_write_packet(p,msg) buffer_write(p,msg)

// Connect the HC-05 TX to Arduino pin RX of choice. 
// Connect the HC-05 RX to Arduino pin TX of choice through a voltage divider.

SoftwareSerial bluetooth_device(PINLAYOUT::blt_tx, PINLAYOUT::blt_rx);

void _bluetooth_init()
{
  bluetooth_device.begin(WIRELESS_BLUETOOTH_BAUD);
}

void _bluetooth_send_packet(const wireless_packet& data)
{
  for(size_t i = 0; i < data.s; i++)
  {
    bluetooth_device.write(data.buff[i]);
  }
}

wireless_packet _bluetooth_rcv_packet()
{
  size_t count = 0;
  wireless_packet p = _bluetooth_create_empty_packet();
  while(bluetooth_device.available() && count < p.s)
  {
    p.buff[count] = bluetooth_device.read();
    count++;
  }
  while(count < p.s)
  {
    p.buff[count] = '\00';
    count++;
  }
  return p
}

#endif
