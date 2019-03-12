
#include "base_includes.h"

void fs_init()
{
  _fs_init();
}

bool fs_open_file(const char* file_name, file_mode_t mode)
{
  _fs_open_file( file_name, mode);
}

buffer_type fs_read(const char* file_name, size_t s)
{
  return _fs_read(file_name, s);
}

size_t fs_write(const char* file_name, const buffer_type& data, size_t off_set)
{
  return _fs_write(file_name, data, off_set);
}

bool fs_create_file(const char* file_name)
{
  return _fs_create_file(file_name);
}

bool fs_file_exists(const char* file_name)
{
  return _fs_file_exists(file_name);
}

size_t fs_file_size(const char* file_name)
{
  return _fs_file_size(file_name);
}

void fs_file_close()
{
  _fs_file_close();
}

void fs_close()
{
  _fs_close();
}
