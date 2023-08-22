#ifndef UTIL_HPP
#define UTIL_HPP

#include <vector>
#include "point.hpp"

std::vector<Point> getRandPoints(int N, int max = 100);

std::vector<Point> copy_sort(std::vector<Point> points, bool (*cmp)(const Point &, const Point &));

#endif