#include "Rectangle.h"

texture Rectangle::flatColor;// = imgLoader::loadPNG("blank.png");
bool Rectangle::Loaded = 0;

Rectangle::Rectangle(glm::vec4 d,Color c):drawableObj(d,flatColor,c){
	if (!Loaded) {
		Loaded = true;
		flatColor = imgLoader::loadPNG("blank.png");
		m_texture = flatColor;
	}
}
