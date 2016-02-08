#include "effects.h"
#include "slog/slog.h"


void split_rgb(uint32_t rgbcolor,
               uint8_t& red, uint8_t& green, uint8_t& blue)
{
    red = rgbcolor >> 24;
    green = rgbcolor >> 16;
    blue = rgbcolor >> 8;
}

uint32_t to_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    uint32_t rgb = 0;

    rgb |= uint32_t(red) << 24;
    rgb |= uint32_t(green) << 16;
    rgb |= uint32_t(blue) << 8;

    return rgb;
}


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
            register uint16_t brightness = (r + g + b) / 3;

            color = to_rgb(brightness, brightness, brightness);
            image_buffer[y * width + x] = color;
        }
    }

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
}
