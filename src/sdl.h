#ifndef __SDL_H__
#define __SDL_H__

#include <cstdint>

bool init_graphics(int frameWidth, int frameHeight);
void close_graphics(void);
void display_vfb (uint32_t* vfb, int width, int height);
bool handle_user_input(void);
int frame_width(void);
int frame_height(void);

#endif // __SDL_H__
