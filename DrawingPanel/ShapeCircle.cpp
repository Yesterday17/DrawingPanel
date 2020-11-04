#include "pch.h"
#include "ShapeCircle.h"

bool ShapeCircle::Draw(CDC* pDC)
{
	if (points.GetSize() == 2) {
		BresenhamCircle(pDC, points.GetAt(0), points.GetAt(1), color);
		return true;
	}
	return false;
}

void ShapeCircle::Preview(CDC* pDC, CPoint p)
{
	assert(points.GetSize() == 1);
	if (lastPoint != nullptr) {
		pDC->SetROP2(R2_NOT);
		BresenhamCircle(pDC, points.GetAt(0), *lastPoint, color);
		delete lastPoint;
	}
	BresenhamCircle(pDC, points.GetAt(0), p, color);
	lastPoint = new CPoint(p.x, p.y);
}
