// CubeDlg.cpp: 实现文件
//

#include "pch.h"
#include "DrawingPanel.h"
#include "CubeDlg.h"
#include "afxdialogex.h"
#include "utils.h"
#include <cmath>

// CubeDlg 对话框

IMPLEMENT_DYNAMIC(CCubeDlg, CDialogEx)

CCubeDlg::CCubeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEWCUBE, pParent)
	, pX(0)
	, pY(0)
	, pZ(300)
	, rParrel(FALSE)
{

}

CCubeDlg::~CCubeDlg()
{
}

void CCubeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PERSPECTIVE_X, pX);
	DDX_Text(pDX, IDC_PERSPECTIVE_Y, pY);
	DDX_Text(pDX, IDC_PERSPECTIVE_Z, pZ);
	DDX_Radio(pDX, IDC_RADIO_PARALLEL, rParrel);
	DDX_Control(pDX, IDC_PERSPECTIVE_X, pxEdit);
	DDX_Control(pDX, IDC_PERSPECTIVE_Y, pyEdit);
	DDX_Control(pDX, IDC_PERSPECTIVE_Z, pzEdit);
	DDX_Control(pDX, IDC_BUTTON_PERSPECTIVE, pSubmit);
}


BEGIN_MESSAGE_MAP(CCubeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_RADIO_PARALLEL, &CCubeDlg::OnBnClickedRadioParallel)
	ON_BN_CLICKED(IDC_RADIO_PERSPECTIVE, &CCubeDlg::OnBnClickedRadioParallel)
	ON_BN_CLICKED(IDC_BUTTON_PERSPECTIVE, &CCubeDlg::OnClickedButtonPerspective)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CCubeDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


void CCubeDlg::MultiplyMatrixTo(const float mul[][4], float to[][4])
{
	float tmp[4][4];
	memcpy(tmp, to, sizeof(float) * 16);
	MatrixMultiply(tmp, mul, to);
}

void CCubeDlg::OnPaint()
{
	CPaintDC dc(this);
	cube.Draw(&dc, CPoint(0, 0));
}


BOOL CCubeDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta > 0) {
		cube.ScaleMatrix[0][0] *= 1.1f;
		cube.ScaleMatrix[1][1] *= 1.1f;
		cube.ScaleMatrix[2][2] *= 1.1f;
	}
	else {
		cube.ScaleMatrix[0][0] *= 0.9f;
		cube.ScaleMatrix[1][1] *= 0.9f;
		cube.ScaleMatrix[2][2] *= 0.9f;
	}
	Invalidate();
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

POJOCube::POJOCube()
{
	float alpha = atan(1); // pi / 4
	ProjMatrix[2][2] = 0;
	ProjMatrix[2][0] = 0.5 * cos(alpha);
	ProjMatrix[2][1] = 0.5 * sin(alpha);
}

/*
	bool shouldDraw[6] = { true,true,true,true,true,true };
	for (int face = 0; face < 6; face++) {
		float tmpPoly[4][3];
		for (int vert = 0; vert < 4; vert++) {
			for (int k = 0; k < 3; k++) {
				tmpPoly[vert][k] = CubeVerts[CubeFaces[face][vert]][k];
			}
		}

		// 计算 Normal
		float normal[3];
		const float P12[3] = { tmpPoly[2][0] - tmpPoly[1][0],tmpPoly[2][1] - tmpPoly[1][1], tmpPoly[2][2] - tmpPoly[1][2] };
		const float P10[3] = { tmpPoly[0][0] - tmpPoly[1][0],tmpPoly[0][1] - tmpPoly[1][1], tmpPoly[0][2] - tmpPoly[1][2] };
		CrossPruduct(P12, P10, normal);
		float len = DotProduct(normal, normal);
		normal[0] /= len;
		normal[1] /= len;
		normal[2] /= len;

		// 计算 viewDir
		float viewDir3[3];
		float viewDir2[4];
		viewDir2[0] = -0.5;
		viewDir2[1] = -0.5;
		viewDir2[2] = 1.;
		viewDir2[3] = 1.;
		viewDir3[0] = viewDir2[0] / viewDir2[3];
		viewDir3[1] = viewDir2[1] / viewDir2[3];
		viewDir3[2] = viewDir2[2] / viewDir2[3];
		len = DotProduct(viewDir3, viewDir3);
		viewDir3[0] /= len;
		viewDir3[1] /= len;
		viewDir3[2] /= len;

		float dot = DotProduct(viewDir3, normal);
		if (dot > 0)
			shouldDraw[face] = true;
		else
			shouldDraw[face] = false;
	}
*/

void POJOCube::Draw(CDC* pDC, CPoint offset)
{
	// Transforms
	float CubeVerts[8][4];
	for (int vert = 0; vert < 8; vert++) {
		float tmpVec[4];
		VectorMatrixMultiply(this->CubeVerts[vert], ScaleMatrix, tmpVec);
		float tmpVec2[4];
		VectorMatrixMultiply(tmpVec, RotateMatrix, tmpVec2);
		VectorMatrixMultiply(tmpVec2, TransformMatrix, CubeVerts[vert]);
	}

	CPoint CubeVerts2D[8];
	for (int i = 0; i < 8; i++) {
		CubeVerts2D[i] = Proj(CubeVerts[i], ProjMatrix);
		CubeVerts2D[i].x += offset.x;
		CubeVerts2D[i].y += offset.y;
	}

	for (int face = 0; face < 6; face++) {
		pDC->MoveTo(CubeVerts2D[CubeFaces[face][0]]);
		for (int vert = 1; vert < 4; vert++) {
			pDC->LineTo(CubeVerts2D[CubeFaces[face][vert]]);
		}
		pDC->LineTo(CubeVerts2D[CubeFaces[face][0]]);
	}
}

