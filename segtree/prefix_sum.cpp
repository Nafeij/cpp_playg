#include <iostream>

#include "segtree.hpp"

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    SegmentTree<int> st(a, 12,
                        [](int a, int b)
                        { return a + b; });

    printf("Sum of values in [2,7) = %d\n", st.query(2, 7)); // = 25
    st.update(2, 1);
    printf("Sum of values in [2,7) = %d\n", st.query(2, 7)); // = 23
    return 0;
};