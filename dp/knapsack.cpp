#include <vector>
#include <iostream>
#include <map>
using namespace std;

struct item
{
    int w, v;
};
ostream &operator<<(ostream &os, const item &i)
{
    os << "(" << i.w << ", " << i.v << ")";
    return os;
}

void knapsack(vector<item> items, int W)
{
    vector<vector<int>> m(2, vector<int>(W + 1));
    for (int i = 0; i < items.size(); i++)
    {
        for (int j = 0; j <= W; j++)
        {
            if (items[i].w > j)
                m[1][j] = m[0][j];
            else
                m[1][j] = max(m[0][j], m[0][j - items[i].w] + items[i].v);
        }
        m[0] = m[1];
    }
    cout << "Max value: " << m[1][W] << endl;
}

int main()
{
    const int W = 10;
    vector<item> items = {{5, 10}, {4, 40}, {6, 30}, {3, 50}};
    knapsack(items, W);
    return 0;
}