#include "slog/slog.h"
#include "sdl.h"
#include "utils.h"
#include "image.h"
#include "effects.h"
#include "inputhandler.h"
#include <SDL/SDL.h>


// bool handle_user_input(Image* image)
// {
// 	SDL_Event ev;
//     while (SDL_WaitEvent(&ev))
//     {
//         SLOG("Event occurs");
//         switch (ev.type)
//         {
//         case SDL_KEYDOWN:
//         {
//             switch (ev.key.keysym.sym) {
//                 case SDLK_1:
//                     BlackAndWhite(image);
//                     break;
//                 case SDLK_2:
//                     BrightnessBoost(image);
//                     break;
//                 case SDLK_ESCAPE:
//                     return false;
//                 default:
//                     break;
//             }
//         }
//         case SDL_QUIT:
//             break;
//         default:
//             break;
//         }
// 
//         display_vfb(image->buffer, image->width, image->height);
//     }
// 
//     return false;
// }


UserInput* user_input;


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        SLOG("Usage: phi <image_path>");
        return (1);
    }

    std::string filename = argv[1];

    // DEBUG
    //std::string filename = "images/cube.jpg";
    std::unique_ptr<Image>image(open_image(filename));
    if (!image)
    {
        SLOG("Fail to open: %s", filename.c_str());
        return (1);
    }

    SLOG("Open image %s (width: %d) (height: %d)",
         filename.c_str(), image->width, image->height);

    if (!init_graphics(800, 600))
    {
        SLOG("Fail to init sdl");
        return (2);
    }

    display_vfb(image->buffer, image->width, image->height);
    InputHandler handler(std::move(image));
    handler.Bind(SDLK_1, GrayScale);
    handler.Bind(SDLK_2, BrightnessChange);
    handler.Bind(SDLK_3, ScaleDown);
    handler.Bind(SDLK_4, FloydSteinbergDithering);
    handler.Bind(SDLK_5, Sepia);

    user_input = new UserInput();
    user_input->AddHandler(&handler);
    user_input->Start();
    close_graphics();
    return 0;
}
