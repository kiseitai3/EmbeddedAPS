#include "base_includes.h"
#ifdef ENCODING_4B6B
/*Modified version of 4b6b encoding functions written by Eric.
 * Visit his GNARL repository for more details!
 * https://github.com/ecc1/gnarl/blob/master/lib/medtronic/
 */
 /*4B/6B encoding take groups of 4bit streams and yield a 6bit results. The problem is 
  * the fact that 4b = 16 possibilities (from 0 to 15, index of 16 byte table array), but
  * 6B implies 64 total possibilities. Of these possibilities, we only use 16 that are 
  * seemingly scattered in a 64 possibility matrix. Turns out, the 16 byte table contents 
  * are the indices of the 64 byte table and vice-versa. Thus, we only need the 16 byte
  * table, so long our search function yields less than 64 bytes. This way, we save up on
  * precious ram and rom space. We should also get a slight absolute performance improvement,
  * because 16 bytes are a lot easier to keep in cache lines if the target architecture
  * possesses this feature.
  */
//Macros for accessing the two halves of an input byte
#define HI(n, x)  ((x) >> (8 - (n)))
#define LO(n, x)  ((x) & ((1 << (n)) - 1))
//API defines
#define _encoding_encode(source) encoding_encode_4b6b(source)
#define _encoding_decode(source) encoding_decode_4b6b(source)

//Encode table
static const byte table_4b6b[16] = {
  0x15, 0x31, 0x32, 0x23,
  0x34, 0x25, 0x26, 0x16,
  0x1A, 0x19, 0x2A, 0x0B,
  0x2C, 0x0D, 0x0E, 0x1C,
};

buffer_type encoding_encode_4b6b(const buffer_type& source)
{
  buffer_type dst = buffer_create(source.s * 1.5);
  size_t i = 0, n = 0, msg_s = source.rcv_s - 1;
  byte x = 0, r = 0, a = 0, b = 0;//x = input, r = remainder, a and b are outputs
  
  // 1 input byte produce 1 + 0.5 remainder output bytes.
  for (i, n; i <= msg_s; i++, n ++) {
    x = source.buff[i];

    a = (table_4b6b[HI(4, x)] << 2); 
    b = table_4b6b[LO(4, x)];

    // Odd final input byte, if any, produces 2 output bytes.
    //This portion is checked first so we can avoid destorying the message
    //because of needed padding
    if (i == msg_s) {  
      dst.buff[n++] = a | HI(4, b);
      dst.buff[n++] = (LO(4, b) << 4) | 0b0101;  // pad
      break;
    }
  
    if(!r)//a and b are never going to be purely zero
    {
      dst.buff[n] = a | HI(4, b);
      r = (LO(4, b) << 4);
      r++;//Increment just in case a and b ever yield an r = 0, protection flag
    }
    else
    {
      r--;//Decrement r to remove the protection flag
      dst.buff[n] = r | HI(4, a);
      dst.buff[n++] = LO(4, a) | b;
      r = 0;
    }
  }
  dst.rcv_s = n;
  return dst;
}

buffer_type encoding_decode_4b6b(const buffer_type& source)
{
  buffer_type dst = buffer_create(source.s / 1.5);
  size_t i = 0, n = 0, msg_s = source.rcv_s - 2;
  byte x = 0, y = 0, z = 0, \
  a = 0, b = 0, c = 0, d = 0;//x, y, and z = inputs, a, b, c and d are outputs

  // 3 input bytes produce 2 output bytes.
  for (i, n; i <= msg_s; i += 3, n += 2) {
    x = source.buff[i], y = source.buff[i + 1], z = source.buff[i + 2];

    a = encoding_decode_4b6b_helper(HI(6, x));
    b = encoding_decode_4b6b_helper((LO(2, x) << 4) | HI(4, y));
    c = encoding_decode_4b6b_helper((LO(4, y) << 2) | HI(2, z));
    d = encoding_decode_4b6b_helper(LO(6, z));
    if (a == 0xFF || b == 0xFF)
    {
      dst.rcv_s = -1;
      return dst;
    }
    // Final 2 input bytes produce 1 output byte.
    if (i == msg_s) {  
      dst.buff[n++] = (a << 4) | b;
      break;
    } else if (i == msg_s + 1) {
      dst.rcv_s = -1;
      return dst;
    }  // shouldn't happen
    else
    {
      if (c == 0xFF || d == 0xFF)
      {
        dst.rcv_s = -1;
        return dst;
      }
      dst.buff[n] = (a << 4) | b;
      dst.buff[n + 1] = (c << 4) | d;
    }
  }
  dst.rcv_s = n;
  return dst;
}

byte encoding_decode_4b6b_helper(byte val)
{
  for(byte i = 0; i < 16; i++)
  {
    if(table_4b6b[i] == val)
      return i;
  }
  return 0xFF;
}

#endif

#ifdef ENCODING_MANCHESTER
/*Manchester line coding algorithm
 * Implementation based on 
 */

#endif


#ifdef ENCODING_TOOLS
buffer_type encoding_encode(const buffer_type& source)
{
  return _encoding_encode(source);
}

buffer_type encoding_decode(const buffer_type& source)
{
  return _encoding_decode(source);
}
#endif

#ifdef ENCODING_TESTS

#endif
