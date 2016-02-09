#ifndef PHI_SDL_H_
#define PHI_SDL_H_

#include <cstdint>

bool init_graphics(int frameWidth, int frameHeight);
void close_graphics(void);
void display_vfb (uint32_t* vfb, int width, int height);
void wait_for_exit(void);
int frame_width(void);
int frame_height(void);

#endif // PHI_SDL_H_
