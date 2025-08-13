/*
    ============
    === EASY ===
    ============

    ===========================
    326) Power of Three
    ===========================

    ============
    Description:
    ============

    Given an integer n, return true if it is a power of three. Otherwise,
    return false.

    An integer n is a power of three, if there exists an integer x such that
    n == 3x.

    =====================================
    FUNCTION: bool isPowerOfThree(int n);
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 27
    Output: true
    Explanation: 27 = 33

    --- Example 2 ---
    Input: n = 0
    Output: false
    Explanation: There is no x where 3x = 0.

    --- Example 3 ---
    Input: n = -1
    Output: false
    Explanation: There is no x where 3x = (-1).


    *** Constraints ***
    -2^31 <= n <= 2^31 - 1

*/

#include <climits>
#include <cmath>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 66.52% */
/* Space Beats:  5.34% */

/* Time  Complexity: O(log3(n)) */
/* Space Complexity: O(1)       */
class Solution_Iteratie {
public:
    bool isPowerOfThree(int n)
    {
        if (n == 1)
            return true;

        if (n <= 0 || n % 3 != 0)
            return false;

        int orig_n = n;
        int power = -1;
        while (n > 0)
        {
            power++;
            n /= 3;
        }

        return orig_n == pow(3, power);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Implemented using recursion.

*/

/* Time  Beats: 66.52% */
/* Space Beats: 76.82% */

/* Time  Complexity: O(log3(n)) */
/* Space Complexity: O(log3(n)) */
class Solution_Recursion {
public:
    static bool isPowerOfThree(int n) // "static" prevents passing "this" pointer
    {
        return (n == 1) ? 1 : ((n <= 0 || n % 3) ? 0 : isPowerOfThree(n / 3));
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This method works because 3 is a prime number. This also works for any
    other PRIME number.

*/

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    bool isPowerOfThree(int n)
    {
        int largest_exponent       = log(INT_MAX) / log(3);
        int largest_power_of_three = pow(3, largest_exponent);

        return n > 0 && largest_power_of_three % n == 0;
    }
};
