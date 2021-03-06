#ifndef PHI_IMAGE_H_
#define PHI_IMAGE_H_

#include <string>
#include <cstdint>


enum class IMAGE_TYPE
{
    PNG,
    EXR,
    JPEG
};

struct Image
{
    uint32_t* buffer;
    int width;
    int height;
    IMAGE_TYPE type;
};


Image* open_image(const std::string& filename);
Image* create_image(int width, int height);
int write_image(const std::string& filename, const Image* image);
void free_image(Image* image);


#endif // PHI_IMAGE_H_
