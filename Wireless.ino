#include "base_includes.h"

#ifdef WIRELESS_1G

void wireless_init()
{
  _wireless_init();
}

void wireless_send_packet(const wireless_packet& data)
{
  _wireless_send_packet(data);
}

wireless_packet wireless_rcv_packet()
{
  return _wireless_rcv_packet();
}

byte wireless_get_rssi()
{
  return _wireless_get_rssi();
}

float wireless_get_temperature()
{
  return _wireless_get_temperature();
}

#endif


#ifdef WIRELESS_1G_TEST
void runW1GTest()
{
  console("Running unit tests for Bluetooth");
  
  console("End of unit test for Bluetooth!");
}

#endif


#ifdef WIRELESS_WIFI



#endif

#ifdef WIRELESS_WIFI_TEST
void runWiFiTest()
{
  console("Running unit tests for Bluetooth");
  
  console("End of unit test for Bluetooth!");
}

#endif


#ifdef WIRELESS_WEBSERVER



#endif

#ifdef WIRELESS_WEBSERVER_TEST
void runWiFiWebTest()
{
  console("Running unit tests for Bluetooth");
  
  console("End of unit test for Bluetooth!");
}
#endif
