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
};

CString ShapeTypeToCString(ShapeType t);

class ShapeFactory
{
public:
	static Shape* Create(ShapeType shape);
};
