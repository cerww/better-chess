#ifndef RENDERER_H
#define RENDERER_H
#include "SpriteBatch.h"
#include "resourceManager.h"
#include "GLSLthingy.h"
#include "camera2D.h"
#include <memory>

template<typename Renderer>
class renderer//interface class 
{
    public:
        renderer() = default;
		void render(const camera2D& cam){
			static_cast<Renderer*>(this)->Render(cam);
		};
};

#endif // RENDERER_H

