#include "base_includes.h"

#ifdef WIRELESS_BLUETOOTH

void bluetooth_init()
{
  _bluetooth_init();
}

void bluetooth_send_packet(const wireless_packet& data)
{
  _bluetooth_send_packet(data);
}

wireless_packet bluetooth_rcv_packet()
{
  return _bluetooth_rcv_packet();
}

#else

void bluetooth_init()
{
  console("Stub Bluetooth init");
}

void bluetooth_send_packet(const wireless_packet& data)
{
  console("Stub Bluetooth Send");
}

wireless_packet bluetooth_rcv_packet()
{
  return wireless_create_empty_packet();
}

#endif

#ifdef BLUETOOTH_TEST
void runBLTTest()
{
  console("Running unit tests for Bluetooth");
  
  console("End of unit test for Bluetooth!");
}

#endif
