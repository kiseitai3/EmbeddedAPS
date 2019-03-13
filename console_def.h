#ifdef APS_VERBOSE
#define console_init(baud) std_console_init(baud)
#define console(a) std_console(a,String(__FILE__),String(__func__),String(__LINE__))
#define console_end() std_console_end()
#else
#define console_init(baud) std_console_init(baud)
#define console(a) {}
#define console_end() std_console_end()
#endif
