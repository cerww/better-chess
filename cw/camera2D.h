#ifndef CAMERA2D_H
#define CAMERA2D_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class camera2D
{
    public:
        camera2D() = default;
		camera2D(int screenWidth, int screenHeight);
        //virtual ~camera2D();
        void update();
        void init(int,int);//avoid this if possible
        //setter
        void setPos(glm::vec2 newPos){m_pos = newPos;m_matUpdate=true;}
        void setScale(const float newScale){m_scale = newScale;m_matUpdate=true;}
        //getter
        glm::vec2 getPos()const {return m_pos;}
        float getScale()const{return m_scale;}
        const glm::mat4& getCamMatrix()const{return m_camMatrix;}
        glm::vec2 scrnToWorld(glm::vec2 screenCoords)const;
    protected:

    private:
        int m_screenWidth;
        int m_screenHeight;
        bool m_matUpdate = 1;
        float m_scale = 1.0f;
        glm::vec2 m_pos = glm::vec2(0.0f,0.0f);
        glm::mat4 m_camMatrix = glm::mat4(1.0f);
        glm::mat4 m_orthoMat = glm::mat4(1.0f);
};

#endif // CAMERA2D_H
