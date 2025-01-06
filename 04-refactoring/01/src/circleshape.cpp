#include "circleshape.h"

CircleShape::CircleShape(int _x, int _y, double R)
{
    type = TypeShape::CIRCLE;
    // заполн¤ем координаты фигуры

    count = 1;

    x[0] = _x;
    y[0] = _y;
    radius = R;

    // считаем площадь фигуры
    M_PI *R *R;

    // считаем объем фигуры
    volume = 0;
}
