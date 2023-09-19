#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#include "segtree.hpp"

using namespace std;

template <typename T>
SegmentTree<T>::SegmentTree(T arr[], int size, T (*tOpt)(T, T))
{
    this->tOpt = tOpt;
    this->size = size;
    this->tree.resize(2 * size);
    build(arr);
};

template <typename T>
SegmentTree<T>::SegmentTree(vector<T> arr, T (*tOpt)(T, T))
{
    SegmentTree(arr.data(), arr.size(), tOpt);
};

template <typename T>
void SegmentTree<T>::build(T arr[])
{
    // leaf nodes
    for (int i = 0; i < size; i++)
        tree[size + i] = arr[i];

    // internal nodes
    for (int i = size - 1; i > 0; --i)
        tree[i] = tOpt(tree[i << 1], tree[i << 1 | 1]);
};

template <typename T>
void SegmentTree<T>::update(int p, T value)
{
    tree[p + size] = value;
    p = p + size;

    // bubble up
    for (int i = p; i > 1; i >>= 1)
        tree[i >> 1] = tOpt(tree[i], tree[i ^ 1]);
};

template <typename T>
T SegmentTree<T>::query(int l, int r)
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
};