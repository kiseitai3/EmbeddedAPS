#include "base_includes.h"

#ifdef WIRELESS_1G_OTHER
/*! \brief Definition of actual device. This is done purely as part of the RadioHead interface.
 * It's a bit messy with all of the MACROs, but that should do for now
 */
#ifdef WIRELESS_NRF905
#include <RH_NRF905.h>
#define W1GDevice RH_NRF905
#define W1GArgs PINLAYOUT::rfm_dio0,PINLAYOUT::rfm_dio1,PINLAYOUT::rfm_ss
#define LIB_HAS_SET_CHANNEL
#elif defined(WIRELESS_CC110)
#include <RH_CC110.h>
#define W1GDevice RH_CC110
#define W1GArgs PINLAYOUT::rfm_ss,PINLAYOUT::rfm_interrupt0,WIRELESS_CC110_27MHz
#define LIB_HAS_SET_FREQUENCY
#elif defined(WIRELESS_E32)
#include <RH_E32.h>
#define W1GDevice RH_E32
#define W1GArgs &Serial,PINLAYOUT::rfm_dio0,PINLAYOUT::rfm_dio1,PINLAYOUT::rfm_ss
#define LIB_HAS_SET_FREQUENCY
#elif defined(WIRELESS_MRF89)
#include <RH_MRF89.h>
#define W1GDevice RH_MRF89
#define W1GArgs PINLAYOUT::rfm_ss,PINLAYOUT::rfm_dio1,PINLAYOUT::rfm_interrupt0
#define LIB_HAS_SET_FREQUENCY
#elif defined(WIRELESS_NRF24)
#include <RH_NRF24.h>
#define W1GDevice RH_NRF24
#define W1GArgs PINLAYOUT::rfm_ss,PINLAYOUT::rfm_dio0
#define LIB_HAS_SET_CHANNEL
#elif defined(WIRELESS_NRF51)
#include <RH_NRF51.h>
#define W1GDevice RH_NRF51
#define W1GArgs 
#define LIB_HAS_SET_CHANNEL
#define LIB_HAS_TEMPERATURE
#define temperatureRead get_temperature
#elif defined(WIRELESS_RF22)
#include <RH_RF22.h>
#define W1GDevice RH_RF22
#define W1GArgs PINLAYOUT::rfm_ss,PINLAYOUT::rfm_interrupt0
#define LIB_HAS_SET_FREQUENCY
#define LIB_HAS_TEMPERATURE
#elif defined(WIRELESS_RF24)
#include <RH_RF24.h>
#define W1GDevice RH_RF24
#define W1GArgs PINLAYOUT::rfm_dio0,PINLAYOUT::rfm_ss
#define LIB_HAS_SET_FREQUENCY
#define LIB_HAS_TEMPERATURE
#define temperatureRead get_temperature
#elif defined(WIRELESS_RF69)
#include <RH_RF69.h>
#define W1GDevice RH_RF69
#define W1GArgs PINLAYOUT::rfm_ss,PINLAYOUT::rfm_interrupt0
#define LIB_HAS_SET_FREQUENCY
#define LIB_HAS_RSSI
#define LIB_HAS_TEMPERATURE
#elif defined(WIRELESS_RF69)
#include <RH_ASK.h>
#define W1GDevice RH_ASK
#define W1GArgs RF_SPEED,PINLAYOUT::rfm_rx,PINLAYOUT::rfm_tx,PINLAYOUT::rfm_ptt
#endif

#define _wireless_create_packet(msg,s) wireless_create_packet(msg,s)
#define _wireless_create_packet(msg) wireless_create_packet(msg)
#define _wireless_create_empty_packet() wireless_create_empty_packet()
#define _wireless_destroy_packet(p) buffer_destroy(p)
#define _wireless_write_packet(p,msg) buffer_write(p,msg)

W1GDevice device_radio(W1GArgs);
 
void _wireless_init()
{
  device_radio.init();
  #ifdef LIB_HAS_SET_CHANNEL
  device_radio.setChannel(RF_CHANNEL);
  #endif
  #ifdef LIB_HAS_SET_FREQUENCY
  device_radio.setFrequency(RF_FREQ);
  #endif
}

void _wireless_send_packet(const wireless_packet& data)
{
  device_radio.send((const uint8_t*)data.buff, data.s);
}

wireless_packet _wireless_rcv_packet()
{
  wireless_packet p = _wireless_create_empty_packet();
  device_radio.recv((uint8_t*)p.buff, (uint8_t*)&p.rcv_s);
  return p;
}

byte _wireless_get_rssi()
{
  #ifdef LIB_HAS_RSSI
  return device_radio.rssiRead();
  #else
  console("W1GDevice library does not report the RSSI");
  return 0;
  #endif
}

float _wireless_get_temperature()
{
  #ifdef LIB_HAS_TEMPERATURE
  return device_radio.temperatureRead();
  #else
  console("W1GDevice library does not report the temperature");
  return 0;
  #endif
}


#endif
