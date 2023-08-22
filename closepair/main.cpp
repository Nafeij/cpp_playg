#include <cstdlib>
#include <iostream>

#include "point.hpp"
#include "util.hpp"
#include "closest.hpp"
#include "plot.hpp"

int main(int argc, char** argv) {
    int N = 9;
    if (argc > 1) {
        N = std::atoi(argv[1]);
    }
    std::vector<Point> points = getRandPoints(N);
    printf("Points:\n");
    for (Point p : points) {
        p.print();
        printf("\n");
    }

    std::pair<Point, Point> closest = closestPair(points);
    printf("Closest pair:\n");
    closest.first.print();
    printf(", ");
    closest.second.print();
    printf("\nDist: %f\n", closest.first.dist(closest.second));

    plot(points, closest);

    return 0;
}