#pragma once
#include <glm\glm.hpp>


struct box{
	box() = default;
	box(glm::vec2 p, int w, int h) :point(p), width(w), height(h) {};
	glm::vec2 point;
	int width;
	int height;
	operator glm::vec4() {
		return glm::vec4{ point.x,point.y,width,height };
	}
};

struct points2{
	points2() = default;
	points2(glm::vec2 t_p1,glm::vec2 t_p2):p1(t_p1),p2(t_p2){}
	glm::vec2 p1 = {};
	glm::vec2 p2 = {};
	operator glm::vec4(){
		return glm::vec4{ p1.x,p1.y,p1.x - p2.x,p1.y - p2.y };
	}
}

