#include "slog/slog.h"
#include "sdl.h"
#include "utils.h"
#include "image.h"
#include "effects.h"
#include <SDL/SDL.h>


bool handle_user_input(Image* image)
{
	SDL_Event ev;
    while (SDL_WaitEvent(&ev))
    {
        SLOG("Event occurs");
        switch (ev.type)
        {
        case SDL_KEYDOWN:
        {
            switch (ev.key.keysym.sym) {
                case SDLK_1:
                    BlackAndWhite(image);
                    break;
                case SDLK_2:
                    BrightnessBoost(image);
                    break;
                case SDLK_ESCAPE:
                    return false;
                default:
                    break;
            }
        }
        case SDL_QUIT:
            break;
        default:
            break;
        }

        display_vfb(image->buffer, image->width, image->height);
    }

    return false;
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        SLOG("Usage: phi <image_path>");
        return (1);
    }

    //std::string filename = "images/android.png";
    std::string filename = argv[1];

    Image* image = open_image(filename, IMAGE_TYPE::PNG);
    if (! image)
    {
        SLOG("Fail to open: %s", filename.c_str());
        return (1);
    }

    SLOG("Open image %s (width: %d) (height: %d)",
         filename.c_str(), image->width, image->height);

    if (!init_graphics(image->width, image->height))
    {
        SLOG("Fail to init sdl");
        return (2);
    }

    bool start = true;
    while(start)
    {
        start = handle_user_input(image);
    }

    free_image(image);
    close_graphics();
    return 0;
}
