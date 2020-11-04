#include "pch.h"
#include "ShapeFactory.h"
#include "ShapeNone.h"
#include "ShapePoint.h"
#include "ShapeCircle.h"
#include "ShapeOval.h"

Shape* ShapeFactory::Create(ShapeType shape)
{
    Shape* result = nullptr;
    switch (shape) {
    case SHAPE_POINT:
        result = new ShapePoint();
        break;
    case SHAPE_CIRCLE:
        result = new ShapeCircle();
        break;
    case SHAPE_OVAL:
        result = new ShapeOval();
        break;
    case SHAPE_NONE:
    default:
        result = new ShapeNone();
        break;
    }
    return result;
}
