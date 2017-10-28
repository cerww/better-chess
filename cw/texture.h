#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <vector>

struct texture
{
        texture() = default;
		texture(GLuint tid, int twidth, int theight):
		        id(tid),width(twidth),height(theight){}

        GLuint id;
        unsigned width;
        unsigned height;

};

#endif // TEXTURE_H
