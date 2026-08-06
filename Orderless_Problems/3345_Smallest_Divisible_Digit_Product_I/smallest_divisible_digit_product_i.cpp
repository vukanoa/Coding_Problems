/*
    ============
    === EASY ===
    ============

    ========================================
    3345) Smallest Divisible Digit Product I
    ========================================

    ============
    Description:
    ============

    You are given two integers n and t. Return the smallest number greater than
    or equal to n such that the product of its digits is divisible by t.

    ===========================================
    FUNCTION: int smallestNumber(int n, int t);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10, t = 2
    Output: 10
    Explanation:
    The digit product of 10 is 0, which is divisible by 2, making it the
    smallest number greater than or equal to 10 that satisfies the condition.

    --- Example 2 ---
    Input: n = 15, t = 3
    Output: 16
    Explanation:
    The digit product of 16 is 6, which is divisible by 3, making it the
    smallest number greater than or equal to 15 that satisfies the condition.

    *** Constraints ***
    1 <= n <= 100
    1 <= t <= 10

*/

/* Time  Beats: 100.00% */
/* Space Beats:  37.77% */

/* Time Complexity:  O((answer - n + 1) * log(answer)) */
/* Space Complexity: O(1)                              */
class Solution {
public:
    int smallestNumber(int n, int t) 
    {
        int i = n;
        for (;;)
        {
            int number = i;

            int sum = 1; // Neutral element for multiplication
            while (number > 0)
            {
                sum    *= number % 10;
                number /= 10;
            }

            if (sum % t == 0)
                return i;
            
            i++;
        }

        return -1; // Unreachable.
    }
};
