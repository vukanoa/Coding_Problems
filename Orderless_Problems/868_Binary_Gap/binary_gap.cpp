/*
    ============
    === EASY ===
    ============

    ===========================
    868) Binary Gap
    ===========================

    ============
    Description:
    ============

    Given a positive integer n, find and return the longest distance between
    any two adjacent 1's in the binary representation of n. If there are no two
    adjacent 1's, return 0.

    Two 1's are adjacent if there are only 0's separating them (possibly no
    0's). The distance between two 1's is the absolute difference between their
    bit positions. For example, the two 1's in "1001" have a distance of 3.

    ===============================
    FUNCTION: int binaryGap(int n);
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 22
    Output: 2
    Explanation: 22 in binary is "10110".
    The first adjacent pair of 1's is "10110" with a distance of 2.
    The second adjacent pair of 1's is "10110" with a distance of 1.
    The answer is the largest of these two distances, which is 2.
    Note that "10110" is not a valid pair since there is a 1 separating the two
    1's underlined.

    --- Example 2 ---
    Input: n = 8
    Output: 0
    Explanation: 8 in binary is "1000".
    There are not any adjacent pairs of 1's in the binary representation of 8,
    so we return 0.

    --- Example 3 ---
    Input: n = 5
    Output: 2
    Explanation: 5 in binary is "101".


    *** Constraints ***
    1 <= n <= 10^9

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
/* Space Beats: 66.75% */

/* Time  Complexity: O(1) */ // Always 32 at most
/* Space Complexity: O(1) */
class Solution {
public:
    int binaryGap(int n)
    {
        int result = 0;

        // Or                    = 31 - __builtin_clz(n);
        int leftmost_set_bit_idx = static_cast<int>(ceil(log2(n)));

        int prev_set_bit_idx = leftmost_set_bit_idx;
        for (int i = leftmost_set_bit_idx - 1; i >= 0; i--)
        {
            if (n & (1 << i))
            {
                result = max(result,  prev_set_bit_idx - i);
                prev_set_bit_idx = i;
            }
        }

        return result;
    }
};
