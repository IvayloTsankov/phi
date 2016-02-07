#ifndef PNGWRAPPER_H_
#define PNGWRAPPER_H_

#include <string>
#include <cstdint>


int png_read(const std::string& filename, long& width,
             long& height, char& bit_depth, uint32_t* image);

int png_write(const std::string& filename, long width,
              long height, uint32_t* image);

std::string err_str(int err);


#endif // PNGWRAPPER_H_
