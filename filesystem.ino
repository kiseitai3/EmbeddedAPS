
#include "base_includes.h"
#ifdef IO_FS
void fs_init()
{
  _fs_init();
}

bool fs_open_file(const char* file_name, file_mode_t mode)
{
  _fs_open_file( file_name, mode);
}

buffer_type fs_read(size_t s, size_t off = 0)
{
  return _fs_read(s, off);
}

size_t fs_write(const buffer_type& data, size_t off_set=0)
{
  return _fs_write(data, off_set);
}

bool fs_create_file(const char* file_name, size_t s = 0)
{
  return _fs_create_file(file_name, s);
}

bool fs_file_exists(const char* file_name)
{
  return _fs_file_exists(file_name);
}

size_t fs_file_size()
{
  return _fs_file_size();
}

String fs_sanitize_file_name(String& file_name)
{
  return _fs_sanitize_file_name(file_name);
}

void fs_file_close()
{
  _fs_file_close();
}

void fs_close()
{
  _fs_close();
}

#else
/*Stub interface if filesystem usage is disabled!*/
void fs_init()
{
}

bool fs_open_file(const char* file_name, file_mode_t mode = file_mode_t::READ)
{
  return false;
}

buffer_type fs_read(size_t s, size_t off = 0)
{
  buffer_type null_buff;
  return null_buff;
}

size_t fs_write(const buffer_type& data, size_t off_set = 0)
{
  return 0;
}

bool fs_create_file(const char* file_name, size_t s = 1)
{
  return false;
}

bool fs_file_exists(const char* file_name)
{
  return false;
}

size_t fs_file_size()
{
  return 0;
}

void fs_file_close()
{
}

String fs_sanitize_file_name(String& file_name)
{
  return String("Stub");
}

void fs_close()
{
}
#endif


#ifdef FILESYSTEM_TEST
void runFSTest()
{
  console("Running unit tests for Filesystem");
  String f = "formatted";
  buffer_type testMsg = buffer_create(13);
  buffer_write(testMsg, "Hello World!");
  fs_init();
  fs_open_file(fs_sanitize_file_name(f).c_str(), file_mode_t::WRITE_TRUNC);
  fs_write(testMsg);
  fs_file_close();
  fs_open_file(fs_sanitize_file_name(f).c_str(), file_mode_t::READ);
  console("Reading message from file!");
  console(fs_read(13).buff);
  fs_file_close();
  console("End of unit test for Filesystem!");
}

#endif
