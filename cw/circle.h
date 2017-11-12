#pragma once
#include "drawableObj.h"


class circle:public Drawable<circle>
{
public:
	circle();
	circle(glm::vec2 t_spot, double t_radius, Color t_colour):spot(t_spot),radius(t_radius),colour(t_colour){}
	static void drawCircle(drawRenderer&,glm::vec2 spot, double r,Color C);
	static texture getCircleTexture();
	glm::vec2 spot = {};
	double radius = 0;
	Color colour = {};
	void Draw(drawRenderer&)const;
private:
	static texture s_circle;
	static void loadCircle(){
		s_circle = imgLoader::loadPNG("circle.png");
	};

};

