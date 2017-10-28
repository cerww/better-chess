#include "fpslimiter.h"

fpslimiter::fpslimiter():_prevFrame(glfwGetTime())
{
    //ctor
}
void fpslimiter::limitFPS(){
    auto currentFrame=glfwGetTime();
    if(currentFrame-_prevFrame<1.0/_maxFPS){
        std::this_thread::sleep_for(std::chrono::microseconds((int)(1000000.0*((1.0/_maxFPS)-(currentFrame-_prevFrame)))));
    }else{
        //std::cout<<1/(currentFrame-_prevFrame)<<std::endl;
    }
    //std::cout<<(currentFrame-_prevFrame)<<std::endl;
    //std::cout<<(1.0/_maxFPS)-(currentFrame-_prevFrame)<<std::endl;
    _prevFrame=glfwGetTime();
}
