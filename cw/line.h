#pragma once
#include "drawableObj.h"
#include "Rectangle.h"
#include "Drawable.h"

class line:public Drawable<line>{
public:
	line() = default;
	line(glm::vec2 t_p1, glm::vec2 t_p2, Color t_color = colours::WHITE, size_t t_width = 2) :m_p1(t_p1), m_p2(t_p2), m_color(t_color), m_width(t_width) {};
	void Draw(drawRenderer&);
private:
	glm::vec2 m_p1;
	glm::vec2 m_p2;
	Color m_color;
	size_t m_width;
};

enum class line_type {
	ROUND,
	BLOCK
};

template<line_type type>
inline void drawLine(drawRenderer & renderer, const glm::vec2 p1, const glm::vec2 p2, const Color color, const size_t width) {
	const math::radians angle = math::atan2((p1 - p2).x, (p1 - p2).y).reverse();//rotate get rotates counter clockwise, needs to be other way
	const double length = glm::length(p1 - p2);
	renderer.draw(glm::vec4{ p1.x,p1.y,width,length },
		defaultUV,
		Rectangle::getFlatColor().id,
		color,
		1.0f,
		angle,
		glm::vec2{p1.x + width/2,p1.y});
	if constexpr(type == line_type::ROUND) {
		circle::drawCircle(renderer, p1, width / 2, color);
		circle::drawCircle(renderer, p2, width / 2, color);
	}
}