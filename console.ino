
void std_console_init(size_t baud)
{
  Serial.begin(baud);
}

void std_console(const String& msg, const String& file, const String& func, const String& line)
{
  Serial.println(file + ":" + func + ":" + line + ":" + msg); 
}

void std_console_close()
{
  Serial.end();
}
