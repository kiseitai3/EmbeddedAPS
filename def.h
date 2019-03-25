#ifndef DEF_H_GUARD
#define DEF_H_GUARD


typedef void* void_ptr;


typedef enum file_mode_t
{
  READ = 0x01, 
  WRITE_TRUNC = 0x02, 
  WRITE_APPEND = 0x04,
  BIN_MODE = 0x10,
  TEXT_MODE = 0x20 
}file_mode_t;

typedef enum status_code_t
{
  NONE = 0x00,
  /*Pump*/
  PUMP_PACKET_PARSE_ERROR = 0x01,
  PUMP_ID_MISSING = 0x02,
  PUMP_NO_RESPONSE = 0x03,
  PUMP_MODEL_MISSING = 0x04,
  PUMP_WRONG_RESPONSE = 0x05
  
}status_code_t;

#define wireless_destroy_packet(p) buffer_destroy(p)
#define wireless_write_packet(p,msg) buffer_write(p,msg)

#endif // DEF_H_GUARD
