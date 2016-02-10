#ifndef PHI_EFFECTS_H_
#define PHI_EFFECTS_H_

#include "image.h"
#include "SDL/SDL.h"


void BlackAndWhite(Image* image, SDLKey key, uint8_t type);
void BrightnessChange(Image* image, SDLKey key, uint8_t type);
void ScaleDown(Image* image, SDLKey key, uint8_t type);
void FloydSteinbergDithering(Image* image, SDLKey, uint8_t type);
void Sepia(Image* image, SDLKey, uint8_t type);


#endif // PHI_EFFECTS_H_
