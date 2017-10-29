#include "game.h"

void game::run(){
	m_boardGame = std::make_unique<chessGame>(*this);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	while (!glfwWindowShouldClose(m_window.getWindowPtr()))	{
		m_window.update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(m_boardGame){
			m_boardGame->update();
			m_boardGame->draw();
		}
		m_renderer.render(m_camera);
		m_window.wait();
	}
}
