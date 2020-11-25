#pragma once
#include "Shape.h"
#include "ShapeInfinity.h"
class ShapePolyRect : public Shape, ShapeInfinity
{
	// Í¨¹ý Shape ¼Ì³Ð
	virtual bool Draw(CDC* pDC) override;
	virtual void Preview(CDC* pDC, CPoint p) override;
};

