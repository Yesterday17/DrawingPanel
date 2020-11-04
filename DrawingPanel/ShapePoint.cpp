#include "pch.h"
#include "ShapePoint.h"

bool ShapePoint::Draw(CDC* pDC)
{
	assert(points.GetSize() > 0);
	auto p = points.GetAt(points.GetSize() - 1);
	for (int i = -5; i < 5; i++) {
		for (int j = -5; j < 5; j++) {
			pDC->SetPixel(p.x + i, p.y + j, color);
		}
	}
	return true;
}

void ShapePoint::Preview(CDC* pDC, CPoint p)
{
}
