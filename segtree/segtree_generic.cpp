#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

template <typename T>
struct SegmentTree
{
    int size;
    vector<T> tree;
    T(*tOpt)
    (T, T);

    SegmentTree(T arr[], int size, T (*tOpt)(T, T))
    {
        this->tOpt = tOpt;
        this->size = size;
        this->tree.resize(2 * size);
        build(arr);
    }

    SegmentTree(vector<T> arr, T (*tOpt)(T, T))
    {
        SegmentTree(arr.data(), arr.size(), tOpt);
    }

    void build(T arr[])
    {
        // leaf nodes
        for (int i = 0; i < size; i++)
            tree[size + i] = arr[i];

        // internal nodes
        for (int i = size - 1; i > 0; --i)
            tree[i] = tOpt(tree[i << 1], tree[i << 1 | 1]);
    }

    void update(int p, T value)
    {
        tree[p + size] = value;
        p = p + size;

        // bubble up
        for (int i = p; i > 1; i >>= 1)
            tree[i >> 1] = tOpt(tree[i], tree[i ^ 1]);
    }

    T query(int l, int r)
    {
        T res{};
        for (l += size, r += size; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = tOpt(res, tree[l++]);
            if (r & 1)
                res = tOpt(res, tree[--r]);
        }
        return res;
    }
};

void prefix_sum()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    SegmentTree<int> st(a, 12,
                        [](int a, int b)
                        { return a + b; });

    printf("Sum of values in [2,7) = %d\n", st.query(2, 7)); // = 25
    st.update(2, 1);
    printf("Sum of values in [2,7) = %d\n", st.query(2, 7)); // = 23
};

void count_max()
{
    // Max + occurence
    struct vi
    {
        int value, count;
    };
    vi b[] = {{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {11, 1}, {12, 1}};
    SegmentTree<vi> st2(b, 12,
                        [](vi a, vi b)
                        {
                            if (a.value == b.value)
                                return vi{a.value, a.count + b.count};
                            else if (a.value > b.value)
                                return a;
                            else
                                return b;
                        });

    vi res = st2.query(2, 7);
    printf("Max value in [2,7) = %d, count = %d\n", res.value, res.count); // = 7, 1
    st2.update(2, vi{7, 1});
    res = st2.query(2, 7);
    printf("Max value in [2,7) = %d, count = %d\n", res.value, res.count); // = 7, 2
};

void LIS()
{
    int c[] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    struct p
    {
        int value, index;
    };
    p _c[16]; // {value, index}
    for (int i = 0; i < 16; i++)
        _c[i] = p{c[i], i};
    sort(_c, _c + 16, [](p a, p b)
         { if (a.value == b.value) // sort by asc value, desc index
                return a.index > b.index;
            else
                return a.value < b.value; });
    int d[16]{};
    SegmentTree<int> st3(d, 16,
                         [](int a, int b)
                         { return max(a, b); });
    for (int i = 0; i < 16; i++) // for ascending values _c[i].value
    {
        int res = st3.query(0, _c[i].index); // query max LIS ending at index 0 .. _c[i].index-1
        st3.update(_c[i].index, res + 1);    // update LIS ending at _c[i].index
    }
    printf("LIS = %d\n", st3.query(0, 16)); // = 6
};

// driver program to test the above function
int main()
{
    // prefix_sum();
    // count_max();
    LIS();

    return 0;
}