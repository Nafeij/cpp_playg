/**Kattis - closestpair2
 * The classic problem. The line sweep algorithm we used previously still works fast enough.
 *
 * Time: O(im not sure), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

#include <vector>
#include <utility>
#include <set>
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>

#include <matplot/matplot.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<ld, ld> pt;
typedef pair<ld, pair<pt, pt>> Ans;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

// Variables:
const int N = 50000;

pt points[N];

ld dist(pt a, pt b)
{
    return hypot(a.first - b.first, a.second - b.second);
}

void initRandPoints(long double max)
{
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<long double> dist(0, max);
    for (int i = 0; i < N; i++)
    {
        points[i] = {dist(e2), dist(e2)};
    }
}

void plot(const pt *points, const pair<pt, pt> &ans)
{
    vector<double> x, y;
    for (int i = 0; i < N; i++)
    {
        x.push_back(points[i].first);
        y.push_back(points[i].second);
    }
    vector<ld> x1 = {ans.first.first, ans.second.first}, y1 = {ans.first.second, ans.second.second};
    matplot::scatter(x, y);
    matplot::hold(matplot::on);
    matplot::plot(x1, y1)->line_style("-x");
    matplot::show();
}

Ans bruteForce(pt points[N])
{
    ld min = 1e12;
    pair<pt, pt> ans_pair;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (ld d = dist(points[i], points[j]); d < min)
            {
                min = d;
                ans_pair = {points[i], points[j]};
            }
        }
    }
    return {min, ans_pair};
}

Ans shamos_hoey_rec(const pt *Px, pt *Py, const int start, const int n)
{
    if (n <= 3)
    {
        ld min = 1e12;
        pair<pt, pt> ans_pair;
        for (int i = start; i < start + n; i++)
        {
            for (int j = i + 1; j < start + n; j++)
            {
                if (ld d = dist(Px[i], Px[j]); d < min)
                {
                    min = d;
                    ans_pair = {Px[i], Px[j]};
                }
                if (Py[i].second > Py[j].second)
                {
                    swap(Py[i], Py[j]);
                }
            }
        }
        return {min, ans_pair};
    }
    const int mid = n / 2;
    ld mid_x = Px[start + mid - 1].first;
    stable_partition(Py + start, Py + start + n, [&](pt p)
                     { return p.first < mid_x; });
    Ans left = shamos_hoey_rec(Px, Py, start, mid);
    Ans right = shamos_hoey_rec(Px, Py, start + mid, n - mid);
    inplace_merge(Py + start, Py + start + mid, Py + start + n, [&](pt a, pt b)
                  { return a.second < b.second; });
    Ans delta = left;
    if (right.first < left.first)
    {
        delta = right;
    }

    vector<pt> strip;
    Ans answer = delta;

    for (int i = start; i < start + n; i++)
    {
        if (abs(Py[i].first - mid_x) < delta.first)
        {
            for (int j = strip.size() - 1; j >= 0 && Py[i].second - strip[j].second < delta.first; j--)
            {
                if (ld d = dist(Py[i], strip[j]); d < answer.first)
                {
                    answer = {d, {Py[i], strip[j]}};
                }
            }
            strip.push_back(Py[i]);
        }
    }
    if (answer.first < delta.first)
    {
        return answer;
    }
    return delta;
}

Ans shamos_hoey(pt Px[N])
{
    pt Py[N];
    copy(Px, Px + N, Py);
    sort(Px, Px + N);
    // sort(Py, Py + N, [](pt a, pt b)
    //      { return a.second < b.second; });
    return shamos_hoey_rec(Px, Py, 0, N);
}

Ans sweep(pt points[N])
{
    int last_point;
    set<pt> s; // here we will store y, x so that it maintains sort by y
    sort(points, points + N);
    ld min = 1e12;
    pair<pt, pt> ans_pair;
    for (int i = 0; i < N; i++)
    {
        while (last_point < i && points[i].first - points[last_point].first >= min)
        {                                                                   // while last point is out of range
            s.erase({points[last_point].second, points[last_point].first}); // remove last point
            last_point++;
        }

        auto lo_it = s.lower_bound({points[i].second - min, -100009.0}); // find the lowest point
        auto hi_it = s.upper_bound({points[i].second + min, 100009.0});  // find the highest point

        for (auto it = lo_it; it != hi_it; it++)
        {
            if (ld d = dist(points[i], {it->second, it->first}); min > d)
            {
                min = d;
                ans_pair = {points[i], {it->second, it->first}};
            }
        }
        s.insert({points[i].second, points[i].first});
    }
    return {min, ans_pair};
}

Ans golin_chew(pt points[N])
{
    auto delta = dist(points[0], points[1]);
    typedef pair<u_int64, u_int64> sq;
    map<sq, pt> s;

    for (int i = 0; i < N; i++)
    {
        sq i_sq = {points[i].first / delta, points[i].second / delta};
        for (int
    }
}

Ans test(string name, Ans (*func)(pt *), pt *points)
{
    mutex m;
    condition_variable cv;
    Ans answer;
    int time;

    thread t([&cv, &answer, &time, func, points]()
             {
        auto start = chrono::steady_clock::now();
        answer = func(points);
        time = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count();
        cv.notify_one(); });

    t.detach();

    {
        unique_lock<mutex> lk(m);
        if (cv.wait_for(lk, 10s) == std::cv_status::timeout)
        {
            cout << name << ": Timeout\n";
            return {0, {{0, 0}, {0, 0}}};
        }
    }

    cout << name << ":\n\t("
         << answer.second.first.first << ", " << answer.second.first.second << ") --- ("
         << answer.second.second.first << ", " << answer.second.second.second << ") = "
         << answer.first
         << ", Time: " << time << "ms\n";
    return answer;
}

int main()
{
    // fast_cin();
    cout << fixed << setprecision(2);
    initRandPoints(1e9);

    test("Brute Force", bruteForce, points);
    test("Shamos Hoey", shamos_hoey, points);
    auto ans = test("Sweep", sweep, points);

    if (N < 200)
    {
        plot(points, ans.second);
    }

    return 0;
}