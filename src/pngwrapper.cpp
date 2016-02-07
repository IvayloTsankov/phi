#include "pngwrapper.h"
#include <cstdlib>
#include <cstdio>
#include <png.h>



int png_read(const std::string& filename, long& width,
             long& height, char& bit_depth, uint32_t* image)
{
    png_bytep *row_pointers;
    png_byte color_type;

    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp)
    {
        return (-1);
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if(!png)
    {
        return (-2);
    }

    png_infop info = png_create_info_struct(png);
    if(!info)
    {
        return (-3);
    }

    if(setjmp(png_jmpbuf(png)))
    {
        return (-4);
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

    image = new uint32_t[height * width];
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            image[y * width + x] = uint32_t(row_pointers[y][x * sizeof(uint32_t)]);
        }
    }

    png_destroy_read_struct(&png, &info, NULL);
    fclose(fp);
    return (0);
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
    case 1:
        return "Fail to open file";
    case 2:
        return "Fail to create png struct";
    case 3:
        return "Fail to create info struct";
    case 4:
        return "Fail IO operation";
    default:
        return "Uknown error";
    }
}
