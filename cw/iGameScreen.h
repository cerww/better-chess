#pragma once
#include <vector>
#include <memory>

class iGameScreen{    
    public:        
    virtual void draw() = 0;
    virtual std::pair<std::vector<int>,std::vector<int>>update() = 0;//things to delete, things to add
};

class screen {
public:
	class base_object {
	public:
		virtual void draw() = 0;
		virtual void update() = 0;
	};
	template<typename T>
	class object:public base_object{
	public:
		void draw() override final{
			m_obj.draw();
		};
		void update() override final{
			m_obj.update();
		};
	private:
		T m_obj;
	};
private:
	std::unique_ptr<base_object> m_obj;
};



