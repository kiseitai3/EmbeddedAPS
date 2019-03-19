#ifndef STRUCTS_H_GUARD
#define STRUCTS_H_GUARD
//#include "base_includes.h"

typedef struct buffer_type
{
  size_t s = 0;
  size_t rcv_s = 0;
  size_t s_guard = 0;
  char* buff = nullptr;
}buffer_type, wireless_packet;

//Eric's packet, check out his Gnarl project at GitHub (https://github.com/ecc1/gnarl)
typedef struct pump_packet_t:wireless_packet
{
  byte pump_type;
  byte packet_type;
  byte pump_id[3];
  byte* command;
  byte length;
  byte* params[64];
  byte* crc;
}pump_packet_t;


#endif //STRUCTS_H_GUARD
