/*
    ============
    === EASY ===
    ============

    ============================
    3827) Count Monobit Integers
    ============================

    ============
    Description:
    ============

    You are given an integer n.

    An integer is called Monobit if all bits in its binary representation are
    the same.

    Return the count of Monobit integers in the range [0, n] (inclusive).

    ==================================
    FUNCTION: int countMonobit(int n);
    ==================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1
    Output: 2
    Explanation:
        The integers in the range [0, 1] have binary representations "0" and
        "1". Each representation consists of identical bits. Thus, the answer
        is 2.

    --- Example 2 ---
    Input: n = 4
    Output: 3
    Explanation:
        The integers in the range [0, 4] include binaries "0", "1", "10", "11",
        and "100". Only 0, 1 and 3 satisfy the Monobit condition. Thus, the
        answer is 3.


    *** Constraints ***
    0 <= n <= 1000

*/

#include <cmath>
using namespace std;

/* Time  Beats: 100.00% */
/* Space Beats:  65.04% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countMonobit(int n)
    {
        int result = 1; // +1 is because we need to count 0 as well

        for (int i = 1; i <= n; i++)
        {
            if ( ((i+1) & i) == 0 ) // If the NEXT number(i.e. "i + 1") is a
                ++result;           // power of 2, then that means the CURRENT
                                    // NUMBER consists of ALL trailing 1 bits
        }

        return result;
    }
};




/* Time  Beats: 100.00% */
/* Space Beats:  65.04% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int countMonobit(int n)
    {
        return 1 + std::log2(n+1); // (1 + ...) because we need to count 0 too
    }
};




/* Time  Beats: 100.00% */
/* Space Beats:  65.04% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_3 {
public:
    int countMonobit(int n)
    {
        // __lg is a non-standard built-in function provided by GCC and Clang
        // (and some other compilers) that computes:
        //
        //     floor(log2(x))  <==>  __lg(x)
        //
        return 1 + __lg(n+1); // (1 + ...) because we need to count 0 too
    }
};




/* Time  Beats: 100.00% */
/* Space Beats:  65.04% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_4 {
public:
    int countMonobit(unsigned n)
    {
        return 32 - __builtin_clz(n+1);
    }
};




/* Time  Beats: 100.00% */
/* Space Beats:  65.04% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_5 {
public:
    int countMonobit(int n) // Since n goes only up to 1000
    {
        if (n ==  0) return 1;
        if (n <   3) return 2;
        if (n <   7) return 3;
        if (n <  15) return 4;
        if (n <  31) return 5;
        if (n <  63) return 6;
        if (n < 127) return 7;
        if (n < 255) return 8;
        if (n < 511) return 9;

        return 10;
    }
};
