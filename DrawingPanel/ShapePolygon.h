#pragma once
#include "Shape.h"
class ShapePolygon : public Shape
{
	// Í¨¹ý Shape ¼Ì³Ð
	virtual bool Draw(CDC* pDC) override;
	virtual void Preview(CDC* pDC, CPoint p) override;
public:
	ShapePolygon();
private:
	bool s_mask[MAX_X][MAX_Y];
	bool dda_mask[MAX_X][MAX_Y];

	void PrepareMask();
	void PrepareDDALine(CPoint start, CPoint end);
	void PrepareLineMask();
	void Fill(CDC* pDC);
};
