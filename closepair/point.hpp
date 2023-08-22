#ifndef POINT_HPP
#define POINT_HPP

struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
    Point() : x(0), y(0) {}
    bool operator==(const Point& p) const;
    double dist(const Point& p) const;
    static bool cmpX(const Point& a, const Point& b);
    static bool cmpY(const Point& a, const Point& b);
    void print() const;
};

#endif