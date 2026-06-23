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
                           ^
                           |


    If we multiply our "result" by 10 it will overflow!

    However, what if our result--again without the very last digit--is this:

        result  = 214748364      // It has  9 digits
        INT_MAX = 2147483647     // It has 10 digits
                           ^
                           |

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

/* Time  Complexity: O(log10(x)) */
/* Space Complexity: O(1)        */
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

            // Have we NOT checked:
            //
            //     if (x == INT_MIN)
            //         return 0;
            //
            // then this would give as an OVERFLOW or we'd need "long long"
            // which is forbiden to use in this Problem. (Although it still
            // will be accepted for some reason)
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




/*
    ------------
    --- IDEA ---
    ------------

    This one is the same as above, however we do NOT use the 2nd if-statement:

        if ((result == INT_MAX / 10) && (result > (INT_MAX % 10)))
            return 0;

    because it turns out it is NOT necessary.
    Why?

    Because x is of type "int" therefore if x consists of 10 digits then the
    first one can either be 1 or 2.

    Therefore, if we get to a point where we're about to add the very last
    digit then it's certainly completely safe to do it without further check
    ups.


        INT_MAX = 2147483647     
              x = 2148333333 <-----
                                  |
                                  |
                                  |
                You CANNOT have this value in x.
                Why not?

                Because x is an INTEGER and this value is GREATER than 2^31 - 1

    However, let's assume that ALL of the last 9 digits are the SAME and that
    ONLY the first--leftmost--differs.

        INT_MAX = 2147483647     
              x = ?3147483647
                  ^
                  |
                  |


    Now you tell me, since x is an INTEGER, which digits can replace the ? as
    to make the x a VALID(!!!) Input?

    Only 1 or 2.
    (Assuming x indeed has exactly 10 digits. If it has LESS, then we don't
     have to worry about anything)


*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.26% */

/* Time  Complexity: O(log10(x)) */
/* Space Complexity: O(1)        */
class Solution_Only_One_If_Statement {
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

            // Have we NOT checked:
            //
            //     if (x == INT_MIN)
            //         return 0;
            //
            // then this would give as an OVERFLOW or we'd need "long long".
            x *= -1;
        }

        while (x != 0)
        {
            int digit = x % 10;

            if (result > INT_MAX / 10)
                return 0;

            // We do NOT actually need this 2nd if-statement below.
            //
            // Why?
            //
            // Because x is of type "int" therefore if x consists of 10 digits
            // then the first one can either be 1 or 2. In both cases it's
            // completely safe to add "digit" to "result".
            //
            // if (result == (INT_MAX / 10) && digit > (INT_MAX % 10))
            //     return 0;

            result *= 10;
            result += digit;

            x /= 10;
        }

        return negative ? -result : result;
    }
};
