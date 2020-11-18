#include "pch.h"
#include "ShapeFactory.h"
#include "ShapeNone.h"
#include "ShapePoint.h"
#include "ShapeLine.h"
#include "ShapeCircle.h"
#include "ShapeOval.h"
#include "ShapePolygon.h"
#include "ShapeCube.h"

Shape* ShapeFactory::Create(ShapeType shape)
{
    Shape* result = nullptr;
    switch (shape) {
    case SHAPE_POINT:
        result = new ShapePoint();
        break;
    case SHAPE_LINE:
        result = new ShapeLine();
        break;
    case SHAPE_CIRCLE:
        result = new ShapeCircle();
        break;
    case SHAPE_OVAL:
        result = new ShapeOval();
        break;
    case SHAPE_POLYGON:
        result = new ShapePolygon();
        break;
    case SHAPE_CUBE:
        result = new ShapeCube();
        break;
    case SHAPE_NONE:
    default:
        result = new ShapeNone();
        break;
    }
    return result;
}
