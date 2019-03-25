#ifdef APS_VERBOSE
#define console_init(baud) std_console_init(baud)
#define console(msg) std_console(msg,String(__FILE__),String(__func__),String(__LINE__))
#define console_error(msg,code) std_console_error(msg,code,String(__FILE__),String(__func__),String(__LINE__))
#define console_end() std_console_end()
#else
#define console_init(baud) std_console_init(baud)
#define console(msg) {}
#define console_error(msg,code) {}
#define console_end() std_console_end()
#endif
