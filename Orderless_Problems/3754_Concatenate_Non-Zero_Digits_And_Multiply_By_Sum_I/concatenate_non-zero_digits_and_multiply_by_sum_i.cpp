/*
    ============
    === EASY ===
    ============

    =======================================================
    3754) Concatenate Non-Zero Digits and Multiply by Sum I
    =======================================================

    ============
    Description:
    ============

    You are given an integer n.

    Form a new integer x by concatenating all the non-zero digits of n in their
    original order. If there are no non-zero digits, x = 0.

    Let sum be the sum of digits in x.

    Return an integer representing the value of x * sum.

    ==========================================
    FUNCTION: long long sumAndMultiply(int n);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10203004
    Output: 12340
    Explanation:
        The non-zero digits are 1, 2, 3, and 4. Thus, x = 1234.
        The sum of digits is sum = 1 + 2 + 3 + 4 = 10.
        Therefore, the answer is x * sum = 1234 * 10 = 12340.

    --- Example 2 ---
    Input: n = 1000
    Output: 1
    Explanation:
        The non-zero digit is 1, so x = 1 and sum = 1.
        Therefore, the answer is x * sum = 1 * 1 = 1.


    *** Constraints ***
    0 <= n <= 10^9

*/

#include <stack>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   6.15% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(logN) */
class Solution {
public:
    long long sumAndMultiply(int n)
    {
        long long x   = 0LL;
        long long sum = 0LL;

        stack<int> stack;

        while (n > 0)
        {
            int digit = n % 10;

            if (digit != 0)
                stack.push(digit);

            sum += digit;

            // Divide
            n /= 10;
        }

        while ( ! stack.empty())
        {
            int digit = stack.top();
            stack.pop();

            x *= 10;
            x += digit;
        }

        return x * sum;
    }
};
