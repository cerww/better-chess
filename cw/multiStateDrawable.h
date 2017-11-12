#pragma once
#include "drawableObj.h"


class multiStateDrawable:public drawableObj
{
    public:
        multiStateDrawable()=default;
        multiStateDrawable(glm::vec4,const std::string&);

    protected:

    private:
};
