#include "pch.h"
#include "ShapePolyRect.h"

bool ShapePolyRect::Draw(CDC* pDC)
{
	if (points.GetSize() > 3 && isFinished()) {
		// First two points are rectangle points
		CPoint first = points.GetAt(0), second = points.GetAt(1);
		pDC->Rectangle(first.x, first.y, second.x, second.y);

		// Then draw Polygon
		for (int i = 1; i < points.GetSize() - 2; i++) {
			DDALine(pDC, points.GetAt(i - 1), points.GetAt(i), color);
		}
		DDALine(pDC, points.GetAt(points.GetSize() - 1), points.GetAt(2), color);
		return true;
	}
	return false;
}

void ShapePolyRect::Preview(CDC* pDC, CPoint p)
{
	if (points.GetSize() == 1) {
		// Preview Rectangle
		CPoint first = points.GetAt(0);
		if (lastPoint != nullptr) {
			pDC->SetROP2(R2_NOT);
			pDC->Rectangle(first.x, first.y, lastPoint->x, lastPoint->y);
			delete lastPoint;
		}
		pDC->Rectangle(first.x, first.y, p.x, p.y);
		lastPoint = new CPoint(p.x, p.y);
	}
	else if (points.GetSize() == 2) {
		// No preview
	}
	else {
		// >= 3 points
		auto prev = points.GetAt(points.GetSize() - 1);
		if (lastPoint != nullptr) {
			pDC->SetROP2(R2_NOT);
			DDALine(pDC, prev, *lastPoint, color);
			delete lastPoint;
		}
		DDALine(pDC, prev, p, color);
		lastPoint = new CPoint(p.x, p.y);
	}
}
