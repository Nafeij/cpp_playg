#pragma once

#include <vector>

using namespace std;

template <typename T>
struct SegmentTree
{
    SegmentTree(T arr[], int size, T (*tOpt)(T, T));
    SegmentTree(vector<T> arr, T (*tOpt)(T, T));

    void build(T arr[]);
    void update(int p, T value);
    T query(int l, int r);

private:
    int size;
    vector<T> tree;
    T(*tOpt)
    (T, T);
};

#include "segtree_impl.hpp"