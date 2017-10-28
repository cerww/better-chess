#pragma once
#ifndef VERTEX_H
#define VERTEX_H
#include <GL/glew.h>
#include <vector>

struct Position{
	float x;
    float y;
};

struct Color{
	Color(int aa,int bb,int c,int d=255):r(aa),g(bb),b(c),a(d){};
    Color() = default;
	union {
		struct {
			GLubyte r;
			GLubyte g;
			GLubyte b;
			GLubyte a;
		};
		GLuint i;
	};
};

struct UV{
	GLfloat u;
	GLfloat v;
};
struct Vertex{
    Position pos;
    Color color;
    UV uv;
    void setColour(const Color& colour){
		color.i = colour.i;
    }
    void setUV(const GLfloat &u,const GLfloat &v){
		uv.u=u;
		uv.v=v;
    }
    void setPosition(const float x,const float y){
		pos.x=x;
		pos.y=y;
    }

};
/*
Color RGBcolorabc(int r,int g,int b,int a=255){
Color re;
re.r = r;
re.g = g;
re.b = b;
re.a = a;
return re;
}*/
#endif // VERTEX_H
