#pragma once
#include "cw/app.h"
#include "cw/drawableObj.h"
#include "chessGame.h"

class game{
public:
	game(){
		glfwMakeContextCurrent(m_window.getWindowPtr());
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		if (glewInit() != GLEW_OK) {
			std::cout << "glew failed to init" << std::endl;
			glfwTerminate();
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_camera.update();
	}
	void run();
	app& getWindow() { return m_window; }
	camera2D& getCamera() { return m_camera; }
	drawRenderer& getRenderer() { return m_renderer; };
private:
	app m_window = glfwCreateWindow(800, 700, "", NULL, NULL);
	camera2D m_camera = camera2D(800,700);
	drawRenderer m_renderer;
	std::unique_ptr<boardGameBase> m_boardGame;
};

