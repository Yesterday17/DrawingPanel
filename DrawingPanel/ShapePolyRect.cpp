#include "pch.h"
#include "ShapePolyRect.h"

CPArray* cut_top(CPArray& rect, CPArray* points)
{
	CPArray* pts = new CPArray();

	int c1, c2;
	int juy2 = max(rect.GetAt(0).y, rect.GetAt(1).y);
	CPoint first = points->GetAt(0), p, last;

	for (int i = 0; i < points->GetSize(); i++) {
		p = points->GetAt(i);

		if (i != 0) {
			c2 = p.y > juy2 ? -1 : 1;
			if (c1 + c2 == 0) {
				CPoint I;
				I.y = juy2;
				I.x = (p.x - last.x) * (I.y - last.y) / (p.y - last.y) + last.x;
				pts->Add(I);
			}
		}

		last = p;
		c1 = last.y > juy2 ? -1 : 1;
		if (last.y <= juy2) {
			pts->Add(last);
		}
	}

	c2 = p.y > juy2 ? -1 : 1;
	if (c1 + c2 == 0) {
		CPoint I;
		I.y = juy2;
		I.x = (first.x - last.x) * (I.y - last.y) / (first.y - last.y) + last.x;
		pts->Add(I);
	}

	delete points;
	return pts;
}

CPArray* cut_right(CPArray& rect, CPArray* points)
{
	CPArray* pts = new CPArray();

	int c1, c2;
	int jux2 = max(rect.GetAt(0).x, rect.GetAt(1).x);
	CPoint first = points->GetAt(0), p, last;

	for (int i = 0; i < points->GetSize(); i++) {
		p = points->GetAt(i);
		if (i != 0) {
			c2 = p.x > jux2 ? -1 : 1;
			if (c1 + c2 == 0) {
				CPoint I;
				I.x = jux2;
				I.y = (p.y - last.y) * (I.x - last.x) / (p.x - last.x) + last.y;
				pts->Add(I);
			}
		}

		last = p;
		c1 = last.x > jux2 ? -1 : 1;
		if (last.x <= jux2) {
			pts->Add(last);
		}
	}

	c2 = p.x > jux2 ? -1 : 1;
	if (c1 + c2 == 0) {
		CPoint I;
		I.x = jux2;
		I.y = (first.y - last.y) * (I.x - last.x) / (first.x - last.x) + last.y;
		pts->Add(I);
	}

	delete points;
	return pts;
}

CPArray* cut_bottem(CPArray& rect, CPArray* points)
{
	CPArray* pts = new CPArray();

	int c1, c2;
	int juy1 = min(rect.GetAt(0).y, rect.GetAt(1).y);
	CPoint first = points->GetAt(0), p, last;

	for (int i = 0; i < points->GetSize(); i++) {
		p = points->GetAt(i);
		if (i != 0) {
			c2 = p.y < juy1 ? -1 : 1;
			if (c1 + c2 == 0) {
				CPoint I;
				I.y = juy1;
				I.x = (p.x - last.x) * (I.y - last.y) / (p.y - last.y) + last.x;
				pts->Add(I);
			}
		}
		last = p;
		c1 = last.y < juy1 ? -1 : 1;
		if (last.y >= juy1) {
			pts->Add(last);
		}
	}

	c2 = p.y < juy1 ? -1 : 1;
	if (c1 + c2 == 0) {
		CPoint I;
		I.y = juy1;
		I.x = (first.x - last.x) * (I.y - last.y) / (first.y - last.y) + last.x;
		pts->Add(I);
	}

	delete points;
	return pts;
}

CPArray* cut_left(CPArray& rect, CPArray* points)
{
	CPArray* pts = new CPArray();

	int c1, c2;
	int jux1 = min(rect.GetAt(0).x, rect.GetAt(1).x);
	CPoint first = points->GetAt(0), p, last;

	for (int i = 0; i < points->GetSize(); i++) {
		p = points->GetAt(i);
		if (i != 0) {
			c2 = p.x < jux1 ? -1 : 1;
			if (c1 + c2 == 0) {
				CPoint I;
				I.x = jux1;
				I.y = (p.y - last.y) * (I.x - last.x) / (p.x - last.x) + last.y;
				pts->Add(I);
			}
		}
		last = p;
		c1 = last.x < jux1 ? -1 : 1;
		if (last.x >= jux1) {
			pts->Add(last);
		}
	}

	c2 = p.x < jux1 ? -1 : 1;
	if (c1 + c2 == 0) {
		CPoint I;
		I.x = jux1;
		I.y = (first.y - last.y) * (I.x - last.x) / (first.x - last.x) + last.y;
		pts->Add(I);
	}

	delete points;
	return pts;
}

void CutPoly(CDC* pDC, CPArray& points)
{
	CPArray rect;
	rect.Add(points.GetAt(0));
	rect.Add(points.GetAt(1));

	CPArray* pt = new CPArray();
	pt->Copy(points);
	pt->RemoveAt(0, 2);

	pt->Add(pt->GetAt(0));
	pt = cut_top(rect, pt);

	pt->Add(pt->GetAt(0));
	pt = cut_right(rect, pt);

	pt->Add(pt->GetAt(0));
	pt = cut_bottem(rect, pt);

	pt->Add(pt->GetAt(0));
	pt = cut_left(rect, pt);

	CPen pen(PS_SOLID, 4, RGB(0x99, 0x99, 0xff));
	CPen* op = pDC->SelectObject(&pen);

	pDC->MoveTo(pt->GetAt(0));
	for (int i = 1; i < pt->GetSize(); i++) {
		pDC->LineTo(pt->GetAt(i));
	}

	pDC->SelectObject(op);
	delete pt;
}

bool ShapePolyRect::Draw(CDC* pDC)
{
	if (isFinished()) {
		if (points.GetSize() > 3) {
			// First two points are rectangle points
			CPoint first = points.GetAt(0), second = points.GetAt(1);
			CBrush brush;
			brush.CreateSolidBrush(color);
			pDC->FrameRect(CRect(first, second), &brush);

			// Then draw Polygon
			for (int i = 2; i < points.GetSize() - 1; i++) {
				DDALine(pDC, points.GetAt(i), points.GetAt(i + 1), color);
			}
			DDALine(pDC, points.GetAt(points.GetSize() - 1), points.GetAt(2), color);

			// Finally cut polygon
			CutPoly(pDC, points);
			return true;
		}
		return false;
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
			CRect r(first, *lastPoint);
			pDC->FrameRect(r, 0);
			delete lastPoint;
			lastPoint = nullptr;
		}
		CBrush brush;
		brush.CreateSolidBrush(color);
		pDC->FrameRect(CRect(first, p), &brush);
		lastPoint = new CPoint(p.x, p.y);
	}
	else if (points.GetSize() == 2) {
		// No preview
		if (lastPoint != nullptr) {
			delete lastPoint;
			lastPoint = nullptr;
		}
	}
	else {
		// > 3 points
		auto prev = points.GetAt(points.GetUpperBound());
		if (lastPoint != nullptr) {
			pDC->SetROP2(R2_NOT);
			DDALine(pDC, prev, *lastPoint, color);
			delete lastPoint;
			lastPoint = nullptr;
		}
		DDALine(pDC, prev, p, color);
		lastPoint = new CPoint(p.x, p.y);
	}
}
