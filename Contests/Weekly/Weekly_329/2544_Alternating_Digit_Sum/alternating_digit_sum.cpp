/*
    ============
    === EASY ===
    ============

    ===========================
    2544) Alternating Digit Sum
    ===========================

    ============
    Description:
    ============

    You are given a positive integer n. Each digit of n has a sign according to
    the following rules:

        + The most significant digit is assigned a positive sign.
        + Each other digit has an opposite sign to its adjacent digits.

    Return the sum of all digits with their corresponding sign.

    =======================================
    FUNCTION: int alternateDigitSum(int n);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 521
    Output: 4
    Explanation: (+5) + (-2) + (+1) = 4.

    --- Example 2 ---
    Input: n = 111
    Output: 1
    Explanation: (+1) + (-1) + (+1) = 1.

    --- Example 3 ---
    Input: n = 886996
    Output: 0
    Explanation: (+8) + (-8) + (+6) + (-9) + (+9) + (-6) = 0.


    *** Constraints ***
    1 <= n <= 10^9

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  44.17% */

/* Time  Complexity: O(N)        */
/* Space Complexity: O(log10(N)) */
class Solution {
public:
    int alternateDigitSum(int n)
    {
        int result = 0;
        string str = to_string(n);

        int sign = 1;
        for (const char& chr : str)
        {
            result += sign * (chr - '0');
            sign *= -1; // Flip the sign
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Optimal.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  72.28% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Optimal__Right_to_Left {
public:
    int alternateDigitSum(int n)
    {
        int result = 0;

        int sign = 1;
        while (n > 0)
        {
            sign *= -1; // Flip the sign
            result += sign * (n % 10);

            // Divide
            n /= 10;
        }

        return sign * result;
    }
};
