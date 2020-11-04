#pragma once

int distance(CPoint a, CPoint b);

void DDALine(CDC* pDC, CPoint start, CPoint end, COLORREF color);

void BresenhamCircle(CDC* pDC, CPoint start, CPoint next, COLORREF color);

void MidpointEllipse(CDC* pDC, COLORREF color, CPoint center, CPoint a, CPoint b);
