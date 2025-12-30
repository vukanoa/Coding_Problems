/*
    ============
    === HARD ===
    ============

    ============================
    829) Consecutive Numbers Sum
    ============================

    ============
    Description:
    ============

    Given an integer n, return the number of ways you can write n as the sum of
    consecutive positive integers.

    ===========================================
    FUNCTION: int consecutiveNumbersSum(int n);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5
    Output: 2
    Explanation: 5 = 2 + 3

    --- Example 2 ---
    Input: n = 9
    Output: 3
    Explanation: 9 = 4 + 5 = 2 + 3 + 4

    --- Example 3 ---
    Input: n = 15
    Output: 4
    Explanation: 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5

    *** Constraints ***
    1 <= n <= 10^9

*/

#include <cmath>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Given some number N, we can possibly write it as a sum of:

        2 numbers, or
        3 numbers, or
        4 numbers, etc.

    Let's assume that the first number in this series is x.
    We would have:

        x + (x+1) + (x+2) +...+ k     // terms = N

        kx + k*(k-1)/2 = N            // implies

        kx = N - k*(k-1)/2

    We can calculate the RHS for every value of k and if it is a multiple of k, then we can construct a sum of N using k terms starting from x.

    Now, one important question arises--Until what value of k should we loop for?
    Easy. In the WORST case, RHS should be greater than 0. Thta is:

        N - k*(k-1)/2 > 0           // which implies

        k*(k-1) < 2N                // which can be approximated to

        k*k < 2N ==> k < sqrt(2N)

    Hence, the overall complexity of hte algorithm is O(sqrt(N))

*/

/* Time  Beats: 51.18% */
/* Space Beats: 34.41% */

/* Time  Complexity: O(sqrt(N)) */
/* Space Complexity: O(1)       */
class Solution {
public:
    int consecutiveNumbersSum(int N)
    {
        int ways = 1;
        for (int k = 2; k < sqrt(2 * N); k++)
        {
            if (( N - (k * (k - 1)/2) ) % k == 0)
                ways++;
        }

        return ways;
    }
};
