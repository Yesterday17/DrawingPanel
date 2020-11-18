#include "pch.h"
#include "ShapeCube.h"

bool ShapeCube::Draw(CDC* pDC)
{
	if (!finished) {
		CCubeDlg dlg;
		if (dlg.DoModal() == IDOK) {
			cube = dlg.cube;
			// TODO: ����������
			// FIXME: ������� false �ĳ� true
			return false;
		}
		else {
			points.RemoveAll();
			return false;
		}
	}
	else {
		// TODO: ����������
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
