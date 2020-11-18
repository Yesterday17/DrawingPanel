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

void MatrixMultiply(const float a[][4], const float b[][4], float result[][4]);

void VectorMatrixMultiply(const float a[4], float b[][4], float result[4]);

float DotProduct(const float U[3], const float V[3]);

void CrossPruduct(const float U[3], const float V[3], float result[3]);

CPoint Proj(float vert[4], float projMat[][4]);