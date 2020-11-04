#pragma once

#undef cimg_display
#define cimg_display 0
#include "CImg.h"
using namespace cimg_library;

int distance(CPoint a, CPoint b);

void DDALine(CDC* pDC, CPoint start, CPoint end, COLORREF color);

void BresenhamCircle(CDC* pDC, CPoint start, CPoint next, COLORREF color);

void MidpointEllipse(CDC* pDC, COLORREF color, CPoint center, CPoint a, CPoint b);

COLORREF ThonkColor(int x, int y);