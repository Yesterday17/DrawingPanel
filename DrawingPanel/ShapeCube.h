#pragma once
#include "Shape.h"
#include "CubeDlg.h"
class ShapeCube : public Shape
{
	// ͨ�� Shape �̳�
	virtual bool Draw(CDC* pDC) override;
	virtual void Preview(CDC* pDC, CPoint p) override;
	virtual bool NeedCapture() override;

public:
	ShapeCube();

private:
	// �������
	bool finished;
	POJOCube cube;
};

