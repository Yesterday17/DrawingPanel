#include "pch.h"
#include "ShapeOval.h"

bool ShapeOval::Draw(CDC* pDC)
{
	if (points.GetSize() == 3) {
		MidpointEllipse(pDC, color, points.GetAt(0), points.GetAt(1), points.GetAt(2));
		return true;
	}
	return false;
}

void ShapeOval::Preview(CDC* pDC, CPoint p)
{
	CPoint p1;

	if (lastPoint != nullptr) {
		pDC->SetROP2(R2_NOT);
		if (points.GetSize() == 1) {
			int R = distance(points.GetAt(0), *lastPoint);
			MidpointEllipse(pDC, color, points.GetAt(0), *lastPoint, CPoint(points.GetAt(0).x, points.GetAt(0).y - R));
		}
		else {
			MidpointEllipse(pDC, color, points.GetAt(0), points.GetAt(1), *lastPoint);
		}
		delete lastPoint;
	}
	if (points.GetSize() == 1) {
		int R = distance(points.GetAt(0), p);
		MidpointEllipse(pDC, color, points.GetAt(0), p, CPoint(points.GetAt(0).x, points.GetAt(0).y - R));
	}
	else {
		MidpointEllipse(pDC, color, points.GetAt(0), points.GetAt(1), p);
	}
	lastPoint = new CPoint(p.x, p.y);
}
