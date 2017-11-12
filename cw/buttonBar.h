#pragma once
#include "Drawable.h"
#include <glm\glm.hpp>
#include "camera2D.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include "things.h"
#include "window.h"

namespace rawry{
	class holder {
	public:
		holder() = default;
		template<typename T>
		holder& operator=(T other) {
			m_lamby = std::make_unique<lambdaHolder<T>>(std::move(other));
			return *this;
		}

		holder& operator=(const holder&) = delete;

		template<typename fn>
		holder(fn f) :m_lamby(std::make_unique<lambdaHolder<fn>>(f)) {}
		~holder() = default;
		void operator()() {
			(*m_lamby)();
		}
	private:
		class lambdaHolderBase {
		public:
			virtual void operator()() = 0;
		};
		template<typename fn>
		class lambdaHolder :public lambdaHolderBase {
		public:
			lambdaHolder(fn t_lambda) :m_lambda(std::move(t_lambda)) {};
			void operator()() override final {
				m_lambda();
			}
		private:
			fn m_lambda;
		};
		std::unique_ptr<lambdaHolderBase> m_lamby = nullptr;
	};
};

class buttonBar:public Drawable<buttonBar> {
public:
	buttonBar(glm::vec2 t_pos,double t_height):m_pos(t_pos),m_height(t_height){}
	template<typename fn>
	void addButton(std::string text, double width, fn function, int index = -1){
		if (index == -1) index = m_buttons.size() - 1;
		m_buttons.insert(m_buttons.begin() + index, buttony{ std::move(text),width,std::move(function) });
		m_totalWidth += width;
	};
	void Draw(drawRenderer& r){
		
	};
	void update(const window& win,const camera2D& cam){
		//m_totalWidthCache = std::accumulate(m_buttons.begin(), m_buttons.end(), 0, [](const auto& b) {return b.width; });
		const auto mouseCoords = cam.scrnToWorld(win.getMousePos());
		if (pointInBox(	glm::vec4{ m_pos.x,m_pos.y,m_totalWidth,m_height }, 
						mouseCoords)) {
			//std::lower_bound(m_buttons.begin(),m_buttons.end(),mouseCoords.x,[](){})
		}
	};
private:	 
	struct buttony{
		std::string text;
		double width;
		rawry::holder fn;
	};
	glm::vec2 m_pos = {};
	double m_height = 0;
	std::vector<buttony> m_buttons;
	int m_totalWidth = 0;
};


