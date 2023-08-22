#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>

#include "closest.hpp"
#include "util.hpp"

// typedef std::priority_queue<Point, std::vector<Point>, decltype(&Point::cmpX)> XQ;
// typedef std::priority_queue<Point, std::vector<Point>, decltype(&Point::cmpY)> YQ;

std::pair<Point, Point> closestPairSimple(std::vector<Point> points)
{
    double dist_min = points[0].dist(points[1]);
    std::pair<Point, Point> closest = std::make_pair(points[0], points[1]);
    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i + 1; j < points.size(); j++)
        {
            if (points[i].dist(points[j]) < dist_min)
            {
                dist_min = points[i].dist(points[j]);
                closest = std::make_pair(points[i], points[j]);
            }
        }
    }
    return closest;
};

std::pair<Point, Point> closestPairRec(
    std::vector<Point> Px,
    std::vector<Point> Py)
{
    if (Px.size() <= 3)
    {
        return closestPairSimple(Px);
    }
    auto u_mid = Px.begin() + Px.size() / 2 + 1;
    std::vector<Point> Q = std::vector<Point>(Px.begin(), u_mid);
    std::vector<Point> R = std::vector<Point>(u_mid, Px.end());

    // for (auto p : R)
    // {
    //     std::cout << "(" << p.x << ", " << p.y << ")";
    // }

    std::vector<Point> Qx = copy_sort(Q, Point::cmpX);
    std::vector<Point> Qy = copy_sort(Q, Point::cmpY);
    std::vector<Point> Rx = copy_sort(R, Point::cmpX);
    std::vector<Point> Ry = copy_sort(R, Point::cmpY);

    std::pair<Point, Point> qs = closestPairRec(Qx, Qy);
    std::pair<Point, Point> rs = closestPairRec(Rx, Ry);

    std::pair<Point, Point> closest = qs;
    double d = qs.first.dist(qs.second);

    if (rs.first.dist(rs.second) < d)
    {
        closest = rs;
        d = rs.first.dist(rs.second);
    }

    double xs = Qx[Qx.size() - 1].x;

    std::vector<Point> Sy;

    for (auto p : Py)
    {
        if (std::abs(xs - p.x) < d)
        {
            Sy.push_back(p);
        }
    }

    for (int i = 0; i < Sy.size(); i++)
    {
        for (int j = i + 1; j < Sy.size() && j < i + 16; j++)
        {
            if (Sy[i].dist(Sy[j]) < d)
            {
                closest = std::make_pair(Sy[i], Sy[j]);
                d = Sy[i].dist(Sy[j]);
            }
        }
    }

    return closest;
};

std::pair<Point, Point> closestPair(std::vector<Point> points)
{
    // XQ pqPX(begin(points), end(points), Point::cmpX);
    // YQ pqPY(begin(points), end(points), Point::cmpY);

    std::vector<Point> Px = copy_sort(points, Point::cmpX);
    std::vector<Point> Py = copy_sort(points, Point::cmpY);

    return closestPairRec(Px, Py);
};
