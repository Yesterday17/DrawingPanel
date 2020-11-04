#include "pch.h"
#include "ShapePolygon.h"

ShapePolygon::ShapePolygon()
{
	memset(s_mask, 0, MAX_X * MAX_Y);
	memset(dda_mask, 0, MAX_X * MAX_Y);
}

void ShapePolygon::PrepareMask() {
	for (int i = 0; i < points.GetSize(); i++)
	{
		CPoint pt0 = points.GetAt((i + points.GetSize() - 1) % points.GetSize());

		CPoint pt1 = points.GetAt(i);
		CPoint pt2 = points.GetAt((i + 1) % points.GetSize());

		double dxs, dys, xs, ys;
		xs = pt1.x;
		dxs = (double)(pt2.x - pt1.x) / (pt2.y - pt1.y);
		dys = fabs((pt2.y - pt1.y)) / (pt2.y - pt1.y);

		for (ys = pt1.y; ys != pt2.y; ys += dys)
		{
			s_mask[(int)ys][(int)(xs + 0.5)] = !s_mask[(int)ys][(int)(xs + 0.5)];
			xs += (dxs * dys);
		}

		if ((pt1.y <= pt0.y && pt1.y <= pt2.y) || (pt1.y >= pt0.y && pt1.y >= pt2.y))
		{
			s_mask[pt1.y][pt1.x] = false;
		}
	}
}

void ShapePolygon::PrepareDDALine(CPoint start, CPoint end)
{
	double dx, dy, e, x, y;
	dx = end.x - start.x;
	dy = end.y - start.y;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	dx /= e;
	dy /= e;
	x = start.x;
	y = start.y;
	for (int i = 1; i <= e; i++)
	{
		dda_mask[(int)(y + 0.5)][(int)(x + 0.5)] = true;
		x += dx;
		y += dy;
	}
}

void ShapePolygon::PrepareLineMask() {
	for (int i = 1; i < points.GetSize(); i++) {
		PrepareDDALine(points.GetAt(i - 1), points.GetAt(i));
	}
	PrepareDDALine(points.GetAt(points.GetSize() - 1), points.GetAt(0));
}

void ShapePolygon::Fill(CDC* pDC) {
	int x, y;
	for (y = 0; y < MAX_Y; y++)
	{
		bool inside = false;
		int ptscnt = 0;

		for (x = 0; x < MAX_X; x++)
		{
			if (s_mask[y][x])
				inside = !inside;
			if (inside && !dda_mask[y][x])
				pDC->SetPixel(x, y, ThonkColor(x, y));
		}
	}
}

bool ShapePolygon::Draw(CDC* pDC)
{
	for (int i = 1; i < points.GetSize(); i++) {
		DDALine(pDC, points.GetAt(i - 1), points.GetAt(i), color);
	}
	// TODO: Any edges
	if (points.GetSize() == 4) {
		DDALine(pDC, points.GetAt(points.GetSize() - 1), points.GetAt(0), color);
		PrepareMask();
		PrepareLineMask();
		Fill(pDC);
		return true;
	}
	return false;
}

void ShapePolygon::Preview(CDC* pDC, CPoint p)
{
	auto prev = points.GetAt(points.GetSize() - 1);
	if (lastPoint != nullptr) {
		pDC->SetROP2(R2_NOT);
		DDALine(pDC, prev, *lastPoint, color);
		delete lastPoint;
	}
	DDALine(pDC, prev, p, color);
	lastPoint = new CPoint(p.x, p.y);
}
