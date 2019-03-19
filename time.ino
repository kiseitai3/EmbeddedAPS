#include "base_includes.h"
#ifdef CLOCK_KEEP_TIME
#include <time.h>
time_t avr_clock;
size_t prevMillis, delta;
struct tm* timeinfo;

void clock_init()
{
  avr_clock = time(NULL);
  timeinfo = gmtime(&avr_clock);
  prevMillis = 0;
  delta = 0;
  String file_path = SPIFFS_FILE_CLOCK;
  file_path = fs_sanitize_file_name(file_path);
  #ifdef CLOCK_PERMANENT_TIME
  buffer_type saved_time;
  if(fs_file_exists(file_path.c_str()))
  {
    fs_open_file(file_path.c_str(), (file_mode_t)(file_mode_t::BIN_MODE | file_mode_t::READ));
    saved_time = fs_read(SPIFFS_FILE_CLOCK_SIZE);
    fs_file_close();
    //avr_clock = (*(time_t*)(&saved_time.buff));
    avr_clock = buffer_read_t<time_t>(saved_time);
    timeinfo = gmtime(&avr_clock);
  }
  else
  {
    fs_create_file(file_path.c_str(), SPIFFS_FILE_CLOCK_SIZE);
  }  
  #endif
}

void clock_update()
{
  #ifdef CLOCK_INTERNAL_UPDATE
  size_t currentMillis = millis();
  delta +=  currentMillis - prevMillis;
  if(delta >= 1000)
  {
    delta -= 1000;
    avr_clock++;
    timeinfo = gmtime(&avr_clock);
  }
  #else
  timeinfo = gmtime(&avr_clock);
  #endif
}

void clock_sync_time(time_t& t)
{
  avr_clock = t;
}

void clock_sync_time(byte seconds, byte minutes, byte hours, byte days, byte months, size_t year)
{
  timeinfo->tm_sec = seconds;
  timeinfo->tm_min = minutes;
  timeinfo->tm_hour = hours;
  timeinfo->tm_mday = days;
  timeinfo->tm_mon = months - 1;
  timeinfo->tm_year = year - 1900;
  avr_clock = mktime(timeinfo);
}

void clock_save()
{
  buffer_type saved_time = buffer_create(SPIFFS_FILE_CLOCK_SIZE);
  String file_path = SPIFFS_FILE_CLOCK;
  file_path = fs_sanitize_file_name(file_path);
  buffer_bin_write(saved_time, (const byte*)(avr_clock), sizeof(time_t));
  #ifdef CLOCK_PERMANENT_TIME
  if(fs_file_exists(file_path.c_str()))
  {
    fs_open_file(file_path.c_str(), (file_mode_t)(file_mode_t::BIN_MODE | file_mode_t::WRITE_TRUNC));
    fs_write(saved_time);
    fs_file_close();
  }
  else
  {
    fs_create_file(file_path.c_str(), SPIFFS_FILE_CLOCK_SIZE);
    fs_open_file(file_path.c_str(), (file_mode_t)(file_mode_t::BIN_MODE | file_mode_t::WRITE_TRUNC));
    fs_write(saved_time);
    fs_file_close();
  }  
  #endif
}

size_t clock_get_us()
{
  return micros() - prevMillis * 1000;
}

size_t clock_get_ms()
{
  return prevMillis;
}

byte clock_get_s()
{
  return timeinfo->tm_sec;
}

byte clock_get_minutes()
{
  return timeinfo->tm_min;
}

byte clock_get_Hour()
{
  return timeinfo->tm_hour;
}

byte clock_get_Day()
{
  return timeinfo->tm_mday;
}

byte clock_get_Month()
{
  return timeinfo->tm_mon;
}

size_t clock_get_Year()
{
  return timeinfo->tm_year;
}

String clock_get_formatted_time()
{
  return String(asctime(timeinfo));
}

#else


#endif
