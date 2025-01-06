#include "cylindershape.h"

CylinderShape::CylinderShape(int _x, int _y, double R, double H)
{
    type = TypeShape::CYLINDER;

    count = 1;

    // заполн¤ем координаты фигуры
    x[0] = _x;
    y[0] = _y;
    radius = R;
    height = H;

    // считаем площадь фигуры
    square = M_PI * R * R + 2 * R * height;

    // считаем объем фигуры
    volume = M_PI * R * R * height;
}