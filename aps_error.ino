#include "base_includes.h"

status_code_t err_code;

void aps_error_init()
{
  err_code = status_code_t::NONE;
}

status_code_t aps_error_get()
{
  return err_code;
}

void aps_error_set(status_code_t code)
{
  err_code = code;
}

void aps_error_print_code(const String& msg = "")
{
  console_error(msg, err_code);
}

void aps_error_clear()
{
  err_code = status_code_t::NONE;
}
