#pragma once
#ifndef APP_H
#define APP_H
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

class app{//just a window, and the keys/mouse
    public:
        app(GLFWwindow* );
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
		uint32_t getCodePoint(){
			return std::exchange(m_codePoint,0);
		};
    private:
		struct keys {
			//std::unordered_map<Keys, int> k;
			std::array<uint16_t, (size_t)Keys::MAX> k = {};
			//std::unordered_map<mouseB, int> m;
			std::array<uint16_t,(size_t)mouseB::MAX> m = {};
		};
        //void test();
        GLFWwindow* _window;
        keys _keys;
        glm::dvec2 m_mousePos;
        std::unordered_map<std::string,texture> _textures;
        fpslimiter _fpsLimiter;
		uint32_t m_codePoint = 0;
		static std::unordered_map<GLFWwindow*, app*> m_refs;//for code points
};

#endif // APP_H
