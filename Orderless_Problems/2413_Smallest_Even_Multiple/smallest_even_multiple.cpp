/*
    ============
    === EASY ===
    ============

    ============================
    2413) Smallest Even Multiple
    ============================

    ============
    Description:
    ============

    Given a positive integer n, return the smallest positive integer that is a
    multiple of both 2 and n. 

    ==========================================
    FUNCTION: int smallestEvenMultiple(int n);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5
    Output: 10
    Explanation: The smallest multiple of both 5 and 2 is 10.

    --- Example 2 ---
    Input: n = 6
    Output: 6
    Explanation: The smallest multiple of both 6 and 2 is 6. Note that a number
                 is a multiple of itself.


    *** Constraints ***
    1 <= n <= 150

*/

/*
    ------------
    --- IDEA ---
    ------------

    Fundamental problem. Computation of "LCM" between two numbers.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  94.35% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(logn) */
class Solution {
public:
    int smallestEvenMultiple(int n)
    {
        return my_lcm(2, n);
    }

private:
    int my_gcd(int a, int b)
    {
        return b == 0 ? a : my_gcd(b, a % b);
    }

    int my_lcm(int a, int b)
    {
        return a / my_gcd(a, b) * b;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Since a(i.e. the first number) is ALWAYS 2 in this problem, then we notice
    that the answer depends on the oddness of number 'n'.

    If the number n is EVEN, then the LCM(2, n) is always n.
    However, if the number n is ODD, then LCM(2, n) is n * 2;

*/

/* Time  Beats: 100.00% */
/* Space Beats:  29.05% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Bit_Manipulation {
public:
    int smallestEvenMultiple(int n)
    {
        return n << (n & 1);
    }
};
