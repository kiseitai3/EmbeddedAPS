/*This code is a modified version of Eric's medtronics code base, licensed under the MIT License!
 * You can find his medtronics repository at https://github.com/ecc1/gnarl/blob/master/lib/medtronic/
 * His GNARL Project at https://github.com/ecc1/gnarl/
 */
#include "base_includes.h"
#ifdef MEDTRONICS
//Driver here

/*Medtronics Pump commands
 * 
 */
#define MEDTRONICS_CMD_ACK    0x06
#define MEDTRONICS_CMD_NAK   0x15
#define MEDTRONICS_CMD_WAKEUP  0x5D
#define MEDTRONICS_CMD_BATTERY 0x72
#define MEDTRONICS_CMD_RESERVOIR 0x73
#define MEDTRONICS_CMD_MODEL 0x8D
#define MEDTRONICS_CMD_TEMP_BASAL  0x98

/*Packet Settings && anatomy
 * 
 */
#define MEDTRONICS_DECODED_SHORT_PACKET 11
#define MEDTRONICS_DECODED_LONG_PACKET 107
#define MEDTRONICS_PUMP_TYPE_INDEX 0
#define MEDTRONICS_PUMP_ID_INDEX 1
#define MEDTRONICS_PUMP_CMD_INDEX 4
#define MEDTRONICS_PUMP_LENGTH_INDEX 5
#define MEDTRONICS_PUMP_PARAMS_INDEX 6
#define MEDTRONICS_PUMP_PARAMS_SIZE 64
#define MEDTRONICS_PUMP_CRC_DEFAULT_INDEX 6


void medtronics_pump_initialize_packet(pump_packet_t& packet)
{
  //Let's set the pointers to the internal buffer
  packet.pump_type = (byte*)&packet.buff[MEDTRONICS_PUMP_TYPE_INDEX];
  packet.pump_id = (byte*)&packet.buff[MEDTRONICS_PUMP_ID_INDEX];
  packet.command = (byte*)&packet.buff[MEDTRONICS_PUMP_CMD_INDEX];
  packet.length = (byte*)&packet.buff[MEDTRONICS_PUMP_LENGTH_INDEX];
  packet.crc = (byte*)&packet.buff[MEDTRONICS_PUMP_CRC_DEFAULT_INDEX];
  
  if(packet.rcv_s > MEDTRONICS_DECODED_LONG_PACKET)
  {
    packet.params = (byte*)&packet.buff[MEDTRONICS_PUMP_PARAMS_INDEX];
    packet.crc = (byte*)&packet.buff[MEDTRONICS_PUMP_PARAMS_INDEX + MEDTRONICS_PUMP_PARAMS_SIZE];
  }
}

status_code_t medtronics_pump_transaction(const pump_transaction_settings& settings)
{
  
}


#endif
