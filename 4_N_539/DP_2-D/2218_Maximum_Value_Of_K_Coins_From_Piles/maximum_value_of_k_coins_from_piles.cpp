#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    =========================================
    2218) Maximum Value of K Coins From Piles
    =========================================

    ============
    Description:
    ============

    There are n piles of coins on a table. Each pile consists of a positive
    number of coins of assorted denominations.

    In one move, you can choose any coin on top of any pile, remove it, and add
    it to your wallet.

    Given a list piles, where piles[i] is a list of integers denoting the
    composition of the ith pile from top to bottom, and a positive integer k,
    return the maximum total value of coins you can have in your wallet if you
    choose exactly k coins optimally.

    =================================================================
    FUNCTION: int maxValueOfCoins(vector<vector<int>>& piles, int k);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: piles = [[1,100,3],[7,8,9]], k = 2
    Output: 101
    Explanation:
    The above diagram shows the different ways we can choose k coins.
    The maximum total we can obtain is 101.

    --- Example 2 ---
    Input: piles = [[100],[100],[100],[100],[100],[100],[1,1,1,1,1,1,700]], k = 7
    Output: 706
    Explanation:
    The maximum total can be obtained if we choose all coins from the last pile.


    *** Constraints ***
    n == piles.length
    1 <= n <= 1000
    1 <= piles[i][j] <= 10^5
    1 <= k <= sum(piles[i].length) <= 2000

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 88.33% */
/* Space Beats: 71.99% */

// n ==> Number of piles
// k ==> Number of coins to pick
// m ==> is the maximum size of any pile
/* Time  Complexity: O(n * k * m) */
/* Space Complexity: O(n * k)     */
class Solution_Memoization {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k)
    {
        const int n = piles.size();
        vector<vector<int>>dp(n, vector<int>(k + 1, -1));

        int result = solve(piles, dp, n - 1, k);

        return result;
    }

private:
    int solve(vector<vector<int>>&piles, vector<vector<int>>&dp, int end_pile_idx, int k)
    {
        if (end_pile_idx < 0 || k == 0)
            return 0;

        if (dp[end_pile_idx][k] != -1)
            return dp[end_pile_idx][k];

        int curr_pile_size = piles[end_pile_idx].size();
        int max_can_pick = min(k, curr_pile_size);

        // Consider 'not picking' any coin
        int max_sum = solve(piles, dp, end_pile_idx - 1, k); // Do NOT pick any coin from curr pile
        int pickedSum = 0;

        // Now consider picking some coins
        for (int i = 0; i < max_can_pick; i++)
        {
            int coin_value = piles[end_pile_idx][i];
            picked_sum += coin_value;

            int next_max_sum = solve(piles, dp, end_pile_idx - 1, k - i - 1);
            max_sum = max(max_sum, picked_sum + next_max_sum);
        }

        return dp[end_pile_idx][k] = max_sum;
    }
};
