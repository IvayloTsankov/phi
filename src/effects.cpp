#include "effects.h"
#include "sdl.h"
#include "slog/slog.h"
#include "scale.h"
#include "utils.h"
#include <cmath>
#include <memory>
#include <omp.h>


void GrayScale(Image* image, SDLKey key, uint8_t type)
{
    SLOG_DEBUG("Execute BlakcAndWhite");

    int height = image->height;
    int width = image->width;
    uint32_t* image_buffer = image->buffer;
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            register uint32_t color = image_buffer[y * width + x];
            uint8_t* pixel = (uint8_t*)(image_buffer + (y * width + x));
            uint32_t gray = *(pixel + 1) * 0.2126 + *(pixel + 2) * 0.7152 + *(pixel + 3) * 0.0722;

            gray = gray < 255 ? gray : 255;
            color = to_rgb(gray, gray, gray);
            image_buffer[y * width + x] = color;
        }
    }

    display_vfb(image->buffer, image->width, image->height);
    return;
}

void BrightnessChange(Image* image, SDLKey key, uint8_t type)
{
    SLOG_DEBUG("Execute BrightnessBoost");
    if (key != SDLK_LEFT && key != SDLK_RIGHT)
    {
        SLOG_DEBUG("Invalid effect option: %d", key);
        return;
    }

    if (key == SDLK_LEFT)
    {
        SLOG_DEBUG("Brightness down");
    }

    if (key == SDLK_RIGHT)
    {
        SLOG_DEBUG("Brightness up");
    }

    int height = image->height;
    int width = image->width;
    uint32_t* image_buffer = image->buffer;
    if (key == SDLK_LEFT)
    {
        for(int y = 0; y < height; ++y)
        {
            for(int x = 0; x < width; ++x)
            {
                register uint32_t color = image_buffer[y * width + x];
                uint8_t r, g, b;
                split_rgb(color, r, g, b);

                r = r < 10 ? 0 : r - 10;
                g = g < 10 ? 0 : g - 10;
                b = b < 10 ? 0 : b - 10;

                color = to_rgb(r, g, b);
                image_buffer[y * width + x] = color;
            }
        }
    }
    else
    {
        for(int y = 0; y < height; ++y)
        {
            for(int x = 0; x < width; ++x)
            {
                register uint32_t color = image_buffer[y * width + x];
                uint8_t r, g, b;
                split_rgb(color, r, g, b);

                r = r + 10 > 255 ? 255 : r + 10;
                g = g + 10 > 255 ? 255 : g + 10;
                b = b + 10 > 255 ? 255 : b + 10;

                color = to_rgb(r, g, b);
                image_buffer[y * width + x] = color;
            }
        }
    }

    display_vfb(image->buffer, image->width, image->height);
    return;
}


void ScaleDown(Image* image, SDLKey key, uint8_t type)
{
    if (key != SDLK_LEFT && key != SDLK_RIGHT)
    {
        SLOG_DEBUG("Invalid option for scaling");
        return;
    }

    static int new_width = image->width;
    static int new_height = image->height;
    if (key == SDLK_LEFT)
    {
        if (new_width > 20)
            new_width /= 2;

        if (new_height > 20)
            new_height /= 2;
    }

    if (key == SDLK_RIGHT)
    {
        new_width *= 2;
        new_height *= 2;

        if (new_width > image->width)
            new_width = image->width;

        if (new_height > image->height)
            new_height = image->height;
    }

    SLOG_DEBUG("(w: %d, h: %d) (nw: %d, nh: %d)",
               image->width, image->height,
               new_width, new_height);

    uint32_t* new_img = scale(image->buffer, image->width, image->height, new_width, new_height);
    display_vfb(new_img, new_width, new_height);
    delete new_img;
}


void FloydSteinbergDithering(Image* image, SDLKey key, uint8_t type)
{
    int w = image->width;
    int h = image->height;
    uint32_t* buffer = image->buffer;
    int prop_error = 0;
    for(int y = 0; y < h; ++y)
    {
        for(int x = 0; x < w; ++ x)
        {
            int pixel_i = (y * w) + x;
            int right = (y * w) + x + 1;
            int down = ((y + 1) * w) + x;
            int rdown = ((y + 1) * w) + x + 1;
            int ldown = ((y + 1) * w) + x - 1;

            uint32_t color = buffer[pixel_i];
            uint8_t* pixel = (uint8_t*)(buffer + pixel_i);
            uint32_t gray = (*(pixel) + *(pixel + 1) + *(pixel + 2)) / 3;
            uint32_t new_color = gray > 128 ? 0xFFFFFF00: 0x00000000;
            buffer[pixel_i] = new_color;

            prop_error += gray - new_color;
            prop_error = prop_error / 255 > 1 ? 255 : prop_error;
            if (x < w)
            {    
                uint8_t* np = (uint8_t*)(buffer + right);
                int prop_coef = 0.4375 * prop_error;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
            }

            if (y + 1 < h)
            {
                uint8_t* np = (uint8_t*)(buffer + down);
                int prop_coef = 0.3125 * prop_error;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
            }

            if (y + 1 < h && x + 1 < w)
            {
                uint8_t* np = (uint8_t*)(buffer + rdown);
                int prop_coef = 0.0625 * prop_error;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
            }

            if (y + 1 < h && x - 1 > 0)
            {
                uint8_t* np = (uint8_t*)(buffer + ldown);
                int prop_coef = 0.1875 * prop_error;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
            }
        }
    }

    display_vfb(image->buffer, image->width, image->height);
}

void Sepia(Image* image, SDLKey key, uint8_t)
{
    uint32_t* buffer = image->buffer;
    int width = image->width;
    int height = image->height;

    #pragma omp parallel for
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            uint8_t* pixel = (uint8_t*)(buffer + (y * width + x));
            uint8_t r = *(pixel + 0);
            uint8_t g = *(pixel + 1);
            uint8_t b = *(pixel + 2);

            *(pixel++) = std::min(r * 0.343 + g * 0.686 + b * 0.168, 255.0);
            *(pixel++) = std::min(r * 0.272 + g * 0.534 + b * 0.131, 255.0);
            *(pixel++) = std::min(r * 0.393 + g * 0.769 + b * 0.189, 255.0);
        }
    }

    display_vfb(image->buffer, image->width, image->height);
}
