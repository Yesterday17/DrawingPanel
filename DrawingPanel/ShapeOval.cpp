#include "pch.h"
#include "ShapeOval.h"

int distance(CPoint a, CPoint b) {
	double x = a.x - b.x;
	double y = a.y - b.y;
	return sqrt(x * x + y * y);
}

void MidpointEllipse(CDC* pDC, COLORREF color, CPoint center, CPoint a, CPoint b) {
	int aa = distance(a, center), bb = distance(b, center);
	int x = 0, y = bb;
	double d1 = bb * bb + aa * aa * (-bb + 0.25);
	pDC->SetPixel(CPoint(x + center.x, y + center.y), color);
	pDC->SetPixel(CPoint(-x + center.x, y + center.y), color);
	pDC->SetPixel(CPoint(x + center.x, -y + center.y), color);
	pDC->SetPixel(CPoint(-x + center.x, -y + center.y), color);
	while (bb * bb * (x + 1) < aa * aa * (y - 0.5)) {
		if (d1 < 0) {
			d1 += bb * bb * (2 * x + 3);
			x++;
		}
		else {
			d1 += (bb * bb * (2 * x + 3) + aa * aa * (-2 * y + 2));
			x++;
			y--;
		}
		pDC->SetPixel(CPoint(x + center.x, y + center.y), color);
		pDC->SetPixel(CPoint(-x + center.x, y + center.y), color);
		pDC->SetPixel(CPoint(x + center.x, -y + center.y), color);
		pDC->SetPixel(CPoint(-x + center.x, -y + center.y), color);
	}
	double d2 = bb * bb * (x + 0.5) * (x + 0.5) + aa * aa * (y - 1) * (y - 1) - aa * aa * bb * bb;
	while (y > 0) {
		if (d2 < 0) {
			d2 += bb * bb * (2 * x + 2) + aa * aa * (-2 * y + 3);
			x++;
			y--;
		}
		else {
			d2 += aa * aa * (-2 * y + 3);
			y--;
		}
		pDC->SetPixel(CPoint(x + center.x, y + center.y), color);
		pDC->SetPixel(CPoint(-x + center.x, y + center.y), color);
		pDC->SetPixel(CPoint(x + center.x, -y + center.y), color);
		pDC->SetPixel(CPoint(-x + center.x, -y + center.y), color);
	}
}

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
