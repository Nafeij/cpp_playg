#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
struct SegmentTree
{
    int n;
    vector<T> tree;
    T(*tOpt)
    (T, T);

    SegmentTree(T arr[], int n, T (*tOpt)(T, T))
    {
        this->tOpt = tOpt;
        this->n = n;
        this->tree.resize(2 * n);
        build(arr);
    }

    void build(T arr[])
    {
        // leaf nodes
        for (int i = 0; i < n; i++)
            tree[n + i] = arr[i];

        // internal nodes
        for (int i = n - 1; i > 0; --i)
            tree[i] = tOpt(tree[i << 1], tree[i << 1 | 1]);
    }

    void update(int p, T value)
    {
        tree[p + n] = value;
        p = p + n;

        // bubble up
        for (int i = p; i > 1; i >>= 1)
            tree[i >> 1] = tOpt(tree[i], tree[i ^ 1]);
    }

    T query(int l, int r)
    {
        T res{};
        for (l += n, r += n; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = tOpt(res, tree[l++]);
            if (r & 1)
                res = tOpt(res, tree[--r]);
        }
        return res;
    }
};
// driver program to test the above function
int main()
{
    // Prefix sum
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    SegmentTree<int> st(a, 12,
                        [](int a, int b)
                        { return a + b; });

    printf("Sum of values in [2,7) = %d\n", st.query(2, 7));
    st.update(2, 1);
    printf("Sum of values in [2,7) = %d\n", st.query(2, 7));

    pair<int, int> b[] = {{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {11, 1}, {12, 1}};

    // Max + occurence
    SegmentTree<pair<int, int>> st2(b, 12,
                                    [](pair<int, int> a, pair<int, int> b)
                                    {
                                        if (a.first == b.first)
                                            return make_pair(a.first, a.second + b.second);
                                        else if (a.first > b.first)
                                            return a;
                                        else
                                            return b;
                                    });

    pair<int, int> res = st2.query(2, 7);
    printf("Max value in [2,7) = %d, count = %d\n", res.first, res.second);
    st2.update(2, make_pair(7, 1));
    res = st2.query(2, 7);
    printf("Max value in [2,7) = %d, count = %d\n", res.first, res.second);

    // LIS
    int c[] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    pair<int, int> _c[16]; // {value, index}
    for (int i = 0; i < 16; i++)
        _c[i] = make_pair(c[i], i);
    sort(_c, _c + 16, [](pair<int, int> a, pair<int, int> b)
         { if (a.first == b.first) // sort by asc value, desc index
                return a.second > b.second;
            else
                return a.first < b.first; });
    int d[16]{};
    SegmentTree<int> st3(d, 16,
                         [](int a, int b)
                         { return max(a, b); });
    for (int i = 0; i < 16; i++) // for ascending values _c[i].first
    {
        int res = st3.query(0, _c[i].second); // query max LIS ending at index < _c[i].second
        st3.update(_c[i].second, res + 1); // update LIS ending at index _c[i].second
    }
    printf("LIS = %d\n", st3.query(0, 16));

    return 0;
}