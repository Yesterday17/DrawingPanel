#include "pch.h"
#include "ShapeCircle.h"
#include <cmath>

void BresenhamCircle(CDC* pDC, CPoint start, CPoint next, COLORREF color) {
	double xx = next.x - start.x;
	double yy = next.y - start.y;
	double R = sqrt(xx * xx + yy * yy);

	int x = 0;
	int y = R;
	int p = 3 - 2 * R;

	for (; x <= y; x++) {
		pDC->SetPixel(CPoint(x + start.x, y + start.y), color);
		pDC->SetPixel(CPoint(-x + start.x, y + start.y), color);
		pDC->SetPixel(CPoint(x + start.x, -y + start.y), color);
		pDC->SetPixel(CPoint(-x + start.x, -y + start.y), color);
		pDC->SetPixel(CPoint(y + start.x, x + start.y), color);
		pDC->SetPixel(CPoint(-y + start.x, x + start.y), color);
		pDC->SetPixel(CPoint(y + start.x, -x + start.y), color);
		pDC->SetPixel(CPoint(-y + start.x, -x + start.y), color);
		if (p >= 0) {
			p += 4 * (x - y) + 10;
			y--;
		}
		else {
			p += 4 * x + 6;
		}
	}
}

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
