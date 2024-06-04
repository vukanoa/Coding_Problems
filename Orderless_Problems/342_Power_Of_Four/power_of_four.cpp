#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    342) Power Of Four
    ===========================

    ============
    Description:
    ============

    Given an integer n, return true if it is a power of four. Otherwise, return
    false.

    An integer n is a power of four, if there exists an integer x such that n
    == 4x.


    ---------------
    -- Follow Up --
    ---------------

        Could you solve it without loops/recursion?


    ====================================
    FUNCTION: bool isPowerOfFour(int n);
    ====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 16
    Output: true

    --- Example 2 ---
    Input: n = 5
    Output: false

    --- Example 3 ---
    Input: n = 1
    Output: true


    *** Constraints ***
    -2^31 <= n <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    If we aren't allowed to use built-in functions, then we have to use a loop.

*/

/* Time  Beats: 37.74% */
/* Space Beats: 73.86% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Without_Builtin_functions {
public:
    bool isPowerOfFour(int n)
    {
        if (n <= 0) return false;
        if (n == 1) return true;

        while (n > 1)
        {
            if (n % 4 != 0)
                return false;

            n /= 4;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Simple math.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  10.78% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Follow_Up {
public:
    bool isPowerOfFour(int n)
    {
        if (n == 0)
            return false;

        return is_integer(log_base_b(n, 4));
    }

private:
    double log_base_b(int num, int b)
    {
        return std::log2(num) / std::log2(b);
    }

    bool is_integer(double number)
    {
        return std::floor(number) == number;
    }
};
