#include "../src/sdl.h"
#include "../third_party/slog/slog.h"


int main()
{
    int width = 640;
    int height = 480;
    uint32_t color = 0xAAAA0000;

    if (!initGraphics(width, height))
    {
        SLOG("Fail to init SDL");
        return (1);
    }

    uint32_t* vfb = new uint32_t[width * height];
    int size = width * height;
    for(int i = 0; i < size; ++i)
    {
        vfb[i] = color;   
    }

    displayVFB(vfb, width, height);
    waitForUserExit();
    closeGraphics();
}
