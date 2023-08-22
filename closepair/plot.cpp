#include <vector>

#include <matplot/matplot.h>

#include "plot.hpp"

void plot(std::vector<Point> points, std::pair<Point, Point> closest)
{
    std::vector<double> x;
    std::vector<double> y;
    for (Point p : points) {
        x.push_back(p.x);
        y.push_back(p.y);
    }
    std::vector<double> x1;
    std::vector<double> y1;
    x1.push_back(closest.first.x);
    y1.push_back(closest.first.y);
    x1.push_back(closest.second.x);
    y1.push_back(closest.second.y);
    matplot::scatter(x, y);
    matplot::hold(matplot::on);
    matplot::plot(x1, y1)->line_style("-x");;
    matplot::show();
}