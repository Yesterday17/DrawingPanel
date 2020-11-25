#pragma once
#include "Shape.h"

enum class ShapeType {
	None,
	Point,
	Line,
	Circle,
	Oval,
	Polygon,
	Cube,
	PolyRect,
};

CString ShapeTypeToCString(ShapeType t);

class ShapeFactory
{
public:
	static Shape* Create(ShapeType shape);
};
