#include "utils.h"

#if defined (_WIN32)
#   include <WinBase.h>
#else
#   include <unistd.h>
#endif // (_WIN32)

void phi_sleep(uint32_t millisec)
{
#if defined (_WIN32)
    Sleep(millisec);
#else
    usleep(millisec * 1000);
#endif // (_WIN32)
}

std::string get_extension(const std::string& filename)
{
    size_t ext_pos = filename.rfind(".");
    std::string extension;
    if (ext_pos != std::string::npos)
    {
        extension = filename.substr(ext_pos + 1, filename.length());
    }

    return extension;
}
