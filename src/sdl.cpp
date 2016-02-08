#include <SDL/SDL.h>
#include <stdio.h>
#include "sdl.h"
#include "slog/slog.h"


SDL_Surface* screen = NULL;

/// try to create a frame window with the given dimensions
bool init_graphics(int frameWidth, int frameHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Cannot initialize SDL: %s\n", SDL_GetError());
		return false;
	}

	screen = SDL_SetVideoMode(frameWidth, frameHeight, 32, 0);
	if (!screen) {
		printf("Cannot set video mode %dx%d - %s\n", frameWidth, frameHeight, SDL_GetError());
		return false;
	}
	return true;
}

/// closes SDL graphics
void close_graphics(void)
{
	SDL_Quit();
}

/// displays a VFB (virtual frame buffer) to the real framebuffer, with the necessary color clipping
void display_vfb(uint32_t* vfb, int width, int height)
{
	int rs = screen->format->Rshift;
	int gs = screen->format->Gshift;
	int bs = screen->format->Bshift;

    if (width > screen->w || height > screen->h)
    {
        return;
    }

	for (int y = 0; y < screen->h; ++y)
    {
		Uint32 *row = (Uint32*) ((Uint8*) screen->pixels + y * screen->pitch);

		for (int x = 0; x < screen->w; x++)
        {
            uint32_t color = vfb[y * width + x];
            uint8_t red = uint8_t(color >> 24);
            uint8_t green = uint8_t(color >> 16);;
            uint8_t blue = uint8_t(color >> 8);

            Uint32 sdl_color = 0;
            sdl_color |= Uint32(red << rs);
            sdl_color |= Uint32(green << gs);
            sdl_color |= Uint32(blue << bs);
			row[x] = sdl_color;
        }
	}

	SDL_Flip(screen);
}

/// returns the frame width
int frame_width(void)
{
	if (screen) return screen->w;
	return 0;
}

/// returns the frame height
int frame_weight(void)
{
	if (screen) return screen->h;
	return 0;
}
