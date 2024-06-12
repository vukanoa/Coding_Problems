#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    461) Hamming Distance
    ===========================

    ============
    Description:
    ============

    The Hamming distance between two integers is the number of positions at
    which the corresponding bits are different.

    Given two integers x and y, return the Hamming distance between them.

    ============================================
    FUNCTION: int hammingDistance(int x, int y); 
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: x = 1, y = 4
    Output: 2
    Explanation:
    1   (0 0 0 1)
    4   (0 1 0 0)
           ↑   ↑
    The above arrows point to positions where the corresponding bits are different.


    --- Example 2 ---
    Input: x = 3, y = 1
    Output: 1


    *** Constraints ***
    0 <= x, y <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    Basic bit manipulation techniques.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  54.71% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int hammingDistance(int x, int y)
    {
        const int BYTE_SIZE = 8;
        int result = 0;

        for (int i = 0; i < sizeof(int) * BYTE_SIZE; i++)
        {
            result += (x & 0x01) ^ (y & 0x01);
            x >>= 1;
            y >>= 1;
        }

        return result;
    }
};
