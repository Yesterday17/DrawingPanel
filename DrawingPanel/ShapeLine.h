#pragma once
#include "Shape.h"
class ShapeLine : public Shape
{
	// ͨ�� Shape �̳�
	virtual bool Draw(CDC* pDC) override;
	virtual void Preview(CDC* pDC, CPoint p) override;
};
