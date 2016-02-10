#include "image.h"
#include "utils.h"
#include "pngwrapper.h"
#include "jpegwrapper.h"
#include <cstring>


Image* open_image(const std::string& filename)
{
    Image* image = new Image;
    memset(image, 0, sizeof(Image));
    int error = 0;
    char bit_depth = 0;

    std::string ext = get_extension(filename);
    if (ext.length() == 0)
    {
        error = 10;
    }

    if (ext == "jpg" ||  ext == "jpeg")
    {
        image->buffer = jpeg_read(filename, image->width,
                                  image->height, error);
    }

    if (ext == "png")
    {
        image->buffer = png_read(filename, image->width,
                                 image->height, bit_depth, error);

        image->type = IMAGE_TYPE::PNG;
    }

    if (ext == "exr")
    {
        error = 5;
    }

    if (error)
    {
        delete image;
        return NULL;
    }

    return image;
}

Image* create_image(int width, int height)
{
    Image* image = new Image;
    image->buffer = new uint32_t[width * height];
    image->width = width;
    image->height = height;

    return image;
}

int write_image(const std::string& filename, const Image* image)
{
    switch(image->type)
    {
    case IMAGE_TYPE::PNG:
        return png_write(filename, image->width, 
                         image->height, image->buffer);

    case IMAGE_TYPE::EXR:
        return (-1);

    default:
        return (10);
    }
}

void free_image(Image* image)
{
    delete image->buffer;
    delete image;
}
