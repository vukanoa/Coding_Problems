/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    3932) Count Kth Roots in a Range
    ================================

    ============
    Description:
    ============

    You are given three integers l, r, and k.

    An integer y is said to be a perfect kth power if there exists an integer x
    such that y = x^k.

    Return the number of integers y in the range [l, r] (inclusive) that are
    perfect kth powers.

    =================================================
    FUNCTION: int countKthRoots(int l, int r, int k);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: l = 1, r = 9, k = 3
    Output: 2
    Explanation:
    The perfect cubes in the range [1, 9] are:
        1 = 13
        8 = 23
    Hence, the answer is 2.

    --- Example 2 ---
    Input: l = 8, r = 30, k = 2
    Output: 3
    Explanation:
    The perfect squares in the range [8, 30] are:
        9 = 32
        16 = 42
        25 = 52
    Hence, the answer is 3.

    *** Constraints ***
    0 <= l <= r <= 10^9
    1 <= k <= 30

*/

#include <cmath>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   5.41% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countKthRoots(int l, int r, int k)
    {
        int upper_kth_square = static_cast<int>(floor(pow(r, 1.0 / k) + 1e-9));
        int lower_kth_square = static_cast<int>(ceil(pow(l , 1.0 / k)));

        return upper_kth_square - lower_kth_square + 1;
    }
};
