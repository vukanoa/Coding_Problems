/*
    ============
    === EASY ===
    ============

    ===================================
    1009) Complement of Base 10 Integer
    ===================================

    ============
    Description:
    ============

    The complement of an integer is the integer you get when you flip all the
    0's to 1's and all the 1's to 0's in its binary representation.

    For example, The integer 5 is "101" in binary and its complement is "010"
    which is the integer 2.

    Given an integer n, return its complement.

    =======================================
    FUNCTION: int bitwiseComplement(int n);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5
    Output: 2
    Explanation: 5 is "101" in binary, with complement "010" in binary, which
                 is 2 in base-10.

    --- Example 2 ---
    Input: n = 7
    Output: 0
    Explanation: 7 is "111" in binary, with complement "000" in binary, which
                 is 0 in base-10.

    --- Example 3 ---
    Input: n = 10
    Output: 5
    Explanation: 10 is "1010" in binary, with complement "0101" in binary,
                 which is 5 in base-10.


    *** Constraints ***
    0 <= n < 10^9

*/

#include <cmath>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   5.96% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int bitwiseComplement(int n)
    {
        if (n == 0)
            return 1;

        double base = 2.0;
        double log_value = log(n) / log(base); // Base-2 logarithm of 8

        int ceil_value = static_cast<int>(1.0 * ceil(log_value));
        int mask = (1 << ceil_value) - 1;


        return (~n) & mask;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but a much cleaner way. Instead of utilizing Logarithm, we
    use "__builtin_clz" which counts the number of LEADING 0s in a number in
    its binary representation.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  34.89% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_builtin_clz {
public:
    int bitwiseComplement(int n)
    {
        if (n == 0)
            return 1; 

        int mask = (1 << (32 - __builtin_clz(n))) - 1; 

        return (~n) &  mask ;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.28% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_builtin_clz_XOR {
public:
    int bitwiseComplement(int n)
    {
        if (n == 0)
            return 1; 

        int mask = (1 << (32 - __builtin_clz(n))) - 1; 

        return n ^ mask ;
    }
};
