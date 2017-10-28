#ifndef RENDERER_H
#define RENDERER_H
#include "SpriteBatch.h"
#include "resourceManager.h"
#include "GLSLthingy.h"
#include "camera2D.h"
#include <memory>
class renderer //interface class 
{
    public:
        renderer() = default;
        virtual void render(const camera2D& cam) = 0;
    protected:
        GLSLthingy glslProg;
        SpriteBatch spriteB;
    private:
};

#endif // RENDERER_H

