/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    2929) Distribute Candies Among Children II
    ==========================================

    ============
    Description:
    ============

    You are given two positive integers n and limit.

    Return the total number of ways to distribute n candies among 3 children
    such that no child gets more than limit candies.

    ========================================================
    FUNCTION: long long distributeCandies(int n, int limit);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, limit = 2
    Output: 3
    Explanation: There are 3 ways to distribute 5 candies such that no child
                 gets more than 2 candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).

    --- Example 2 ---
    Input: n = 3, limit = 3
    Output: 10
    Explanation: There are 10 ways to distribute 3 candies such that no child
                 gets more than 3 candies:
                 (0, 0, 3), (0, 1, 2), (0, 2, 1), (0, 3, 0), (1, 0, 2),
                 (1, 1, 1), (1, 2, 0), (2, 0, 1), (2, 1, 0) and (3, 0, 0).


    *** Constraints ***
    1 <= n <= 10^6
    1 <= limit <= 10^6

*/

#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 12.35% */
/* Space Beats: 57.06% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long distributeCandies(int n, int limit)
    {
        long long result = 0;

        for (int i = 0; i <= min(limit, n); i++)
        {
            if (n - i <= 2 * limit)
                result += min(n - i, limit) - max(0, n - i - limit) + 1;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 84.12% */
/* Space Beats: 84.71% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Math {
public:
    long long H3(long long n)
    {
        /*
           In General:

                           a! 
           C(a, b) = --------------
                      b! * (a - b)!


          In our problem:


                          (n + 2)! 
           C(n + 2, 2) = -----------
                          2! * n!


                          (n + 2) * (n + 1) * n! 
           C(n + 2, 2) = ----------------------
                                2! * n!


                          (n + 2) * (n + 1) 
           C(n + 2, 2) = ----------------------
                                2!


                          (n + 2) * (n + 1) 
           C(n + 2, 2) = ----------------------
                                2

        */

        return n < 0 ? 0 : (n+1) * (n+2) / 2;
    }

    long long distributeCandies(int n, int limit) 
    {
        return H3(n)                       -
               3LL * H3(n - limit - 1)     +
               3LL * H3(n - 2*(limit + 1)) -
               1LL * H3(n - 3*(limit + 1));
    }
};
