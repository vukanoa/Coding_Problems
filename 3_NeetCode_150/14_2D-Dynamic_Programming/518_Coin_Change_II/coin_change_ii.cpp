/*
    ==============
    === MEDIUM ===
    ==============

    ===================
    518) Coin Change II
    ===================

    ============
    Description:
    ============

    You are given an integer array coins representing coins of different
    denominations and an integer amount representing a total amount of money.

    Return the number of combinations that make up that amount. If that amount
    of money cannot be made up by any combination of the coins, return 0.

    You may assume that you have an infinite number of each kind of coin.

    The answer is guaranteed to fit into a signed 32-bit integer.

    =====================================================
    FUNCTION: int change(int amount, vector<int>& coins);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: amount = 5, coins = [1,2,5]
    Output: 4
    Explanation: there are four ways to make up the amount:
    5=5
    5=2+2+1
    5=2+1+1+1
    5=1+1+1+1+1


    --- Example 2 ---
    Input: amount = 3, coins = [2]
    Output: 0
    Explanation: the amount of 3 cannot be made up just with coins of 2.


    --- Example 3 ---
    Input: amount = 10, coins = [10]
    Output: 1

    *** Constraints ***
    1 <= coins.length <= 300
    1 <= coins[i] <= 5000
    All the values of coins are unique.
    0 <= amount <= 5000

*/

#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 66.76% */
/* Space Beats: 64.57% */

/* Time  Complexity: O(N * amount) */
/* Space Complexity: O(N * amount) */
class Solution_Top_Down__Memoization {
    unsigned long long memo[301][5001];

public:
    int change(int amount, vector<int>& coins)
    {
        const int N = coins.size();

        /* Sort */
        sort(coins.begin(), coins.end());

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        /* Solve */
        return solve(N-1, amount, coins);
    }

private:
    int solve(int idx, int amount, vector<int>& coins)
    {
        if (amount == 0)
            return 1;

        if (idx < 0)
            return 0;

        if (memo[idx][amount] != -1)
            return memo[idx][amount];

        int result = 0;
        if ((amount - coins[idx]) < 0)
            result = solve(idx - 1, amount, coins);
        else
            result = solve(idx - 1, amount             , coins) +
                     solve(idx    , amount - coins[idx], coins);

        return memo[idx][amount] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 48.52% */
/* Space Beats: 13.41% */

/* Time  Complexity: O(N * amount) */
/* Space Complexity: O(N * amount) */
class Solution_Bottom_Up__Tabulation {
public:
    int change(int amount, vector<int>& coins)
    {
        const int N = coins.size();

        /* Sort */
        sort(coins.begin(), coins.end());
        
        vector<vector<unsigned long long>> dp(N, vector<unsigned long long>(amount+1, 0ULL));
        dp[0][0] = 1ULL;

        /* Initialize 0th row, i.e. num of combinations if use ONLY coins[0] */
        for (int a = 1; a <= amount; a++)
        {
            if ((a - coins[0]) < 0)
                continue;

            dp[0][a] = dp[0][a - coins[0]];
        }

        /* Initialize 0th column, i.e. amount=0 */
        for (int i = 0; i < N; i++)
            dp[i][0] = 1ULL;

        /* Solve */
        for (int i = 1; i < N; i++)
        {
            for (int a = 1; a <= amount; a++)
            {
                if ((a - coins[i]) < 0)
                    dp[i][a] = dp[i - 1][a];
                else
                    dp[i][a] = dp[i - 1][a] + dp[i][a - coins[i]];
            }
        }

        return dp[N-1][amount];
    }
};
