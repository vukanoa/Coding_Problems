/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    390) Elimination Game
    ===========================

    ============
    Description:
    ============

    You have a list arr of all integers in the range [1, n] sorted in a
    strictly increasing order. Apply the following algorithm on arr:

        + Starting from left to right, remove the first number and every other
          number afterward until you reach the end of the list.

        + Repeat the previous step again, but this time from right to left,
          remove the rightmost number and every other number from the remaining
          numbers.

        + Keep repeating the steps again, alternating left to right and right
          to left, until a single number remains.

    Given the integer n, return the last number that remains in arr.

    ===================================
    FUNCTION: int lastRemaining(int n);
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 9
    Output: 6
    Explanation:
    arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    arr = [2, 4, 6, 8]
    arr = [2, 6]
    arr = [6]

    --- Example 2 ---
    Input: n = 1
    Output: 1


    *** Constraints ***
    1 <= n <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  7.81% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int lastRemaining(int n)
    {
        int head = 1;
        int step = 1;

        bool direction = true; // True --> to_the_right, False - to_the_left
        while (n>1)
        {
            if (direction)
                head += step;
            else
                head += (n % 2 == 0) ? 0 : step;

            step *= 2;
            n /= 2;

            direction =! direction;
        }

        return head;
    }
};
