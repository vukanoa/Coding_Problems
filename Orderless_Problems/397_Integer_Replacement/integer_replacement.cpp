/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    397) Integer Replacement
    ===========================

    ============
    Description:
    ============

    Given a positive integer n, you can apply one of the following operations:

        1. If n is even, replace n with n / 2.
        2. {If n is odd, replace n with either n + 1 or n - 1.

    Return the minimum number of operations needed for n to become 1.

    ========================================
    FUNCTION: int integerReplacement(int n);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 8
    Output: 3
    Explanation: 8 -> 4 -> 2 -> 1

    --- Example 2 ---
    Input: n = 7
    Output: 4
    Explanation: 7 -> 8 -> 4 -> 2 -> 1
    or 7 -> 6 -> 3 -> 2 -> 1

    --- Example 3 ---
    Input: n = 4
    Output: 2


    *** Constraints ***
    1 <= n <= 2^31 - 1

*/

#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  59.91% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(logN) */
class Solution {
private:
    unordered_map<int, int> memo;

public:
    int integerReplacement(int n)
    {
        return solve(n);
    }

private:
    int solve(long long n)
    {
        if (memo.count(n))
            return memo[n];

        if (n == 1)
            return 0;

        if (n % 2 == 0)
            memo[n] = 1 + solve(n / 2);
        else
            memo[n] = 1 + min(solve(n + 1),
                              solve(n - 1));

        return memo[n];
    }
};
