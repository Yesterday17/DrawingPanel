#pragma once
#include "Shape.h"

enum ShapeType {
	SHAPE_NONE,
	SHAPE_POINT,
	SHAPE_LINE,
	SHAPE_CIRCLE,
	SHAPE_OVAL,
	SHAPE_POLYGON,
};

class ShapeFactory
{
public:
	static Shape* Create(ShapeType shape);
};
