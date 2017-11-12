#ifndef DRAWABLEOBJ_H
#define DRAWABLEOBJ_H
#include "renderer.h"
#include <string>
#include "texture.h"
#include "resourceManager.h"
#include "mathStuff.h"
#include "Drawable.h"
const glm::vec4 defaultUV = { 0.0f,0.0f,1.0f,1.0f };
class drawableObj;


class drawRenderer :public renderer<drawRenderer>,private SpriteBatch {
public:
	drawRenderer();
	/*
	void draw(glm::vec4 dimensions, glm::vec4 uv, GLuint text, Color colour, float depth, math::radians angle, glm::vec2 offSetAfterRotation);
	void draw(glm::vec4 dimensions, glm::vec4 uv, GLuint text, Color colour, float depth, math::radians angle);
	void draw(glm::vec4 dimensions, glm::vec4 uv, GLuint text, Color colour, float depth, glm::vec2 dir);
	void draw(glm::vec4 dimensions, glm::vec4 uv, GLuint text, Color colour, float depth);
	*/
	using SpriteBatch::draw;
	/*
	void draw(const drawableObj*);
	void draw(const drawableObj&);
	*/
	template<typename type>
	void drawObj(const Drawable<type>& item) {
		item.draw(*this);
	};
	
	void Render(const camera2D& cam);
	friend class drawableObj;
private:
	GLSLthingy glslProg;
	//SpriteBatch spriteB;
};
//for things that don't need to be drawn weird

class drawableObj:public Drawable<drawableObj>
{
    public:
		drawableObj() = default;
        drawableObj(glm::vec4,std::string file,Color = { 255,255,255,255 });
		drawableObj(glm::vec4, texture file, Color = { 255,255,255,255 });

        void init(glm::vec4,const std::string& file);
        void move(glm::vec2);
        glm::vec2 getSpot()const{return glm::vec2(m_dims.x,m_dims.y);};
		void Draw(drawRenderer&)const;
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