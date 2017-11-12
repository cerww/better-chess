#pragma once
#ifndef CW_WINDOW_H
#define CW_WINDOW_H
#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include "texture.h"
#include "GLSLthingy.h"
#include "imgLoader.h"
#include "SpriteBatch.h"
#include "camera2D.h"
#include "fpslimiter.h"
#include <thread>
#include <future>
#include <glm/glm.hpp>
#include <array>
#include "Event.h"

class window{//just a window, and the keys/mouse
    public:
		window(GLFWwindow* );
        void update();
        int getKey(Keys key)const;
        glm::vec2 getMousePos()const;
        int getMouseButton(mouseB Button)const;
        texture getTexture(const std::string&);
        void setMaxFPS(int);
        void wait();
		GLFWwindow * getWindowPtr() const { return _window; };
		static void setCodePoint(GLFWwindow* win, uint32_t t_codePoint) {
			m_refs[win]->m_codePoint = t_codePoint;
		}
		static void setScrolled(GLFWwindow* win,double x,double y){
			m_refs[win]->m_scrolled = { x,y };
		}
		uint32_t getCodePoint(){
			return std::exchange(m_codePoint,0);//i have to get rid of code point somewhere
		};
		std::pair<double,double> getScrolled()const {
			return m_scrolled;
		}
		static void initialize();
    private:
		struct keys {
			std::array<int32_t, (size_t)Keys::MAX> k = {};
			std::array<int32_t, (size_t)mouseB::MAX> m = {};
		};
        GLFWwindow* _window;
        keys _keys;
        glm::dvec2 m_mousePos;
        std::unordered_map<std::string,texture> _textures;
        fpslimiter _fpsLimiter;
		uint32_t m_codePoint = 0;
		static std::unordered_map<GLFWwindow*, window*> m_refs;//for code points
		std::pair<double, double> m_scrolled;
};

#endif // CW_WINDOW_H
