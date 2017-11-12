#pragma once
#include "drawableObj.h"

class slider:public Drawable<slider> {
public:

	slider() = default;
	slider(glm::vec4,int = 0,int = 100,int = 50);
	int getVal()const { return m_current; };
	glm::vec4 getDims()const { return m_dims; };
	void Draw(drawRenderer&)const;
	bool update(glm::vec2,int);
private:
	static texture bar;// = imgLoader::loadPNG("sliderBar.png");
	static texture barSlider;// = imgLoader::loadPNG("sliderThing.png");
	static bool Loaded;
	glm::vec4 m_dims;
	//int m_current;
	int m_min = 0;
	int m_max = 100;
	float m_barYCoords;
	int m_current; 
	float m_prevMouseY = 2000000.0f;
};