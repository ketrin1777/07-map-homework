#include "cubeshape.h"

CubeShape::CubeShape(int _x[7], int _y[7], int _z[7])
{
    type = TypeShape::CUBE;
    // заполн¤ем координаты фигуры

    count = 7;

    for (size_t i = 0; i < 7; i++)
    {
        x[i] = _x[i];
        y[i] = _y[i];
        z[i] = _z[i];
    }

    // стороны фигуры
    int a = abs(x[0] - x[1]);
    int b = abs(y[0] - y[1]);
    int c = abs(z[0] - z[1]);

    // считаем площадь фигуры
    square = 2 * a * b + 2 * a * c + 2 * b * c;

    // считаем объем фигуры
    volume = a * b * c;
}
