#pragma once
#include "window.h"
#include "vertex.h"
#include "drawableObj.h"
#include "things.h"
#include <type_traits>

template<typename fn>
class button2:private drawableObj {
public:
	button2() = delete;
	button2(glm::vec4 dims, std::array<texture, 3> m_t, std::array<Color, 3> m_c, fn t_f):
		m_dims(std::move(dims)),
		m_normalTexture(m_t[0]),
		m_normalColor(m_c[0]),
		m_hoverTexture(m_t[1]),
		m_hoverColor(m_c[1]),
		m_clickTexture(m_t[2]),
		m_clickColor(m_c[2]),
		m_f(std::move(t_f)){};

	using drawableObj::getSpot;
	using drawableObj::draw;
	void update(const glm::vec2, int) {
		if (pointInBox(m_dims, mousePos)) {
			if (durationOfClick) {
				m_currentState = state::CLICKED;
				m_texture = m_clickTexture;
				m_color = m_clickColor;
			}
			else {
				m_currentState = state::HOVER;
				m_texture = m_hoverTexture;
				m_color = m_hoverColor;
			}
		}
		else {
			m_currentState = state::NORMAL;
			m_texture = m_normalTexture;
			m_color = m_normalColor;
		};
	}
	template<typename ... Args>
	void click(Args...args) {
		m_f(std::forward<Args>(args)...);
	};
protected:
	Color m_normalColor;
	texture m_normalTexture;

	Color m_hoverColor;
	texture m_hoverTexture;

	Color m_clickColor;
	texture m_clickTexture;

	glm::vec4 m_dims;

private:
	enum class state { NORMAL, HOVER, CLICKED };
	fn m_f;
	state m_currentState = state::NORMAL;
};

template<typename fn>
inline auto make_button(glm::vec4 dims, std::array<texture, 3> m_t, std::array<Color, 3> m_c, fn t_f) {
	return button2<fn>(std::move(dims), std::move(m_t), std::move(m_c), std::move(t_f));
}

template<typename fn>
inline auto make_button(glm::vec4 dims, texture m_t, Color m_c, fn t_f) {
	return button2<fn>(std::move(dims), std::array<texture, 3>{m_t, m_t, m_t}, std::array<Color, 3>{m_c, m_c, m_c}, std::move(t_f));
}

