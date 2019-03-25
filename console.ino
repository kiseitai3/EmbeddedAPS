
void std_console_init(size_t baud)
{
  Serial.begin(baud);
}

void std_console(const String& msg, const String& file, const String& func, const String& line)
{
  Serial.println(file + ":" + func + ":" + line + ":" + msg); 
}

void std_console_error(const String& msg, status_code_t code, const String& file, const String& func, const String& line)
{
  Serial.println();
  Serial.print(file + ":" + func + ":" + line + ":" + msg + "<Error: " ); 
  Serial.print(code, HEX);
  Serial.println();
}

void std_console_close()
{
  Serial.end();
}
