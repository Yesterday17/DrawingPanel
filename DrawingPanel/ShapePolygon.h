#pragma once
#include "Shape.h"
#include "ShapeInfinity.h"
class ShapePolygon : public Shape, public ShapeInfinity
{
	// Í¨¹ý Shape ¼Ì³Ð
	virtual bool Draw(CDC* pDC) override;
	virtual void Preview(CDC* pDC, CPoint p) override;
public:
	ShapePolygon();
private:
	bool s_mask[MAX_X][MAX_Y];

	void PrepareMask();
	void ClearMask();
	void Fill(CDC* pDC);
};
