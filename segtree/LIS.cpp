#include <iostream>
#include <algorithm>

#include "segtree.hpp"

int main()
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