#include "shape.h"

Shape::Shape(int _x[7], int _y[7], int _z[7])
{
    // type = _type;
    // заполн¤ем координаты фигуры

    // стороны фигуры

    // считаем объем фигуры
}

void Shape::shift(int m, int n, int k)
{
    for (size_t i = 0; i < count; i++)
    {
        shape.x[i] += m;
        shape.y[i] += n;
        if (shape.getType() == Shape::CUBE)
        {
            shape.z[i] += k;
        }
    }
}

void Shape::scaleX(int a)
{
    for (size_t i = 0; i < count; i++)
    {
        shape.x[i] *= a;
    }
}

void Shape::scaleY(int d)
{
    for (size_t i = 0; i < count; i++)
    {
        shape.y[i] *= d;
    }
}

void Shape::scaleZ(int e)
{
    if (shape.getType() == Shape::CUBE)
    {
        for (size_t i = 0; i < count; i++)
        {
            shape.z[i] *= e;
        }
    }
}

void Shape::scale(int s)
{
    for (size_t i = 0; i < count; i++)
    {
        shape.x[i] /= s;
        shape.y[i] /= s;
        if (shape.getType() == Shape::CUBE)
        {
            shape.z[i] /= s;
        }
    }
}
