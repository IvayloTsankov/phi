#include "effects.h"
#include "sdl.h"
#include "slog/slog.h"
#include "scale.h"
#include "utils.h"
#include <cmath>
#include <memory>


void BlackAndWhite(Image* image, SDLKey key, uint8_t type)
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
            uint8_t r, g, b;
            split_rgb(color, r, g, b);
            uint32_t gray = r * 0.2126 + g * 0.7152 + b * 0.0722;

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
        new_width /= 2;
        new_height /= 2;
    }

    if (key == SDLK_RIGHT)
    {
        new_width *= 2;
        new_height *= 2;
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
    for(int y = 0; y < h; ++y)
    {
        int error = 0;
        for(int x = 0; x < w; ++ x)
        {
            int pixel_i = (y * w) + x;
            int right = (y * w) + x + 1;
            int down = ((y + 1) * w) + x;
            int rdown = ((y + 1) * w) + x + 1;
            int ldown = ((y + 1) * w) + x - 1;

            uint32_t color = buffer[pixel_i];
            uint8_t r, g, b;
            split_rgb(color, r, g, b);
            int delta_l = g - r;
            int delta_r = g - b;
            
            if (delta_l <= delta_r)
            {
                error += delta_l;
                color = 0x00000000;
            }
            else
            {
                error += delta_r;
                color = 0xFFFFFF00;
            }
            
            buffer[pixel_i] = color;

            // distribute error
            int error_fraction = error / 16;

            if (x < w)
                buffer[right] += error_fraction;
            if (y + 1 < h)
                buffer[down] += error_fraction;
            if (y + 1 < h && x + 1 < w)
                buffer[rdown] += error_fraction;
            if (y + 1 < h && x - 1 > 0)
                buffer[ldown] += error_fraction;
        }
    }

    display_vfb(image->buffer, image->width, image->height);
}
