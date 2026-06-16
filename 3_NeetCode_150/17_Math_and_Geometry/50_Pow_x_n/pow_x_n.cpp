/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    50) Pow(x, n)
    ===========================

    ============
    Description:
    ============

    Implement pow(x, n), which calculates x raised to the power n (i.e., x^n).

    ========================================
    FUNCTION: double myPow(double x, int n);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: x = 2.00000, n = 10
    Output: 1024.00000

    --- Example 2 ---
    Input: x = 2.10000, n = 3
    Output: 9.26100

    --- Example 3 ---
    Input: x = 2.00000, n = -2
    Output: 0.25000
    Explanation: 2-2 = 1/22 = 1/4 = 0.25

    *** Constraints ***
    -100.0 < x < 100.0
    -231 <= n <= 231-1
    n is an integer.
    Either x is not zero or n > 0.
    -104 <= xn <= 104

*/

#include <cstdlib>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    So what is, for example:

        2^10?

    It's: 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2
          ~~~~~~~~~~~~~~~~~v~~~~~~~~~~~~~~~~~~~
                          10

    So is it this easy? We can just iterate n times and multiply?
    No. That would give a TLE. That Solution is O(n) which doesn't pass all the
    tests.

    So how are we going to solve it in less than O(n).

    Consider this same example:

        2^10 = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2
               ~~~~~~~~~~~~~~~~~v~~~~~~~~~~~~~~~~~~~
                               10

    We can notice that:

        2^10 = 2^5 * 2^5

    Can you see the repeated work?

    Can't we just take calculated 2^5 and multiply it by itself?
    That's half the work.

    But, why stop there?
    We can go further. We can break down: 2^5 now.

    How are we going to break it down if the exponent is an odd number?

    Let's write it down:

        2^5 = 2^2 * 2^2 * 2;

    That's 2^2 twice, multiplied by a constant value of 2.
    Let's break it down even further:

        2^2 = 2^1 * 2^1

    And now, we can just go backwards and multiply with given results.

    This indicates that we're going to use a recursion, that further indicates
    that we need some form of base case at which we'll stop.

    So what will be the Base Case:

        if n == 0, it's always going to be 1.


    However, what happens if the exponent is ODD?
    Let's say we have:

        3^11

    In that case we need to do one additional multiplication, multiplying once
    more with the base.

        3^11 = 3^5 * 3^5 * 3
                           ^
                           |
                           |
                        Additional multiplication with the base

    In the code we'll cover this case by simply having an if statement:

        if (exp & 1)
            result *= base;

*/

/* Time  Beats: 100.00% */
/* Space Beats:  69.48% */

/* Time  Complexity: O(log2(N)) */
/* Space Complexity: O(log2(N)) */
class Solution {
public:
    double myPow(double x, int n)
    {
        bool negative_exponent = n < 0;
        bool negative_base = x < 0;
        bool odd_exponent = n & 1;

        x = abs(x);
        long long LL_n = llabs((long long)n);

        double result = recursive_binary_exponentiation(x, LL_n);

        if (negative_exponent)
            result = 1.0 / result;

        if (negative_base && odd_exponent)
            result *= -1.0;

        return result;
    }

private:
    double recursive_binary_exponentiation(double base, long long exp)
    {
        if (exp == 0)
            return 1.0;

        double subproblem = recursive_binary_exponentiation(base, exp / 2);

        double result = subproblem * subproblem;

        if (exp & 1)
            result *= base;

        return result;
    }
};
