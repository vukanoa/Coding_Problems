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

#include <cmath>
using namespace std;

/* Time  Beats: 100.00% */
/* Space Beats:  12.15% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int smallestNumber(int n, int t)
    {
        if (n % 10 == 0)
            return n;

        if (n <= 9)
        {

            if (n <= t)
                return t;

            int div = static_cast<int>(ceil(1.0 * n / t));

            return div * t < 10 ? div * t : 10;
        }

        int val = n / 10;
        for (int i = n % 10; i <= 9; i++)
        {
            if ((val * i) % t == 0)
                return val * 10 + i;
        }

        return val * 10 + 10;
    }
};


/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int smallestNumber(int n, int t)
    {
        auto product_of_digits = [](int x)
        {
            int product = 1;

            while (x > 0)
            {
                product *= (x % 10);
                x /= 10;
            }

            return product;
        };

        for (int i = n; i < n + 10; i++)
        {
            if (product_of_digits(i) % t == 0)
                return i;
        }
        
        return -1;
    }
};
