#include "pch.h"
#include "ShapeFactory.h"
#include "ShapeNone.h"
#include "ShapePoint.h"
#include "ShapeLine.h"
#include "ShapeCircle.h"
#include "ShapeOval.h"
#include "ShapePolygon.h"
#include "ShapeCube.h"

Shape* ShapeFactory::Create(ShapeType type)
{
    Shape* result = nullptr;
    switch (type) {
    case ShapeType::Point:
        result = new ShapePoint();
        break;
    case ShapeType::Line:
        result = new ShapeLine();
        break;
    case ShapeType::Circle:
        result = new ShapeCircle();
        break;
    case ShapeType::Oval:
        result = new ShapeOval();
        break;
    case ShapeType::Polygon:
        result = new ShapePolygon();
        break;
    case ShapeType::Cube:
        result = new ShapeCube();
        break;
    case ShapeType::None:
    default:
        result = new ShapeNone();
        break;
    }
    return result;
}

CString ShapeTypeToCString(ShapeType type)
{
    switch (type) {
    case ShapeType::Point:
        return CString("��");
    case ShapeType::Line:
        return CString("ֱ��");
        break;
    case ShapeType::Circle:
        return CString("Բ");
        break;
    case ShapeType::Oval:
        return CString("��Բ");
        break;
    case ShapeType::Polygon:
        return CString("�����");
        break;
    case ShapeType::Cube:
        return CString("������");
        break;
    case ShapeType::None:
    default:
        return CString("δѡ����״");
        break;
    }
}
