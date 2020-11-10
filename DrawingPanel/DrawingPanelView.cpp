
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
#include "Shape.h"
#include "ShapeInfinity.h"


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
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CDrawingPanelView 构造/析构

CDrawingPanelView::CDrawingPanelView() noexcept : clr_r(0), clr_g(0), clr_b(0), shape(SHAPE_NONE), painting(nullptr)
{
	// TODO: 在此处添加构造代码
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

	// TODO: 在此处为本机数据添加绘制代码
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


void CDrawingPanelView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);

	if (painting == nullptr) {
		this->SetCapture();
		painting = ShapeFactory::Create(shape);
		painting->SetColor(RGB(clr_r, clr_g, clr_b));
	}
	painting->AddPoint(point);
	if (painting->Draw(&dc)) {
		delete painting;
		painting = nullptr;
		ReleaseCapture();
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

void CDrawingPanelView::OnPoint()
{
	shape = SHAPE_POINT;
}

void CDrawingPanelView::OnLine()
{
	shape = SHAPE_LINE;
}

void CDrawingPanelView::OnCircle()
{
	shape = SHAPE_CIRCLE;
}

void CDrawingPanelView::OnOval()
{
	shape = SHAPE_OVAL;
}


void CDrawingPanelView::OnPolygon()
{
	shape = SHAPE_POLYGON;
}


void CDrawingPanelView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (painting != nullptr) {
		ShapeInfinity* inf = dynamic_cast<ShapeInfinity*>(painting);
		if (inf != nullptr) {
			inf->Finish();
			CClientDC dc(this);
			painting->Draw(&dc);
			delete painting;
			painting = nullptr;
			ReleaseCapture();
		}
	}
	CView::OnLButtonDblClk(nFlags, point);
}
