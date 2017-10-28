#pragma once
#include <glm\glm.hpp>
struct box{
	box() = default;
	box(glm::vec2 p, unsigned w, unsigned h) :point(p), width(w), height(h) {};
	glm::vec2 point;
	unsigned width;
	unsigned height;
};