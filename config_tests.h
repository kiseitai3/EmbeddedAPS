#ifndef CONFIG_TESTS_H_GUARD
#define CONFIG_TESTS_H_GUARD
#define APS_TESTS

//#if defined(APS_TESTS) && !defined(CONFIG_TESTS_H_GUARD)
#ifdef APS_TESTS
//Filesystem
#ifdef IO_FS
#define FILESYSTEM_TEST
#endif//Filesystem

//Wireless comm tests
#ifdef WIRELESS_WEBSERVER
#define WIRELESS_WEBSERVER_TEST
#endif
#ifdef BLUETOOTH
#define BLUETOOTH_TEST
#endif
#ifdef WIRELESS_WIFI
#define WIRELESS_WIFI_TEST
#endif
#ifdef WIRELESS_1G
#define WIRELESS_1G_TEST
#endif








#endif//APS_TESTS
#endif //CONFIG_TESTS_H_GUARD
