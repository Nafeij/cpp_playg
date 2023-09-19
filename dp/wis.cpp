#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct job
{
    int s, e, w;
};
ostream &operator<<(ostream &os, const job &j)
{
    os << "(" << j.s << ", " << j.e << ", " << j.w << ")";
    return os;
}

int p(vector<job> jobsFAsc, int n)
{
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int m = (l + r) / 2;
        if (jobsFAsc[m].e <= jobsFAsc[n].s)
        {
            if (jobsFAsc[m + 1].e <= jobsFAsc[n].s)
                l = m + 1;
            else
                return m;
        }
        else
            r = m - 1;
    }
    return -1;
}

void wis(vector<job> jobs)
{
    sort(jobs.begin(), jobs.end(), [](const job &j1, const job &j2)
         { return j1.e < j2.e; });
    for (auto j : jobs)
        cout << j << ' ';
    cout << endl;
    vector<int> m(jobs.size());
    m[0] = jobs[0].w;
    for (int i = 1; i < jobs.size(); i++)
    {
        int p_i = p(jobs, i);
        m[i] = max(m[i - 1], (p_i == -1 ? 0 : m[p_i]) + jobs[i].w);
    }
    cout << "Max profit: " << m[m.size() - 1] << " <= ";
    for (int i = m.size() - 1; i >= 0; i--)
    {
        if (m[i] != m[i - 1])
        {
            cout << jobs[i] << ' ';
            i = p(jobs, i);
            if (i == 0)
            {
                cout << jobs[i];
                break;
            }
        }
    }
    cout << endl;
};

int main()
{
    vector<job> jobs = {{1, 2, 50}, {3, 5, 20}, {6, 19, 100}, {2, 100, 200}};
    wis(jobs);
    vector<job> jobs2 = {{1, 2, 50}, {3, 5, 20}, {6, 19, 100}, {2, 100, 200}, {5, 10, 50}, {4, 6, 70}, {7, 8, 30}, {9, 11, 10}, {12, 15, 20}, {13, 14, 40}, {16, 18, 60}, {17, 19, 80}, {20, 21, 90}, {22, 23, 100}, {24, 25, 110}, {26, 27, 120}};
    wis(jobs2);
    return 0;
};