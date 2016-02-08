#include "../src/sdl.h"
#include "../src/utils.h"
#include "SDL/SDL.h"
#include "slog/slog.h"
#include <climits>


void infinite_poll()
{
    bool quit = false;
    while(!quit)
    {
        SDLKey key;
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            SLOG("Event occurs");
            if (ev.type == SDL_KEYDOWN)
            {
                key = ev.key.keysym.sym;
                break;
            }
        }

        SLOG("Press: %d", key);
        if (key == SDLK_ESCAPE)
        {
            quit = true;
        }
    }
}

// Return values:
//      1 - KEY_DOWN
//      2 - KEY_UP
//      3 - other event
//      4 - no events
int check_pressed(SDLKey& key)
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        if (ev.type == SDL_KEYDOWN)
        {
            key = ev.key.keysym.sym;
            return (1);
        }
        else if (ev.type == SDL_KEYUP)
        {
            return (2);
        }
        else
        {
            SLOG("OTHER EVENT: %d", ev.type);
            return (3);
        }
    }

    return (4);
}


void test_user_input()
{
    SDLKey key;
    bool quit = false;
    bool pressed = false;
    while(!quit)
    {
        SDLKey user_key;
        int button_status = check_pressed(user_key);
        if (button_status == 1)
        {
            pressed = true;
            key = user_key;
        }
        else if (button_status == 2)
        {
            pressed = false;
        }
        else if (button_status == 3)
        {
            SLOG("Other event");
            continue;
        }
        else if (button_status == 4)
        {
            phi_sleep(50);
            continue;
        }

        switch(key)
        {
        case SDLK_LEFT:
            SLOG("LEFT pressed");
            break;
        case SDLK_RIGHT:
            SLOG("RIGHT pressed");
            break;
        case SDLK_q:
            SLOG("Quit pressed");
            quit = true;
            break;
        case SDLK_ESCAPE:
            SLOG("Escape pressed");
            exit(0);
        default:
            SLOG("No handler for this key");
            break;
        }

    }
}


int main()
{
    init_graphics(640, 480);
    test_user_input();
    close_graphics();
    return (0);
}
