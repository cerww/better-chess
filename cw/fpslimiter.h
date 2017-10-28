#ifndef FPSLIMITER_H
#define FPSLIMITER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>
class fpslimiter
{
    public:
        fpslimiter();
        void setMaxFPS(int newfps){_maxFPS=newfps;};
        double getMaxFPS(){return _maxFPS;};
        void limitFPS();

    protected:

    private:
        double _prevFrame;
        double _maxFPS = 60.0;
};

#endif // FPSLIMITER_H
