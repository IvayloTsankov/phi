#ifndef PHI_UTILS_H_
#define PHI_UTILS_H_

#include <cstdint>


uint32_t* alloc_image_buffer(int width, int height);
void free_image_buffer(uint32_t* img_buffer);

uint32_t* scale(uint32_t* src_img, int src_w, int src_h,
                int dst_w, int dst_h);

void phi_sleep(uint32_t millisec);


#endif // PHI_UTILS_H_
