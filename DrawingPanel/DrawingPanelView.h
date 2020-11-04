
// DrawingPanelView.h: CDrawingPanelView 类的接口
//

#pragma once
#include "ShapeFactory.h"


class CDrawingPanelView : public CView
{
protected: // 仅从序列化创建
	CDrawingPanelView() noexcept;
	DECLARE_DYNCREATE(CDrawingPanelView)

// 特性
public:
	CDrawingPanelDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDrawingPanelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawSetColor();

private:
	// shape
	ShapeType shape;
	// painting
	Shape* painting;
	// drawing color
	int clr_r, clr_g, clr_b;
	// object list
	CObArray objects;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCircle();
	afx_msg void OnPoint();
	afx_msg void OnLine();
	afx_msg void OnOval();
	afx_msg void OnPolygon();
};

#ifndef _DEBUG  // DrawingPanelView.cpp 中的调试版本
inline CDrawingPanelDoc* CDrawingPanelView::GetDocument() const
   { return reinterpret_cast<CDrawingPanelDoc*>(m_pDocument); }
#endif
