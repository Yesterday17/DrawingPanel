#include "pch.h"
#include "ShapeLine.h"

bool ShapeLine::Draw(CDC* pDC)
{
	if (points.GetSize() == 2) {
		DDALine(pDC, points.GetAt(0), points.GetAt(1), color);
		return true;
	}
	return false;
}

void ShapeLine::Preview(CDC* pDC, CPoint p)
{
	assert(points.GetSize() == 1);
	if (lastPoint != nullptr) {
		pDC->SetROP2(R2_NOT);
		DDALine(pDC, points.GetAt(0), *lastPoint, color);
		delete lastPoint;
	}
	DDALine(pDC, points.GetAt(0), p, color);
	lastPoint = new CPoint(p.x, p.y);
}
