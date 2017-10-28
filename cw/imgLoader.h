#ifndef IMGLOADER_H
#define IMGLOADER_H
#include "texture.h"
#include <string>
class imgLoader
{
    public:
        static texture loadPNG(const std::string &path);
    protected:

    private:
};

#endif // IMGLOADER_H
