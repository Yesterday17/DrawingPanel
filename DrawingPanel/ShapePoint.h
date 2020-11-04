#pragma once
#include "Shape.h"
class ShapePoint : public Shape
{
	// 通过 Shape 继承
	virtual bool Draw(CDC* pDC) override;

	// 通过 Shape 继承
	virtual void Preview(CDC* pDC, CPoint p) override;
};

