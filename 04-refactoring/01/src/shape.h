#pragma once

#define _USE_MATH_DEFINES
#include <string>
#include <cmath>
class Shape
{
public:
    enum TypeShape
    {
        LINE,
        SQR,
        CUBE,
        CIRCLE,
        CYLINDER,
        UNKNOWN
    };

    Shape() = default;
    Shape(int _x[7], int _y[7], int _z[7]);
    virtual int getType() { return type; }

    TypeShape type{TypeShape::UNKNOWN};
    int x[7]{0}, y[7]{0}, z[7]{0};

    double volume{0};
    double square{0};
    double height{0};
    double radius{0};

    // Transform
    virtual void shift(int m, int n, int k);
    virtual void scaleX(int a);
    virtual void scaleY(int d);
    virtual void scaleZ(int e);
    virtual void scale(int s);

protected:
    int count{7};
};
