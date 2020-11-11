#include "pch.h"
#include "utils.h"

int distance(CPoint a, CPoint b) {
	double x = a.x - b.x;
	double y = a.y - b.y;
	return sqrt(x * x + y * y);
}

void DDALine(CDC* pDC, CPoint start, CPoint end, COLORREF color) {
	double dx, dy, e, x, y;
	dx = end.x - start.x;
	dy = end.y - start.y;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	dx /= e;
	dy /= e;
	x = start.x;
	y = start.y;
	for (int i = 1; i <= e; i++)
	{
		pDC->SetPixel((int)(x + 0.5), (int)(y + 0.5), color);
		x += dx;
		y += dy;
	}
}

void BresenhamCircle(CDC* pDC, CPoint start, CPoint next, COLORREF color) {
	double R = distance(start, next);

	int x = 0;
	int y = R;
	int p = 3 - 2 * R;

	for (; x <= y; x++) {
		pDC->SetPixel(CPoint(x + start.x, y + start.y), color);
		pDC->SetPixel(CPoint(-x + start.x, y + start.y), color);
		pDC->SetPixel(CPoint(x + start.x, -y + start.y), color);
		pDC->SetPixel(CPoint(-x + start.x, -y + start.y), color);
		pDC->SetPixel(CPoint(y + start.x, x + start.y), color);
		pDC->SetPixel(CPoint(-y + start.x, x + start.y), color);
		pDC->SetPixel(CPoint(y + start.x, -x + start.y), color);
		pDC->SetPixel(CPoint(-y + start.x, -x + start.y), color);
		if (p >= 0) {
			p += 4 * (x - y) + 10;
			y--;
		}
		else {
			p += 4 * x + 6;
		}
	}
}

void MidpointEllipse(CDC* pDC, COLORREF color, CPoint center, CPoint a, CPoint b) {
	int aa = distance(a, center), bb = distance(b, center);
	int x = 0, y = bb;
	double d1 = bb * bb + aa * aa * (-bb + 0.25);
	pDC->SetPixel(CPoint(x + center.x, y + center.y), color);
	pDC->SetPixel(CPoint(-x + center.x, y + center.y), color);
	pDC->SetPixel(CPoint(x + center.x, -y + center.y), color);
	pDC->SetPixel(CPoint(-x + center.x, -y + center.y), color);
	while (bb * bb * (x + 1) < aa * aa * (y - 0.5)) {
		if (d1 < 0) {
			d1 += bb * bb * (2 * x + 3);
			x++;
		}
		else {
			d1 += (bb * bb * (2 * x + 3) + aa * aa * (-2 * y + 2));
			x++;
			y--;
		}
		pDC->SetPixel(CPoint(x + center.x, y + center.y), color);
		pDC->SetPixel(CPoint(-x + center.x, y + center.y), color);
		pDC->SetPixel(CPoint(x + center.x, -y + center.y), color);
		pDC->SetPixel(CPoint(-x + center.x, -y + center.y), color);
	}
	double d2 = bb * bb * (x + 0.5) * (x + 0.5) + aa * aa * (y - 1) * (y - 1) - aa * aa * bb * bb;
	while (y > 0) {
		if (d2 < 0) {
			d2 += bb * bb * (2 * x + 2) + aa * aa * (-2 * y + 3);
			x++;
			y--;
		}
		else {
			d2 += aa * aa * (-2 * y + 3);
			y--;
		}
		pDC->SetPixel(CPoint(x + center.x, y + center.y), color);
		pDC->SetPixel(CPoint(-x + center.x, y + center.y), color);
		pDC->SetPixel(CPoint(x + center.x, -y + center.y), color);
		pDC->SetPixel(CPoint(-x + center.x, -y + center.y), color);
	}
}

COLORREF ThonkColor(int x, int y) {
	try {
		static CImg<unsigned char> img("1117.bmp");
		x = x % img.width();
		y = y % img.height();
		return RGB(img(x, y, 0, 0), img(x, y, 0, 1), img(x, y, 0, 2));
	}
	catch (CImgException e) {
		TRACE(e._message);
	}

	// no color, white
	return RGB(0xff, 0xff, 0xff);
}