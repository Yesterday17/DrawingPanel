#include "pch.h"
#include "ShapeCube.h"

bool ShapeCube::Draw(CDC* pDC)
{
	if (!finished) {
		CCubeDlg dlg;
		if (dlg.DoModal() == IDOK) {
			cube = dlg.cube;
			// TODO: 绘制立方体
			// FIXME: 把下面的 false 改成 true
			return false;
		}
		else {
			points.RemoveAll();
			return false;
		}
	}
	else {
		// TODO: 绘制立方体
		return true;
	}
}

void ShapeCube::Preview(CDC* pDC, CPoint p)
{
}

bool ShapeCube::NeedCapture()
{
	return false;
}

ShapeCube::ShapeCube() : finished(false)
{
}
