#ifndef PHI_JPEGWRAPPER_H_
#define PHI_JPEGWRAPPER_H_

#include "image.h"

uint32_t* jpeg_read(const std::string& filename, int& width, int& height, int& error);

#endif // PHI_JPEGWRAPPeR_H_
