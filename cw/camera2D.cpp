#include "camera2D.h"

void camera2D::init(int screenWidth,int screenHeight){
    m_screenWidth=screenWidth;
    m_screenHeight=screenHeight;
    m_orthoMat = glm::ortho(0.0f,(float)m_screenWidth,0.0f,(float)m_screenHeight);
}

camera2D::camera2D(int screenWidth, int screenHeight):
	m_screenWidth(screenWidth),
	m_screenHeight(screenHeight),
	m_orthoMat(glm::ortho(0.0f,(float)screenWidth,0.0f,(float)screenHeight)){}

void camera2D::update(){
    if(m_matUpdate){
        //glm::mat4 orthoMat = glm::ortho(0.0f,(float)_screenWidth,0.0f,(float)_screenHeight);

        glm::vec3 translate(-m_pos.x+m_screenWidth/2,-m_pos.y+m_screenHeight/2,0.0f);
        m_camMatrix = glm::translate(m_orthoMat,translate);

        glm::vec3 scale(m_scale,m_scale,0.0f);
        m_camMatrix = glm::scale(glm::mat4(1.0f),scale)*m_camMatrix;

        m_matUpdate=false;
    }
}

glm::vec2 camera2D::scrnToWorld(glm::vec2 screen)const{
	screen.y = m_screenHeight - screen.y;
	screen -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
	screen /= m_scale;
	screen += m_pos;
	return screen;
}

