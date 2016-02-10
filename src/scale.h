#ifndef PHI_SCALE_H_
#define PHI_SCALE_H_

#include <cstdint>

#ifndef NULL
#define NULL 0
#endif // NULL


// If modify is true function returns NULL and override
// src_img, src_w, src_h
uint32_t* scale(uint32_t* src_img, int& src_w, int& src_h,
                int dst_w, int dst_h, bool modify=false);

#endif // PHI_SCALE_H_
