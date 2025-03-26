/*
    ============
    === EASY ===
    ============

    =====================================================
    3178) Find the Child Who Has the Ball After K Seconds
    =====================================================

    ============
    Description:
    ============

    You are given two positive integers n and k. There are n children numbered
    from 0 to n - 1 standing in a queue in order from left to right.

    Initially, child 0 holds a ball and the direction of passing the ball is
    towards the right direction. After each second, the child holding the ball
    passes it to the child next to them. Once the ball reaches either end of
    the line, i.e. child 0 or child n - 1, the direction of passing is reversed

    Return the number of the child who receives the ball after k seconds.

    ==========================================
    FUNCTION: int numberOfChild(int n, int k);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, k = 5
    Output: 1

    --- Example 2 ---
    Input: n = 5, k = 6
    Output: 2

    --- Example 3 ---
    Input: n = 4, k = 2
    Output: 2


    *** Constraints ***
    2 <= n <= 50
    1 <= k <= 50

*/

/*
    ------------
    --- IDEA ---
    ------------

    Intuitive simple math.

    This question is the same as 2582: Pass the Pillow.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  84.31% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numberOfChild(int n, int k)
    {
        int circles = k / (n-1);

        if (circles & 1)
            return (n-1) - (k % (n-1));

        return 0 + (k % (n-1));
    }
};
