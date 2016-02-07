#include "slog/slog.h"
#include "pngwrapper.h"


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
    if (argc < 2)
    {
        SLOG("Usage: phi <image_path>");
        exit(1);
    }

    std::string filename = argv[1];
    uint32_t* image = NULL;
    long width = 0;
    long height = 0;
    char bit_depth = 0;        
    int ret = png_read(filename, width, height, bit_depth, image);
    if (ret)
    {
        std::string error = err_str(ret);
        SLOG("%s", error.c_str());
    }

    SLOG("Open image %s (width: %ld) (height: %ld)", filename.c_str(), width, height);

//     if(argc != 3) abort();

//     read_png_file(argv[1]);
//     process_png_file();
//     write_png_file(argv[2]);
 
    return 0;
}
