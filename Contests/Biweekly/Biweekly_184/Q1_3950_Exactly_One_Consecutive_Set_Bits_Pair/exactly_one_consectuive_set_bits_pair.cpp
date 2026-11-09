/*
    ============
    === EASY ===
    ============

    ===========================================
    3950) Exactly One Consecutive Set Bits Pair
    ===========================================

    ============
    Description:
    ============

    You are given an integer n.

    Return true if its binary representation contains exactly one adjacent pair
    of set bits, and false otherwise.

    =========================================
    FUNCTION: bool consecutiveSetBits(int n);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 6
    Output: true
    Explanation:
        + Binary representation of 6 is 110.

        + There is exactly one adjacent pair of set bits ("11"). Thus, the
          answer is true

    --- Example 2 ---
    Input: n = 5
    Output: false
    Explanation:
        + Binary representation of 5 is 101.

        + There is no adjacent pair of set bits. Thus, the answer is false

    *** Constraints ***
    0 <= n <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  30.97% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool consecutiveSetBits(int n)
    {
        int adjacent_pairs = 0;

        while (n > 1)
        {
            if ((n & 3) == 3)
                adjacent_pairs++;

            n >>= 1;
        }

        return adjacent_pairs == 1;
    }
};
