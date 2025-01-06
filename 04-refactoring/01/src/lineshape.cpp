#include "lineshape.h"

LineShape::LineShape(int _x[2], int _y[2])
{
    type = TypeShape::LINE;
    count = 2;

    // заполн¤ем координаты фигуры
    x[0] = _x[0];
    y[0] = _y[0];
    x[1] = _x[1];
    y[1] = _y[1];

    // стороны фигуры
	// int a = abs(x[0] - x[1]);
	// int b = abs(y[0] - y[1]);

    // считаем площадь фигуры
    square = 0;

    // считаем объем фигуры
    volume = 0;
}
