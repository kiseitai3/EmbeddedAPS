#ifndef DEF_H_GUARD
#define DEF_H_GUARD


typedef void* void_ptr;



typedef enum file_mode_t
{
  READ, WRITE_TRUNC, WRITE_APPEND
}file_mode_t;

#define wireless_destroy_packet(p) buffer_destroy(p)
#define wireless_write_packet(p,msg) buffer_write(p,msg)

#endif // DEF_H_GUARD
