#include "base_includes.h"
#ifdef IO_SPIFFS
#include <FS.h>

using namespace fs;

File fh;

void _fs_init()
{
  SPIFFS.begin();
  char formatted[] = "/formatted";
  if (_fs_file_exists(formatted))
  {
    console("SPIFFS initialized correctly!");
  }
  else
  {
    console("SPIFFS not formatted! Creating filesystem. Please wait!");
    if (SPIFFS.format())
    {
      if (_fs_create_file(formatted, 13))
        console("Formatted!");
    }
    else
    {
      console("Formatting failed! SPIFFS failed!");
    }
  }
}

bool _fs_open_file(const char* file_name, file_mode_t mode)
{
  _fs_file_close();//Close previous file
  switch (mode)
  {
    case file_mode_t::READ:
      fh = SPIFFS.open(file_name, "r");
      break;
    case file_mode_t::WRITE_TRUNC:
      fh = SPIFFS.open(file_name, "w");
      break;
    case file_mode_t::WRITE_APPEND:
      fh = SPIFFS.open(file_name, "a");
      break;
  }
  if (fh)
  {
    console("File opened!");
  }
}

buffer_type _fs_read(size_t s, size_t off)
{
  buffer_type buff = buffer_create(s);
  fh.seek(off);
  fh.readBytes(buff.buff, buff.s);
  return buff;
}

size_t _fs_write(const buffer_type& data, size_t off_set)
{
  size_t r = 0;
  fh.seek(off_set);
  r = fh.write((const uint8_t*)data.buff, data.s);
  fh.flush();
  return r;
}

bool _fs_create_file(const char* file_name, size_t s)
{
  _fs_open_file(file_name, file_mode_t::WRITE_APPEND);
  for (size_t i = 0; i < s; i++)
  {
    fh.write(0);
  }
  return _fs_file_exists && (_fs_file_size() == s);
}

bool _fs_file_exists(const char* file_name)
{
  return SPIFFS.exists(file_name);
}

size_t _fs_file_size()
{
  return fh.size();
}

String _fs_sanitize_file_name(String& file_name)
{
  if(file_name[0] != '/')
    return String("/" + file_name);
  return file_name;
}

void _fs_file_close()
{
  fh.close();
}

void _fs_close()
{
  SPIFFS.end();
}

#endif
