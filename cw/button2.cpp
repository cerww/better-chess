#include "button2.h"

template<typename fn>
void button2<fn>::update(const glm::vec2 mousePos, int durationOfClick) {
	if (pointInBox(m_dims,mousePos)) {
		if (durationOfClick) {
			m_currentState = state::CLICKED;
			m_texture = m_clickTexture;
			m_color = m_clickColor;
		}else{
			m_currentState = state::HOVER;
			m_texture = m_hoverTexture;
			m_color = m_hoverColor;
		}
	}else {
		m_currentState = state::NORMAL;
		m_texture = m_normalTexture;
		m_color = m_normalColor;
	}
}