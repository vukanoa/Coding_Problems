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

#include <cmath>
using namespace std;

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
class Solution_Loop {
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
        if (n <= 0) return false;

        double base = 4.0;
        double x = std::log(static_cast<double>(n)) / std::log(base);

        const double EPS = 1e-10;
        return std::fabs(x - std::round(x)) < EPS; // 2.0000000001 is INT
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Similar Math as above.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  52.41% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Follow_Up_2 {
public:
    bool isPowerOfFour(int n)
    {
        if (n <= 0)
            return false;

        double base = 4.0;
        double x = std::log2(static_cast<double>(n)) / 2.0;

        const double EPS = 1e-10;

        // Nearest integer exponent
        int exponent = static_cast<int>(std::round(x));

        // Verify by recomputing 4^exponent and comparing to n with tolerance
        double candidate = std::pow(base, exponent);

        // std::fabs <==> floating-point absolute
        return std::fabs(candidate - static_cast<double>(n)) < EPS;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Explained in the comments.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  52.41% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Pure_Binary_Math {
public:
    bool isPowerOfFour(int n)
    {
        // 1. Must be positive
        // 2. Must be power of two (only one bit set)
        // 3. That bit must be at an odd position (power of four property)
        return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555);
    }
};
