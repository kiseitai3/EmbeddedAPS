buffer_type buffer_create(size_t s)
{
  buffer_type b;
  b.s = s;
  b.s_guard = s + 1;
  b.buff = new char[b.s_guard];
  buffer_clear_memory(b);//This step is to mitigate the security risks associated with using dirst memory
  return b;
}

void buffer_destroy(buffer_type& b)
{
  buffer_clear_memory(b);//This step is to mitigate the security risks associated with using dirst memory
  b.s = 0;
  delete[] b.buff;
  b.buff = nullptr;
}

void buffer_clear_memory(buffer_type& b)
{
  for(size_t i = 0; i < b.s_guard; i++)
  {
    b.buff[i] = '\00';
  }
}

void buffer_write(buffer_type& b, const String& data)
{
  if(b.s > data.length())
  {
    for(size_t i = 0; i < data.length(); i++)
    {
      b.buff[i] = data[i];
    }
  }
  else
  {
    for(size_t i = 0; i < b.s; i++)
    {
      b.buff[i] = data[i];
    }
  }
}

void buffer_bin_write(buffer_type& b, const byte* data, size_t s)
{
  if(b.s > s)
  {
    for(size_t i = 0; i < s; i++)
    {
      b.buff[i] = data[i];
    }
  }
  else
  {
    for(size_t i = 0; i < b.s; i++)
    {
      b.buff[i] = data[i];
    }
  }
}

byte buffer_read_byte(buffer_type& b)
{
  return b.buff[0];
}

size_t buffer_read_size_t(buffer_type& b)
{
  byte val[sizeof(size_t)] = {0};
  for(byte i = 0; i < sizeof(size_t); i++)
  {
    val[i] = b.buff[i];
  }
  return (size_t)(val);
}

String buffer_read_str(buffer_type& b)
{
  return String(b.buff);
}

template<typename T> T buffer_read_t(buffer_type& b)
{
  size_t T_size = sizeof(T);
  byte val[T_size];
  if(T_size > b.s)
  {
    return (T)(val);
  }
  for(byte i = 0; i < T_size; i++)
  {
    val[i] = b.buff[i];
  }
  return (T)(val);
}

wireless_packet wireless_create_packet(const String& msg = "")
{
  wireless_packet p = buffer_create(WIRELESS_PACKETSIZE);
  if(msg.length() > p.s)
    console("Error constructing packet! Packet exceeds max size!");
  wireless_write_packet(p, msg);
  return p;
}

wireless_packet wireless_create_packet(const char* msg, size_t s)
{
  String str;
  for(size_t i = 0; i < s; i++)
  {
    str[i] = msg[i];
  }
  return wireless_create_packet(str);
}

wireless_packet wireless_create_empty_packet()
{
  return wireless_create_packet("\0", 1);
}
