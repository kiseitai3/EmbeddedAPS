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
    b.buff[data.length() + 1] = '\00';
  }
}
