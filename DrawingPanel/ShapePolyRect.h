#pragma once
#include "Shape.h"
#include "ShapeInfinity.h"
class ShapePolyRect : public Shape, ShapeInfinity
{
	// ͨ�� Shape �̳�
	virtual bool Draw(CDC* pDC) override;
	virtual void Preview(CDC* pDC, CPoint p) override;
};