BOOL CCubeDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (CCubeDlg::OnKeyDown(pMsg->wParam)) {
			return 1;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


bool CCubeDlg::OnKeyDown(UINT nChar)
{
	static const float theta = 2.0f / 180 * (float)atan(1) * 4;
	if (GetKeyState(VK_CONTROL) & 0x80) {
		// Ctrl+Key, rotate
		switch (nChar) {
		case VK_UP: {
			float transform[4][4] = {
				{1,0,0,0},
				{0,cos(theta),sin(theta),0},
				{0,-sin(theta),cos(theta),0},
				{0,0,0,1}
			};
			MultiplyMatrixTo(transform, cube.RotateMatrix);
			break;
		}
		case VK_DOWN: {
			float transform[4][4] = {
				{1,0,0,0},
				{0,cos(-theta),sin(-theta),0},
				{0,-sin(-theta),cos(-theta),0},
				{0,0,0,1}
			};
			MultiplyMatrixTo(transform, cube.RotateMatrix);
			break;
		}
		case VK_LEFT: {
			float transform[4][4] = {
				{cos(-theta),0,-sin(-theta),0},
				{0,1,0,0},
				{sin(-theta),0,cos(-theta),0},
				{0,0,0,1}
			};
			MultiplyMatrixTo(transform, cube.RotateMatrix);
			break;
		}
		case VK_RIGHT: {
			float transform[4][4] = {
				{cos(theta),0,-sin(theta),0},
				{0,1,0,0},
				{sin(theta),0,cos(theta),0},
				{0,0,0,1}
			};
			MultiplyMatrixTo(transform, cube.RotateMatrix);
			break;
		}
		case VK_PRIOR: { // Page Up
			float transform[4][4] = {
				{cos(-theta),sin(-theta),0,0},
				{-sin(-theta),cos(-theta),0,0},
				{0,0,1,0},
				{0,0,0,1}
			};
			MultiplyMatrixTo(transform, cube.RotateMatrix);
			break;
		}
		case VK_NEXT: {// Page Down
			float transform[4][4] = {
				{cos(theta),sin(theta),0,0},
				{-sin(theta),cos(theta),0,0},
				{0,0,1,0},
				{0,0,0,1}
			};
			MultiplyMatrixTo(transform, cube.RotateMatrix);
			break;
		}
		default:
			return false;
		}
	}
	else {
		// Only Key, move
		switch (nChar) {
		case VK_UP:
			cube.TransformMatrix[3][1] -= 10;
			break;
		case VK_DOWN:
			cube.TransformMatrix[3][1] += 10;
			break;
		case VK_LEFT:
			cube.TransformMatrix[3][0] -= 10;
			break;
		case VK_RIGHT:
			cube.TransformMatrix[3][0] += 10;
			break;
		case VK_PRIOR: // Page Up
			cube.TransformMatrix[3][2] -= 10;
			break;
		case VK_NEXT: // Page Down
			cube.TransformMatrix[3][2] += 10.;
			break;
		default:
			return false;
		}
	}
	Invalidate();
	return true;
}

void CCubeDlg::OnBnClickedRadioParallel()
{
	UpdateData(TRUE);
	switch (rParrel) {
	case 0: {
		// 禁用透视投影参数框
		pxEdit.EnableWindow(FALSE);
		pyEdit.EnableWindow(FALSE);
		pzEdit.EnableWindow(FALSE);
		pSubmit.EnableWindow(FALSE);

		// 平行投影
		float alpha = atan(1); // pi / 4
		memcpy(cube.ProjMatrix, cube.IdentityMatrix, sizeof(float) * 16);
		cube.ProjMatrix[2][2] = 0;
		cube.ProjMatrix[2][0] = 0.5 * cos(alpha);
		cube.ProjMatrix[2][1] = 0.5 * sin(alpha);
		Invalidate();
		break;
	}
	case 1:
		// 开始准备透视投影的参数
		pxEdit.EnableWindow(TRUE);
		pyEdit.EnableWindow(TRUE);
		pzEdit.EnableWindow(TRUE);
		pSubmit.EnableWindow(TRUE);
		break;
	}
}


void CCubeDlg::OnClickedButtonPerspective()
{
	UpdateData(TRUE);
	memcpy(cube.ProjMatrix, cube.IdentityMatrix, sizeof(float) * 16);

	const float d = -pZ;
	cube.ProjMatrix[2][0] = pX / d;
	cube.ProjMatrix[2][1] = pY / d;
	cube.ProjMatrix[2][2] = 0;
	cube.ProjMatrix[2][3] = 1 / d;
	Invalidate();
}


void CCubeDlg::OnBnClickedButtonReset()
{
	// TODO
	cube = POJOCube();
	Invalidate();
}
