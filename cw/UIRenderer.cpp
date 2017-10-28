#include "UIRenderer.h"



UIRenderer::UIRenderer(glm::vec2 t_screenSize):m_uiCam(t_screenSize.x,t_screenSize.y){
	m_uiCam.update();
}

void UIRenderer::renderUI(){
	render(m_uiCam);
}

