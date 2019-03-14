buffer_type buffer_create(size_t s)
{
  buffer_type b;
  b.s = s;
  b.buff = new char[s];
  return b;
}

void buffer_destroy(buffer_type& b)
{
  b.s = 0;
  delete[] b.buff;
  b.buff = nullptr;
}

void buffer_write(buffer_type& b, const String& data)
{
  if(b.s > data.length())
  {
    for(size_t i = 0; i < data.length(); i++)
    {
      b.buff[i] = data[i];
    }
    b.buff[data.length()] = '\00';
  }
  else
  {
    for(size_t i = 0; i < b.s; i++)
    {
      b.buff[i] = data[i];
    }
    b.buff[b.s] = '\00';
  }
}

wireless_packet wireless_create_packet(const String& msg = "")
{
  wireless_packet p = buffer_create(WIRELESS_PACKETSIZE + 1);
  if(msg.length() > WIRELESS_PACKETSIZE + 1)
    console("Error constructing packet! Packet exceeds max size!");
  wireless_write_packet(p, msg);
  p.s = WIRELESS_PACKETSIZE + 1;
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
