#include "base_includes.h"
#ifdef IO_SPIFFS
#include <spiffs.h>

spiffs *fs;
spiffs_file fh;

void _fs_init()
{
  
}

bool _fs_open_file(const char* file_name, file_mode_t mode)
{
  
}

buffer_type _fs_read(const char* file_name, size_t s)
{
  
}

size_t _fs_write(const char* file_name, const buffer_type& data, size_t off_set)
{
  
}

bool _fs_create_file(const char* file_name)
{
  
}

bool _fs_file_exists(const char* file_name)
{
  
}

size_t _fs_file_size(const char* file_name)
{
  
}

void _fs_file_close()
{
  
}

void _fs_close()
{
  
}

#endif
