#include <vector>
#include <random>
#include <algorithm>
#include "point.hpp"
#include "util.hpp"

std::vector<Point> getRandPoints(int N, int max)
{
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<double> dist(0, max);
    std::vector<Point> points;
    for (int i = 0; i < N; i++) {
        points.push_back(Point(dist(e2), dist(e2)));
    }
    return points;
}

std::vector<Point> copy_sort(std::vector<Point> points, bool (*cmp)(const Point &, const Point &))
{
    std::vector<Point> sorted = points;
    std::sort(sorted.begin(), sorted.end(), cmp);
    return sorted;
}
