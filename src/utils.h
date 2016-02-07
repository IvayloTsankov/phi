#ifndef PHI_UTILS_H_
#define PHI_UTILS_H_

#include <cstdint>


uint32_t* alloc_image(int width, int height);
void free_image(uint32_t* img);

uint32_t* scale(uint32_t* src_img, int src_w, int src_h,
                int dst_w, int dst_h);


#endif // PHI_UTILS_H_
