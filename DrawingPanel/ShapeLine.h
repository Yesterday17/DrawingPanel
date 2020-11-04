#pragma once
#include "Shape.h"
class ShapeLine : public Shape
{
	// Í¨¹ý Shape ¼Ì³Ð
	virtual bool Draw(CDC* pDC) override;
	virtual void Preview(CDC* pDC, CPoint p) override;
};
