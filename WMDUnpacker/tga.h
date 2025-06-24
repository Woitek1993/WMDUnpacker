#ifndef TGA_H
#define TGA_H

#include <stdint.h>

#pragma pack(push,1)

struct tga_header {
    uint8_t  id_length;
    uint8_t  map_type;
    uint8_t  image_type;
    uint16_t map_first_entry;
    uint16_t map_length;
    uint8_t  map_entry_size;
    uint16_t image_x_origin;
    uint16_t image_y_origin;
    uint16_t image_width;
    uint16_t image_height;
    uint8_t  pixel_depth;
    uint8_t  image_descriptor;
};

#pragma pack(pop)

#endif