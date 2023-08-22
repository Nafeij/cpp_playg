#include <cmath>
#include <iostream>

#include "point.hpp"

bool Point::operator==(const Point &p) const
{
    return x == p.x && y == p.y;
};

double Point::dist(const Point &p) const
{
    return std::hypot(p.x - x, p.y - y);
};

bool Point::cmpX(const Point &a, const Point &b)
{
    return a.x < b.x;
};

bool Point::cmpY(const Point &a, const Point &b)
{
    return a.y < b.y;
};

void Point::print() const
{
    std::cout << "(" << x << ", " << y << ")";
};