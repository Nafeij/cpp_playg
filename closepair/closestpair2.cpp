#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

#include <cstdlib>
#include <iostream>

#include "point.hpp"
#include "util.hpp"
#include "closest.hpp"

using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int main()
{
    fast_cin();
    cout << fixed;
    cout.precision(2);
    while (1)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        std::vector<Point> points;
        for (int i = 0; i < n; i++)
        {
            long double x, y;
            cin >> x >> y;
            points.push_back({x, y});
        }
        pair<Point, Point> ans_pair = closestPair(points);
        // std::assert(ans_pair.first.dist(ans_pair.second) < 1e12);
        cout << ans_pair.first.x << " " << ans_pair.first.y << " " << ans_pair.second.x << " " << ans_pair.second.y << endl;
    }

    return 0;
}