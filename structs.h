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
  byte* pump_type = nullptr;
  byte* pump_id = nullptr;//3 bytes
  byte* command = nullptr;
  byte* length = nullptr;
  byte* params = nullptr;//64 bytes
  byte* crc = nullptr;
}pump_packet_t;

typedef struct pump_transaction_settings
{
  pump_packet_t* request = nullptr;
  pump_packet_t* response = nullptr;
  byte attempts = 3;
  byte timeout = 10;
}pump_transaction_settings;

typedef struct crc_contents
{
  void* tables[4] = {nullptr};
  size_t polynomial[4] = {0};
  size_t init_remainder[4] = {0};
  size_t final_xor[4] = {0};
  ~crc_contents()
  {
    for(byte i = 0; i < 4; i++)
    {
      void* table = tables[i];
      if(table)
      {
        delete[] table;
      }
    }
  }
}crc_contents;

#endif //STRUCTS_H_GUARD
