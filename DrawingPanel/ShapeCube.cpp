#include "pch.h"
#include "ShapeCube.h"

bool ShapeCube::Draw(CDC* pDC)
{
	if (!finished) {
		CCubeDlg dlg;
		if (dlg.DoModal() == IDOK) {
			finished = true;
			cube = dlg.cube;
			cube.Draw(pDC, points.GetAt(0));
			return true;
		}
		else {
			points.RemoveAll();
			return false;
		}
	}
	else {
		cube.Draw(pDC, points.GetAt(0));
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
