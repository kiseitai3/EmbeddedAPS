#ifndef CONFIG_TESTS_H_GUARD
#define CONFIG_TESTS_H_GUARD
#define APS_TESTS

//#if defined(APS_TESTS) && !defined(CONFIG_TESTS_H_GUARD)
#ifdef APS_TESTS
//Filesystem
#ifdef IO_FS
#define FILESYSTEM_TEST
#endif//Filesystem









#endif//APS_TESTS
#endif //CONFIG_TESTS_H_GUARD
