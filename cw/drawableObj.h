#ifndef DRAWABLEOBJ_H
#define DRAWABLEOBJ_H
#include "renderer.h"
#include <string>
#include "texture.h"
#include "resourceManager.h"
#include "iDrawable.h"
#include "mathStuff.h"
const glm::vec4 fullPicUV = { 0.0f,0.0f,1.0f,1.0f };
class drawableObj;

class drawRenderer :public renderer {
public:
	drawRenderer();
	virtual void draw(const drawableObj*);
	virtual void draw(const drawableObj&);
	virtual void draw(const glm::vec4, const glm::vec4, const GLuint, const Color, GLfloat);
	virtual void draw(const glm::vec4, const glm::vec4, const GLuint, const Color, GLfloat,math::radians);
	void render(const camera2D& cam) override;
	friend class drawableObj;

};
//for things that don't need to be drawn weird

class drawableObj:public iDrawable
{
    public:
        drawableObj(glm::vec4&&,const std::string& file,Color = { 255,255,255,255 });
        drawableObj(glm::vec4&,const std::string& file, Color = { 255,255,255,255 });

		drawableObj(glm::vec4&&, const texture& file, Color = {255,255,255,255});
		drawableObj(glm::vec4&, const texture& file, Color = { 255,255,255,255 });
        drawableObj() = default;
        void init(glm::vec4,const std::string& file);
        //virtual ~drawableObj() = default;
        void move(glm::vec2);
        glm::vec2 getSpot()const{return glm::vec2(m_dims.x,m_dims.y);};
		virtual void draw(drawRenderer&)const;
    protected:
		Color m_color;
        texture m_texture;
        //void setUVs(glm::vec4);
        glm::vec4 m_dims;
		glm::vec4 m_uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    private:
        friend class drawRenderer;//so i can do drawRenderer.draw(obj);
};


#endif // DRAWABLEOBJ_H
