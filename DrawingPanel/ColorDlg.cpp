// ColorDlg.cpp: 实现文件
//

#include "pch.h"
#include "DrawingPanel.h"
#include "ColorDlg.h"
#include "afxdialogex.h"


// CColorDlg 对话框

IMPLEMENT_DYNAMIC(CColorDlg, CDialog)

CColorDlg::CColorDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SETCOLOR, pParent)
	, clr_r(0)
	, clr_g(0)
	, clr_b(0)
{

}

CColorDlg::CColorDlg(int r, int g, int b) :CDialog(IDD_SETCOLOR, nullptr)
{
	this->clr_r = r;
	this->clr_g = g;
	this->clr_b = b;
}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COLOR_R, clr_r);
	DDX_Text(pDX, IDC_COLOR_G, clr_g);
	DDX_Text(pDX, IDC_COLOR_B, clr_b);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialog)
END_MESSAGE_MAP()


// CColorDlg 消息处理程序
