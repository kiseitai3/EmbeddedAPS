#ifndef CONFIG_H_GUARD
#define CONFIG_H_GUARD

//Platform
#define BOARD_ESP8266
//#define BOARD_ESP32

//Radio settings
#define RF_FREQ 915 //Can be 433, 868, 916
#define RF_MODULATION OOK //Radio modulation
#define RF_CHANNEL 170

//Pump settings
#define PUMP_PACKET_SIZE 107//Can be up to 107 bytes
#define PUMP_PAGE_SIZE 1024 //1024 or 2048 bytes


//Pump drivers
#define MEDTRONICS


//Display drivers
#define LCD_HITACHI16X2
#define LCD_74HC595


//Communication drivers
#define WIRELESS_WIFI
#define WIRELESS_1G
#define WIRELESS_RFM95_SX1272+ //using transceivers rfm{95 to 98} / SX12{72,73,76 to 79} 
#define WIRELESS_RFM95 //actual transceiver module
//#define WIRELESS_NRF905 //transceiver/receiver for 433/868/916
//#define WIRELESS_BLUETOOTH
#define WIRELESS_WEBSERVER //enable webserver with web interface

//Communications extra settings
#define WIRELESS_1G_DEST_ADDRESS
#define WIRELESS_1G_PACKETSIZE PUMP_PACKET_SIZE

//Webserver + server back-end settings
#define WEB_BACK_SERVER_PORT 555


//Input
#define IO_BUTTONS
#define IO_FS
#define IO_SPIFFS
#define IO_CONSOLE
#define IO_SERIAL_BAUD 115200

enum PINLAYOUT
{
  clk,
  mosi,
  rfm_dio0=2,
  rfm_dio1=3,
  rfm_ss = 4,
  miso
};


//Debugging
#define APS_VERBOSE

#endif //CONFIG_H_GUARD
