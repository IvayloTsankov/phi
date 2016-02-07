#include "slog/slog.h"
#include "sdl.h"
#include "utils.h"
#include "image.h"


int main(int argc, char *argv[])
{
//     if (argc < 2)
//     {
//         SLOG("Usage: phi <image_path>");
//         return (1);
//     }

    std::string filename = "images/android.png";
    Image* image = open_image(filename, IMAGE_TYPE::PNG);
    if (! image)
    {
        SLOG("Fail to open: %s", filename.c_str());
        return (1);
    }

    SLOG("Open image %s (width: %d) (height: %d)",
         filename.c_str(), image->width, image->height);

    if (!initGraphics(image->width, image->height))
    {
        SLOG("Fail to init sdl");
        return (2);
    }

    displayVFB(image->buffer, image->width, image->height);
    waitForUserExit();
    closeGraphics();
    return 0;
}
