#pragma once
#include "Shape.h"
class ShapePoint : public Shape
{
	// ͨ�� Shape �̳�
	virtual bool Draw(CDC* pDC) override;

	// ͨ�� Shape �̳�
	virtual void Preview(CDC* pDC, CPoint p) override;
};

