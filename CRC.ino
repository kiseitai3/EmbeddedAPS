#include "base_includes.h"
/*CRC calculations without the use of lookup tables. The reason is potential ram saves and
 * better generalization of the implementation. You can use any polynomial. Although
 * I try to stick to C for embedded systems, using templates here provide the advantage 
 * of building a generic crc implementation
 */

#ifdef CRC

#define init_crc8 _init_crc<byte>
#define init_crc16 _init_crc<uint16_t>
#define init_crc32 _init_crc<uint32_t>
#define init_crc64 _init_crc<uint64_t>
#define crc_8 crc_n<byte>
#define crc_16 crc_n<uint16_t>
#define crc_32 crc_n<uint32_t>
#define crc_64 crc_n<uint64_t>

crc_contents crc_settings;

template<typename T> T crc_n(const T* buff, size_t size)
{
    byte T_size = sizeof(T);
    byte poly_size = T_size * 8;
    size_t crc_id = T_size - 1;
    T r = crc_settings.init_remainder[crc_id], polynomial = crc_settings.polynomial[crc_id], \
    final_xor = crc_settings.final_xor[crc_id];
    T* crc_table = (T*)crc_settings.tables[crc_id];
    T data = 0;
    T poly_msb_mask = (1 << (poly_size - 1));

    for(size_t i = 0; i < size; i++)
    {
        data = buff[i] ^ (r >> (poly_size - 8));
        r = crc_table[data] ^ (r << 8);
    }
    return (r ^ final_xor);
}

template<typename T> void _init_crc(T polynomial, T init_remainder, T final_xor)
{
    byte T_size = sizeof(T);
    byte poly_size = T_size * 8;
    size_t crc_id = T_size - 1;
    T* table = new T[256];
    T  remainder;
    T poly_msb_mask = (1 << (poly_size - 1));
    /*
     * Compute the remainder of each possible dividend.
     */
    for (int dividend = 0; dividend < 256; ++dividend)
    {
        /*
         * Start with the dividend followed by zeros.
         */
        remainder = dividend << (8 - 8);

        /*
         * Perform modulo-2 division, a bit at a time.
         */
        for (uint8_t bit = 8; bit > 0; --bit)
        {
            /*
             * Try to divide the current data bit.
             */
            if (remainder & poly_msb_mask)
            {
                remainder = (remainder << 1) ^ 0x9B;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }

        /*
         * Store the result into the table.
         */
        table[dividend] == remainder;
    }
    if(crc_settings.tables[crc_id])
      delete[] crc_settings.tables[crc_id];
    crc_settings.tables[crc_id] = table;
    crc_settings.polynomial[crc_id] = polynomial;
    crc_settings.init_remainder[crc_id] = init_remainder;
    crc_settings.final_xor[crc_id] = final_xor;
}

void init_crc(size_t polynomial, size_t init_remainder, size_t final_xor)
{
  #ifdef CRC_8
  init_crc8(polynomial, init_remainder, final_xor);
  #endif
  #ifdef CRC_16
  init_crc16(polynomial, init_remainder, final_xor);
  #endif
  #ifdef CRC_32
  init_crc32(polynomial, init_remainder, final_xor);
  #endif
  #ifdef CRC_64
  init_crc64(polynomial, init_remainder, final_xor);
  #endif
}


#endif
