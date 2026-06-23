/*
    ==============
    === MEDIUM ===
    ==============

    ==================
    7) Reverse Integer
    ==================

    ============
    Description:
    ============

    Given a signed 32-bit integer x, return x with its digits reversed.
    If reversing x causes the value to go outside the signed 32-bit integer
    range [-2^31, 2^31 - 1], then return 0;

    =====
    Note: Assume the environment does not allow you to store 64-bit integers
          (signed or unsigned)
    =====

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: x = 123
    Output: 321

    --- Example 2 ---
    Input: x = -123
    Ouput: -321

    --- Example 3 ---
    Input: x = 120
    Output: 21

    *** Constraints ***
    -2^31 <= x <= 2^31 - 1
*/

#include <climits>
using namespace std;

/*
    INT_MIN = -2147483648
    INT_MAX =  2147483647
*/

/*
    ------------
    --- IDEA ---
    ------------

    It is self-explanatory for cases other than edge cases.

    Consider this:

        x = 2147483647 // INT_MAX

    Only these two if-statements are important:

        if (result > INT_MAX / 10)
            return 0;

        if ((result == INT_MAX / 10) && (result > (INT_MAX % 10)))
            return 0;

    So, why are we doing this?
    How exactly and WHY this works?

        INT_MAX =  2147483647

    Suppose that we have reversed some integer up to--but NOT including--the
    very last digit.

    Let's say our result is:

        result  = 2147483642     // It has 10 digits already
        INT_MAX = 2147483647     // It has 10 digits

    If we multiply our "result" by 10 it will overflow!

    However, what if our result--again without the very last digit--is this:

        result  = 214748364      // It has  9 digits
        INT_MAX = 2147483647     // It has 10 digits

    In that case we can indeed multiply by 10, but we can ONLY add digits that
    are LESS THAN OR EQUAL to 7:

        result  = 2147483640     // Okay
        result  = 2147483641     // Okay
        result  = 2147483642     // Okay
        result  = 2147483643     // Okay
        result  = 2147483644     // Okay
        result  = 2147483645     // Okay
        result  = 2147483646     // Okay
        result  = 2147483647     // Okay
        result  = 2147483648     // Overflow! It's a BIGGER value than INT_MAX

        INT_MAX = 2147483647     

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.36% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
public:
    int reverse(int x)
    {
        if (x == INT_MIN)
            return 0;

        int result = 0;

        bool negative = false;
        if (x < 0)
        {
            negative = true;
            x *= -1;
        }

        while (x != 0)
        {
            int digit = x % 10;

            // Appending ANY digit to "result" would create an Overflow
            if (result > INT_MAX / 10)
                return 0;

            if ((result == INT_MAX / 10) && (result > (INT_MAX % 10)))
                return 0;

            result *= 10;
            result += digit;

            x /= 10;
        }

        return negative ? -result : result;
    }
};
