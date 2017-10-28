#pragma once
#include "drawableObj.h"
#include "camera2D.h"

class UIRenderer :
	public drawRenderer
{
public:
	UIRenderer(glm::vec2 t_screenSize);
	void renderUI();
private:
	camera2D m_uiCam;
};

