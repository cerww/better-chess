#pragma once
#include "window.h"
#include "vertex.h"
#include "drawableObj.h"
#include "things.h"
#include <functional>
#include <array>

//template<typename fn>
class button:private drawableObj {
public:
	button() = default;
	button(glm::vec4, std::array<texture, 3> t, std::array<Color, 3> C, std::function<void()> f);

	button(glm::vec4, texture t, Color C, std::function<void()> f);
	//template<typename ... Args>
	void doClick();
	
	void setNormalTexture(texture t) {
		m_normalTexture = std::move(t);
	}

	void setNormalColor(Color c) {
		m_normalColor = std::move(c);
	}

	void setHoverColor(Color c) {
		m_hoverColor = std::move(c);
	}
	void setHoverTexture(texture t){
		m_hoverTexture = std::move(t);
	}

	void setClickColor(Color c) {
		m_clickColor = std::move(c);
	}
	void setClickTexture(texture t) {
		m_clickTexture = std::move(t);
	}
	
	//void getState(const app&);
	using drawableObj::getSpot;
	using drawableObj::draw;
	void update(const glm::vec2,int);
protected:
	Color m_normalColor;
	texture m_normalTexture;

	Color m_hoverColor;
	texture m_hoverTexture;

	Color m_clickColor;
	texture m_clickTexture;
private:
	enum class state {NORMAL,HOVER,CLICKED};
	std::function<void()> m_function;
	//bool m_clicked = 0;
	state m_currentState = state::NORMAL;
};
/*
inline auto makeButton(glm::vec4 d, texture t, Color C, fn f,const std::string& s) {
	return button(d, t, C, f,s);
}*/
