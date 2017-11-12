#pragma once
#ifndef VERTEX_H
#define VERTEX_H
#include <cstdint>

struct Position{
	float x;
    float y;
};

struct Color{
	constexpr Color(uint8_t aa,uint8_t bb, uint8_t c, uint8_t d=255):r(aa),g(bb),b(c),a(d){};
    constexpr Color() = default;
	union {
		struct {
			uint8_t r;
			uint8_t g;
			uint8_t b;
			uint8_t a;
		};
		uint32_t i = 0;
	};
};


struct UV{
	float u;
	float v;
};

struct Vertex{
    Position pos;
    Color color;
    UV uv;
    void setColour(Color colour){
		color.i = colour.i;
    }
    void setUV(float u,float v){
		uv.u=u;
		uv.v=v;
    }
    void setPosition(const float x,const float y){
		pos.x=x;
		pos.y=y;
    }

};
namespace colours{
	constexpr Color BLACK(255, 255, 255);
	constexpr Color WHITE(0, 0, 0);
	constexpr Color RED(255, 0, 0);
	constexpr Color GREEN(0, 255, 0);
	constexpr Color BLUE(0, 0, 255);
}

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
