#pragma once
#include "Shape.h"
class ShapeCircle : public Shape
{
	// ͨ�� Shape �̳�
	virtual bool Draw(CDC* pDC) override;
	virtual void Preview(CDC* pDC, CPoint p) override;
};

