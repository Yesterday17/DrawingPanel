// CubeDlg.cpp: 实现文件
//

#include "pch.h"
#include "DrawingPanel.h"
#include "CubeDlg.h"
#include "afxdialogex.h"


// CubeDlg 对话框

IMPLEMENT_DYNAMIC(CCubeDlg, CDialogEx)

CCubeDlg::CCubeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEWCUBE, pParent)
{

}

CCubeDlg::~CCubeDlg()
{
}

void CCubeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCubeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CubeDlg 消息处理程序


void CCubeDlg::OnPaint()
{
	CPaintDC dc(this);
	cube.Draw(&dc);
}


BOOL CCubeDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta > 0) {
		cube.scale *= 1.1;
	}
	else {
		cube.scale *= 0.9;
	}
	RePaint();
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

void CCubeDlg::RePaint()
{
	Invalidate();
}

void POJOCube::Draw(CDC* pDC)
{
	pDC->LineTo(100 * scale, 100 * scale);
}
