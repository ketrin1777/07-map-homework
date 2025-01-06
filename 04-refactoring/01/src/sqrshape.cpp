#include "sqrshape.h"

SqrShape::SqrShape(int _x[4], int _y[4])
{

    type = TypeShape::SQR;

    count = 4;

    // заполн¤ем координаты фигуры
    for (size_t i = 0; i < 3; i++)
    {
        x[i] = _x[i];
        y[i] = _y[i];
    }


    // стороны фигуры
    int a = abs(x[0] - x[1]);
    int b = abs(y[0] - y[1]);

    // считаем площадь фигуры
    square = a * b;

    // считаем объем фигуры
    volume = 0;
}
