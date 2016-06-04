#include <string>
#include <iostream>


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

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: fileext <finame>" << std::endl;
        return (1);
    }

    std::string filename(argv[1]);
    std::string ext = get_extension(filename);
    std::cout << ext << std::endl;
    return (0);
}
