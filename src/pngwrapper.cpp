#include "pngwrapper.h"
#include "utils.h"
#include <cstdlib>
#include <cstdio>
#include <png.h>


// #include "png++/image.hpp"
// uint32_t* png_read(const std::string& filename, int& width,
//                    int& height, char& bit_depth, int& error)
// {
//     png::image<png::rgb_pixel> png_image;
//     try
//     {
//         png_image.read(filename); 
//     }
//     catch (std::exception& e)
//     {
//         error = -1;
//         return NULL;
//     }
// 
//     height = png_image.get_height();
//     width = png_image.get_width();
// 
//     uint32_t* image = alloc_image(width, height);
//     for(int y = 0; y < height; ++y)
//     {
//         for(int x = 0; x < width; ++x)
//         {
//             png::rgb_pixel = png_image[y][x];
//             uint32_t color = 0;
//             color |= rgb_pixel.red << 24;
//             color |= rgb_pixel.red << 16;
//             color |= rgb_pixel.red << 8;
// 
//             image[y * width + x] = color;
//         }
//     }
// 
//     return image;
// }


uint32_t* png_read(const std::string& filename, int& width,
                   int& height, char& bit_depth, int& error)
{
    png_bytep *row_pointers;
    png_byte color_type;

    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp)
    {
        error = -1;
        return (NULL);
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if(!png)
    {
        error = -2;
        return (NULL);
    }

    png_infop info = png_create_info_struct(png);
    if(!info)
    {
        error = -3;
        return (NULL);
    }

    if(setjmp(png_jmpbuf(png)))
    {
        error = -4;
        return (NULL);
    }

    png_init_io(png, fp);
    png_read_info(png, info);

    width      = png_get_image_width(png, info);
    height     = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth  = png_get_bit_depth(png, info);

    if(bit_depth == 16)
    {
        png_set_strip_16(png);
    }

    if(color_type == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(png);
    }

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    {
        png_set_expand_gray_1_2_4_to_8(png);
    }

    //
    if(png_get_valid(png, info, PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(png);
    }

    if(color_type == PNG_COLOR_TYPE_RGB ||
       color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    }

    if(color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
        png_set_gray_to_rgb(png);
    }

    png_read_update_info(png, info);

    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for(int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }

    png_read_image(png, row_pointers);

    uint32_t* image = new uint32_t[width * height];
    for(int y = 0; y < height; y++)
    {
        png_bytep row = row_pointers[y];
        for(int x = 0; x < width; x++)
        {
            png_bytep px = &(row[x * 4]);
            uint32_t color = 0;
            color |= uint32_t(px[0]) << 24;
            color |= uint32_t(px[1]) << 16;
            color |= uint32_t(px[2]) << 8;
            color |= uint32_t(px[3]);

            image[y * width + x] = color;
        }
    }

    png_destroy_read_struct(&png, &info, NULL);
    fclose(fp);

    error = 0;
    return image;
}


int png_write(const std::string& filename, long width,
              long height, uint32_t* image)
{
    FILE *fp = fopen(filename.c_str(), "wb");
    if (!fp)
    {
        return (-1);
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
    {
        return (-2);
    }

    png_infop info = png_create_info_struct(png);
    if (!info)
    {
        return (-3);
    }

    if (setjmp(png_jmpbuf(png)))
    {
        return (-4);
    }

    png_init_io(png, fp);

    png_set_IHDR(
        png,
        info,
        width, height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );

    png_write_info(png, info);

    png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for(int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            row_pointers[y][x * sizeof(uint32_t)] = image[y * width + x];
        }
    }

    png_write_image(png, row_pointers);
    png_write_end(png, NULL);

    for(int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }

    free(row_pointers);
    fclose(fp);

    return (0);
}

std::string err_str(int err)
{
    switch(err)
    {
    case -1:
        return "Fail to open file";
    case -2:
        return "Fail to create png struct";
    case -3:
        return "Fail to create info struct";
    case -4:
        return "Fail IO operation";
    default:
        return "Uknown error";
    }
}
