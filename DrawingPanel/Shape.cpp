#include "pch.h"
#include "Shape.h"

Shape::Shape() : lastPoint(nullptr)
{
}

Shape::~Shape()
{
	if (lastPoint != nullptr) {
		delete lastPoint;
	}
}

void Shape::AddPoint(CPoint point)
{
	points.Add(point);
}

void Shape::SetColor(COLORREF color)
{
	this->color = color;
}
