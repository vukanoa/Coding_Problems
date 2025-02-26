/*
    ============
    === EASY ===
    ============

    ======================================================
    3226) Number of Bit Changes to Make Two Integers Equal
    ======================================================

    ============
    Description:
    ============

    You are given two positive integers n and k.

    You can choose any bit in the binary representation of n that is equal to 1
    and change it to 0.

    Return the number of changes needed to make n equal to k. If it is
    impossible, return -1.

    =======================================
    FUNCTION: int minChanges(int n, int k);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 13, k = 4
    Output: 2
    Explanation:
    Initially, the binary representations of n and k are n = (1101)2 and k = (0100)2.
    We can change the first and fourth bits of n. The resulting integer is n = (0100)2 = k.

    --- Example 2 ---
    Input: n = 21, k = 21
    Output: 0
    Explanation:
    n and k are already equal, so no changes are needed.

    --- Example 3 ---
    Input: n = 14, k = 13
    Output: -1
    Explanation:
    It is not possible to make n equal to k.


    *** Constraints ***
    1 <= n, k <= 10^6

*/

/*
    ------------
    --- IDEA ---
    ------------

    If at any bit, we find that for k it's 1 and for n it's 0, then immediately
    return -1.

    Why?
    Because we're allowed to only modify 1's in n, therefore if some 0 bit in n
    is 1 bit in k, we can't do anything about it, thus we won't ever make it
    the same.

    If some bit is 1 in both n and k, then do nothing.
    If some bit is 1 in n and 0 in k, then increment result.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  31.03% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minChanges(int n, int k)
    {
        int result = 0;

        while (n != 0 || n != k)
        {
            if ( !(n & 1) && (k & 1))
                return -1;

            if (n & 1)
                result += !(k & 1);

            n >>= 1;
            k >>= 1;
        }

        return result;
    }
};
