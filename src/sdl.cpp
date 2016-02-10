#include "sdl.h"
#include <SDL/SDL.h>
#include <stdio.h>
#include "scale.h"
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
void display_vfb(uint32_t* image, int width, int height)
{
    uint32_t* vfb = image;
    int vfb_w = width;
    int vfb_h = height;
    bool scaled = false;
    if (width > screen->w || height > screen->h)
    {
        vfb = scale(image, width, height, screen->w, screen->h);
        vfb_w = screen->w;
        vfb_h = screen->h;
        scaled = true;
    }

	int rs = screen->format->Rshift;
	int gs = screen->format->Gshift;
	int bs = screen->format->Bshift;

	for (int y = 0; y < vfb_h; ++y)
    {
		Uint32 *row = (Uint32*) ((Uint8*) screen->pixels + y * screen->pitch);

		for (int x = 0; x < vfb_w; x++)
        {
            uint32_t color = vfb[y * vfb_w + x];
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

    if (vfb_w < screen->w)
    {
        for (int y = 0; y < vfb_h; ++y)
        {
            Uint32 *row = (Uint32*) ((Uint8*) screen->pixels + y * screen->pitch);
            for (int x = vfb_w; x < screen->w; x++)
            {
                row[x] = 0;
            }
        }
    }

    if (vfb_h < screen->h)
    {
        for (int y = vfb_h; y < screen->h; ++y)
        {
            Uint32 *row = (Uint32*) ((Uint8*) screen->pixels + y * screen->pitch);
            for (int x = 0; x <  screen->w; x++)
            {
                row[x] = 0;
            }
        }
    }

    if (scaled)
    {
        delete vfb;
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
int frame_height(void)
{
	if (screen) return screen->h;
	return 0;
}

void wait_for_exit(void)
{
   SDL_Event ev; 
   while (1)
   {
       while (SDL_WaitEvent(&ev))
       {
           switch (ev.type)
           {
               case SDL_QUIT:
                   return;
               case SDL_KEYDOWN:
               {   
                   switch (ev.key.keysym.sym)
                   {
                       case SDLK_ESCAPE:
                           return;
                       default:
                           break;
                   }
               }
               default:
                   break;
           }
       }
   }
}
