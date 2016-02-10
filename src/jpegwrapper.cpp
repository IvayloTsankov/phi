#include "jpegwrapper.h"
#include "utils.h"
#include "slog/slog.h"
#include <jpeglib.h>    
#include <jerror.h>


uint32_t* jpeg_read(const std::string& filename, int& width, int& height,
                    int& error)
{
    unsigned char a, r, g, b;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE * infile;                /* source file */
    JSAMPARRAY pJpegBuffer;       /* Output row buffer */
    int row_stride;               /* physical row width in output buffer */
    if ((infile = fopen(filename.c_str(), "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", filename.c_str());
        error = -1;
        return 0;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    (void) jpeg_read_header(&cinfo, TRUE);
    (void) jpeg_start_decompress(&cinfo);
    width = cinfo.output_width;
    height = cinfo.output_height;

    unsigned char* buffer = new unsigned char [width*height*4];
    unsigned char* it = buffer;
    row_stride = width * cinfo.output_components;
    pJpegBuffer = (*cinfo.mem->alloc_sarray)
               ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

    while (cinfo.output_scanline < cinfo.output_height)
    {
        (void) jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
        for (int x = 0; x < width; x++)
        {
            a = 0; // alpha value is not supported on jpg
            r = pJpegBuffer[0][cinfo.output_components * x];
            if (cinfo.output_components > 2)
            {
                g = pJpegBuffer[0][cinfo.output_components * x + 1];
                b = pJpegBuffer[0][cinfo.output_components * x + 2];
            } else {
                g = r;
                b = r;
            }

            uint32_t color = to_rgb(r, g, b);
            *((uint32_t*)it) = color;
            it += 4;
        }
    }

    fclose(infile);
    (void) jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return (uint32_t*)buffer;
}
