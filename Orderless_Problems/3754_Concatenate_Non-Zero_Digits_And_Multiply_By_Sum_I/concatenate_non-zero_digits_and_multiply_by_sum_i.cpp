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
#include <string>
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




/*
    ------------
    --- IDEA ---
    ------------

    Same idea, different way to implement.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  76.90% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(logN) */
class Solution_2 {
public:
    long long sumAndMultiply(int n)
    {
        long long x   = 0;
        long long sum = 0;

        string str_n = to_string(n);

        for (const char& chr : str_n)
        {
            int digit = chr - '0';

            if (digit > 0)
                x = x * 10 + digit;

            sum += digit;
        }

        return x * sum;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Anoher way to implement, this one doesn't use any additional space.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  89.81% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution_Space_Efficient_3 {
public:
    long long sumAndMultiply(int n)
    {
        long long x   = 0;
        long long sum = 0;

        long long pow_10 = 1;
        while (n > 0)
        {
            int digit = n % 10;

            if (digit > 0)
            {
                x += digit * pow_10;
                pow_10 *= 10;
            }

            sum += digit;


            // Divide
            n /= 10;
        }

        return x * sum;
    }
};
