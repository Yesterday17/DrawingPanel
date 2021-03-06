#pragma once
#include "utils.h"
constexpr auto MAX_X = 4096;
constexpr auto MAX_Y = 4096;

typedef CArray<CPoint, CPoint> CPArray;

class Shape : public CObject
{
protected:
	CPArray points;
	COLORREF color;
	CPoint* lastPoint;

public:
	Shape();
	virtual ~Shape();

	void AddPoint(CPoint);
	void SetColor(COLORREF);
	virtual bool Draw(CDC* pDC) = 0;
	virtual void Preview(CDC* pDC, CPoint p) = 0;
	virtual bool NeedCapture();
};
