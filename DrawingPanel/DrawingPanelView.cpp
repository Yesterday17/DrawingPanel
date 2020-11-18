
// DrawingPanelView.cpp: CDrawingPanelView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DrawingPanel.h"
#endif

#include "DrawingPanelDoc.h"
#include "DrawingPanelView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "ColorDlg.h"
#include "CubeDlg.h"
#include "Shape.h"
#include "ShapeInfinity.h"
#include "MainFrm.h"


// CDrawingPanelView

IMPLEMENT_DYNCREATE(CDrawingPanelView, CView)

BEGIN_MESSAGE_MAP(CDrawingPanelView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DRAW_SET_COLOR, &CDrawingPanelView::OnDrawSetColor)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_CIRCLE, &CDrawingPanelView::OnCircle)
	ON_COMMAND(ID_POINT, &CDrawingPanelView::OnPoint)
	ON_COMMAND(ID_LINE, &CDrawingPanelView::OnLine)
	ON_COMMAND(ID_OVAL, &CDrawingPanelView::OnOval)
	ON_COMMAND(ID_POLYGON, &CDrawingPanelView::OnPolygon)
	ON_COMMAND(ID_NEWCUBE, &CDrawingPanelView::OnCube)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_FILE_NEW, &CDrawingPanelView::OnFileNew)
END_MESSAGE_MAP()

// CDrawingPanelView 构造/析构

CDrawingPanelView::CDrawingPanelView() noexcept : clr_r(0), clr_g(0), clr_b(0), shape(ShapeType::None), painting(nullptr)
{
	//UpdateStatus();
}

CDrawingPanelView::~CDrawingPanelView()
{
}

BOOL CDrawingPanelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDrawingPanelView 绘图

void CDrawingPanelView::OnDraw(CDC* /*pDC*/)
{
	CDrawingPanelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	auto pDC = this->GetDC();
	for (int i = 0; i < objects.GetSize(); i++) {
		auto obj = (Shape*)objects.GetAt(i);
		obj->Draw(pDC);
	}
}


// CDrawingPanelView 打印

BOOL CDrawingPanelView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawingPanelView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawingPanelView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDrawingPanelView 诊断

#ifdef _DEBUG
void CDrawingPanelView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawingPanelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawingPanelDoc* CDrawingPanelView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawingPanelDoc)));
	return (CDrawingPanelDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawingPanelView 消息处理程序

void CDrawingPanelView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);

	if (painting == nullptr) {
		painting = ShapeFactory::Create(shape);
		painting->SetColor(RGB(clr_r, clr_g, clr_b));
		if (painting->NeedCapture()) {
			this->SetCapture();
		}
	}
	painting->AddPoint(point);
	if (painting->Draw(&dc)) {
		objects.Add(painting);
		if (painting->NeedCapture()) {
			ReleaseCapture();
		}
		// delete painting;
		painting = nullptr;
	}

	CView::OnLButtonDown(nFlags, point);
}


void CDrawingPanelView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (painting != nullptr) {
		CDC* pDC = this->GetDC();
		painting->Preview(pDC, point);
	}
	CView::OnMouseMove(nFlags, point);
}

void CDrawingPanelView::UpdateStatus()
{
	CString* pString = new CString;
	*pString = ShapeTypeToCString(shape);
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_SET_STATUS, 0, reinterpret_cast<LPARAM>(pString));
}

void CDrawingPanelView::OnPoint()
{
	shape = ShapeType::Point;
	UpdateStatus();
}

void CDrawingPanelView::OnLine()
{
	shape = ShapeType::Line;
	UpdateStatus();
}

void CDrawingPanelView::OnCircle()
{
	shape = ShapeType::Circle;
	UpdateStatus();
}

void CDrawingPanelView::OnOval()
{
	shape = ShapeType::Oval;
	UpdateStatus();
}

void CDrawingPanelView::OnCube()
{
	shape = ShapeType::Cube;
	UpdateStatus();
}


void CDrawingPanelView::OnPolygon()
{
	shape = ShapeType::Polygon;
	UpdateStatus();
}


void CDrawingPanelView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (painting != nullptr) {
		ShapeInfinity* inf = dynamic_cast<ShapeInfinity*>(painting);
		if (inf != nullptr) {
			inf->Finish();
			CClientDC dc(this);
			painting->Draw(&dc);
			objects.Add(painting);
			//delete painting;
			painting = nullptr;
			ReleaseCapture();
		}
	}
	CView::OnLButtonDblClk(nFlags, point);
}


void CDrawingPanelView::OnFileNew()
{
	Invalidate();
	for (int i = 0; i < objects.GetSize(); i++) {
		delete objects.GetAt(i);
	}
	objects.RemoveAll();
}

void CDrawingPanelView::OnDrawSetColor()
{
	CColorDlg dlg(this->clr_r, this->clr_g, this->clr_b);
	if (dlg.DoModal() == IDOK) {
		// Update color
		clr_r = dlg.clr_r;
		clr_g = dlg.clr_g;
		clr_b = dlg.clr_b;
		if (painting != nullptr) {
			painting->SetColor(RGB(clr_r, clr_g, clr_b));
		}
	}
}

