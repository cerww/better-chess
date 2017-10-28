#include "slider.h"
#include "things.h"
#include <algorithm>
//pics that all sliders use!
bool slider::Loaded = 0;
texture slider::bar;// = imgLoader::loadPNG("sliderBar.png");
texture slider::barSlider;// = imgLoader::loadPNG("sliderThing.png");

slider::slider(glm::vec4 dims, int min, int max, int start) :
	m_dims(dims),
	m_min(min),
	m_max(max),
	m_current(start) {	
	if (m_min > m_max) 
		std::swap(m_min, m_max);
	if (!Loaded) {
		bar = imgLoader::loadPNG("sliderBar.png");
		barSlider = imgLoader::loadPNG("sliderThing.png");
		Loaded = 1;
	}
}

void slider::draw(drawRenderer & renderer) const{
	//const glm::vec4 barDims = { m_dims.x,m_dims.y + m_dims.w*(m_current - m_min) / (m_max - m_min) - 5,m_dims.z, 10 };
	//barDims.w = m_dims.w *(float)(m_current-m_min)/(float)(m_max/m_min);
	renderer.draw(glm::vec4(m_dims.x, m_dims.y + 2, m_dims.z - 2, m_dims.w), fullPicUV, bar.id, { 255,255,255,255 }, 1.0f);
	renderer.draw(glm::vec4(m_dims.x, m_barYCoords, m_dims.z, 10.0f), fullPicUV, barSlider.id, { 255,255,255,255 }, 1.0f);
}

bool slider::update(const glm::vec2 mouseCoords,int n) {	
	if (n && (mouseCoords.y == m_prevMouseY || !pointInBox(m_dims, mouseCoords))) {
		return false; //do nothing,m_current depends on the y coord,if it's the same as the previsous, it won't change
	}

	m_current = clamp(m_min,m_max,(int)glm::round((((mouseCoords.y - m_dims.y) / ((float)m_dims.w))*(m_max - m_min))) + m_min);

	m_barYCoords = m_dims.y + m_dims.w*(m_current - m_min) / (m_max - m_min) - 5;
	m_prevMouseY = mouseCoords.y;
	return true;
}

