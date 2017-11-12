#ifndef FPSLIMITER_H
#define FPSLIMITER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>
#include <numeric>

constexpr int sampleSize = 5;
class fpslimiter
{
    public:
        fpslimiter();
        void limitFPS();
		double getAvgFPS()const{
			return std::accumulate(m_times, m_times + sampleSize, 0.0) / (double)sampleSize;
		};
		double fps = 60.0;
    private:
		double m_times[sampleSize];
};

#endif // FPSLIMITER_H
