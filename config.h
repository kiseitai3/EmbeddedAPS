#ifndef CONFIG_H_GUARD
#define CONFIG_H_GUARD

//Platform
#define BOARD_ESP8266
//#define BOARD_ESP32

//Radio settings
#define RF_FREQ 915 //Can be 433, 868, 915
#define RF_MODULATION_OOK //Radio modulation with OOK
#define RF_CHANNEL 170
#define RF_SPEED 2000

//Pump settings
#define PUMP_PACKET_SIZE 107//Can be up to 107 bytes
#define PUMP_PAGE_SIZE 1024 //1024 or 2048 bytes


//Pump drivers
#define MEDTRONICS
//#define OMNIPOD


//Display drivers
#define LCD_HITACHI16X2
#define LCD_74HC595


//Communication drivers
#define WIRELESS_WIFI
#define WIRELESS_1G
#ifdef WIRELESS_1G
//#define WIRELESS_RFM95_SX1272 //using transceivers rfm{95 to 98} / SX12{72,73,76 to 79}
#ifdef WIRELESS_RFM95_SX1272
#define WIRELESS_RFM95 //actual transceiver module
#else
#define WIRELESS_1G_OTHER
#endif
#define WIRELESS_NRF905 //transceiver/receiver for 433/868/916
//#define WIRELESS_CC110
#ifdef WIRELES_CC110
#define WIRELESS_CC110_27MHz 0
#endif
#endif
//#define WIRELESS_BLUETOOTH
//#ifdef WIRELESS_BLUETOOTH
//#define WIRELESS_BLUETOOTH_BAUD 9600
//#define WIRELESS_BLUETOOTH_HC05//Bluetooth module
//#endif
#define WIRELESS_WEBSERVER //enable webserver with web interface

//Communications extra settings
#define WIRELESS_1G_DEST_ADDRESS
#define WIRELESS_PACKETSIZE PUMP_PACKET_SIZE

//Webserver + server back-end settings
#ifdef WIRELESS_WEBSERVER
#define WEB_BACK_SERVER_PORT 555
#endif


//Input
#define IO_BUTTONS
#define IO_FS
#define IO_SPIFFS
#define IO_CONSOLE
#define IO_SERIAL_BAUD 115200

//SPIFFS
#define SPIFFS_FILE_PUMP_PAGE "/pump_page"
#define SPIFFS_FILE_PUMP_PAGE_SIZE PUMP_PAGE_SIZE
#define SPIFFS_FILE_CLOCK "/clock"
#define SPIFFS_FILE_CLOCK_SIZE sizeof(size_t)
#define SPIFFS_FILE_WEB_INDEX "/index.html"
#define SPIFFS_FILE_WEB_INDEX_SIZE 900

//Clock/Scheduling
#define CLOCK_KEEP_TIME
#define CLOCK_PERMANENT_TIME
#define CLOCK_INTERNAL_UPDATE
#define CLOCK_SCHEDULER

//Encoding Algorithm
#define ENCODING_TOOLS
#ifdef MEDTRONICS
#define ENCODING_4B6B
#endif
#ifdef OMNIPOD
#define ENCODING_MANCHESTER
#endif

//CRC Settings
#define CRC
#define CRC_8
#define CRC_16

#if defined(CRC) || defined(CRC_FAST)
enum CRC_POLYNOMIALS
{
  MEDTRONICS_8 = 0x9B,
  MEDTRONICS_16 = 0x1021
};
#endif

//Further CRC settings depending on target device
#ifdef MEDTRONICS && (defined(CRC) || defined(CRC_FAST))
#define CRC_8_POLYNOMIAL CRC_POLYNOMIALS::MEDTRONICS_8
#define CRC_16_POLYNOMIAL CRC_POLYNOMIALS::MEDTRONICS_16
#endif

enum PINLAYOUT
{
  clk,
  mosi,
  rfm_dio0=8,
  rfm_dio1=9,
  rfm_rx=11,
  rfm_tx=12,
  rfm_ptt=10,
  rfm_ss = 4,
  rfm_interrupt0=2,
  blt_tx = 2,
  blt_rx = 3,
  miso
};


//Debugging
#define APS_VERBOSE

#endif //CONFIG_H_GUARD
