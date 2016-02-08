#ifndef PHI_IMAGE_H_
#define PHI_IMAGE_H_

#include <string>
#include <cstdint>


enum class IMAGE_TYPE
{
    PNG,
    EXR
};

struct Image
{
    uint32_t* buffer;
    int width;
    int height;
    IMAGE_TYPE type;
};


Image* open_image(const std::string& filename, IMAGE_TYPE type);
int write_image(const std::string& filename, const Image* image);
void free_image(Image* image);


#endif // PHI_IMAGE_H_
