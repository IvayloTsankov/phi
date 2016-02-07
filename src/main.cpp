#include "slog/slog.h"
#include "pngwrapper.h"
#include "sdl.h"


// void process_png_file()
// {
//     for(int y = 0; y < height; y++)
//     {
//         png_bytep row = row_pointers[y];
//         for(int x = 0; x < width; x++)
//         {
//             png_bytep px = &(row[x * 4]);
//             // Do something awesome for each pixel here...
//             //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
//         }
//     }
// }


int main(int argc, char *argv[])
{
//     if (argc < 2)
//     {
//         SLOG("Usage: phi <image_path>");
//         return (1);
//     }

    std::string filename = "images/android.png";

    int width = 0;
    int height = 0;
    char bit_depth = 0;
    int ret = 0;
    uint32_t* image = png_read(filename, width, height, bit_depth, ret);
    if (ret)
    {
        std::string error = err_str(ret);
        SLOG("%s", error.c_str());
        return (1);
    }

    SLOG("Open image %s (width: %d) (height: %d) (ret: %d)", filename.c_str(), width, height, ret);

    int size = width * height;
// 
//     for (int i = 0; i < height; ++i)
//     {
//         for (int j = 0; j < width; ++j)
//             printf("%d", image[i * width + j]);
//     }
//     return (5);

    if (!initGraphics(width, height))
    {
        SLOG("Fail to init sdl");
        return (2);
    }

    displayVFB(image, width, height);
    waitForUserExit();
    closeGraphics();

//     if(argc != 3) abort();

//     read_png_file(argv[1]);
//     process_png_file();
//     write_png_file(argv[2]);

    return 0;
}
