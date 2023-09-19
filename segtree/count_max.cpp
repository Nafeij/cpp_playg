#include <iostream>

#include "segtree.hpp"

int main()
{
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