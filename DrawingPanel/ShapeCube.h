#pragma once
#include "Shape.h"
#include "CubeDlg.h"
class ShapeCube : public Shape
{
	// 通过 Shape 继承
	virtual bool Draw(CDC* pDC) override;
	virtual void Preview(CDC* pDC, CPoint p) override;
	virtual bool NeedCapture() override;

public:
	ShapeCube();

private:
	// 完成配置
	bool finished;
	POJOCube cube;
};

