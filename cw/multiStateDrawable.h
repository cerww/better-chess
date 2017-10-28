#ifndef MULTISTATEDRAWABLE_H
#define MULTISTATEDRAWABLE_H
#include "drawableObj.h"


class multiStateDrawable:public drawableObj
{
    public:
        multiStateDrawable()=default;
        multiStateDrawable(glm::vec4,const std::string&);

    protected:

    private:
};

#endif // MULTISTATEDRAWABLE_H
