/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    808) Soup Servings
    ===========================

    ============
    Description:
    ============

    You have two soups, A and B, each starting with n mL. On every turn, one of
    the following four serving operations is chosen at random, each with
    probability 0.25 independent of all previous turns:

        + pour 100 mL from type A and 0 mL from type B
        + pour 75 mL from type A and 25 mL from type B
        + pour 50 mL from type A and 50 mL from type B
        + pour 25 mL from type A and 75 mL from type B

    Note:

        + There is no operation that pours 0 mL from A and 100 mL from B.
        + The amounts from A and B are poured simultaneously during the turn.
        + If an operation asks you to pour more than you have left of a soup,
          pour all that remains of that soup.

    The process stops immediately after any turn in which one of the soups is
    used up.

    Return the probability that A is used up before B, plus half the
    probability that both soups are used up in the same turn. Answers within
    10-5 of the actual answer will be accepted.

    =====================================
    FUNCTION: double soupServings(int n);
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 50
    Output: 0.62500
    Explanation:
    If we perform either of the first two serving operations, soup A will
    become empty first.
    If we perform the third operation, A and B will become empty at the same
    time.
    If we perform the fourth operation, B will become empty first.
    So the total probability of A becoming empty first plus half the
    probability that A and B become empty at the same time, is:
    0.25 * (1 + 1 + 0.5 + 0) = 0.625.

    --- Example 2 ---
    Input: n = 100 Output: 0.71875
    Explanation:
    + If we perform the first serving operation, soup A will become empty first
    + If we perform the second serving operations, A will become empty on
      performing operation [1, 2, 3], and both A and B become empty on
      performing operation 4.
    + If we perform the third operation, A will become empty on performing
      operation [1, 2], and both A and B become empty on performing operation 3
    + If we perform the fourth operation, A will become empty on performing
      operation 1, and both A and B become empty on performing operation 2.
    + So the total probability of A becoming empty first plus half the
      probability that A and B become empty at the same time, is 0.71875.


    *** Constraints ***
    0 <= n <= 10^9

*/

#include <cmath>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 22.17% */
/* Space Beats: 41.67% */

/* Time  Complexity: O((N / 25)^2) */ // But practically O(1)
/* Space Complexity: O((N / 25)^2) */ // But practically O(1)
class Solution {
public:
    double soupServings(int n)
    {
        int servings_unit_count = ceil(n / 25.0);
        unordered_map<int, unordered_map<int, double>> dp;

        for (int k = 1; k <= servings_unit_count; k++)
        {
            if (solve(k, k, dp) > 1 - 1e-5)
                return 1;
        }

        return solve(servings_unit_count, servings_unit_count, dp);
    }

private:
    double solve(int i, int j, unordered_map<int, unordered_map<int, double>>& dp)
    {
        if (i <= 0 && j <= 0)
            return 0.5;

        if (i <= 0)
            return 1;

        if (j <= 0)
            return 0;

        if (dp[i].count(j))
            return dp[i][j];

        dp[i][j] = solve(i - 4, j    , dp) +
                   solve(i - 3, j - 1, dp) +
                   solve(i - 2, j - 2, dp) +
                   solve(i - 1, j - 3, dp);

        dp[i][j] /= 4;

        return dp[i][j];
    }
};
