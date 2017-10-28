#pragma once
#include "drawableObj.h"

class Rectangle:public drawableObj {
public:
	static const texture& getFlatColor() {
		if (!Loaded) {
			flatColor = imgLoader::loadPNG("blank.png");
			Loaded = true;
		}
		return flatColor;
	};
	Rectangle() = default;
	Rectangle(glm::vec4,Color);
	//void draw(drawRenderer& r) const override;
private:
	static bool Loaded;
	static texture flatColor;
};
