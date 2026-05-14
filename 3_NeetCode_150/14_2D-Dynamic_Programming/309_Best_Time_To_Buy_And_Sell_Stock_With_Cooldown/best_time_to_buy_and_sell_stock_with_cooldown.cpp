/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    309) Best Time To Buy And Sell Stock With Cooldown
    ==================================================

    ============
    Description:
    ============

    You are given an array prices where prices[i] is the price of a given stock
    on the ith day.

    Find the maximum profit you can achieve. You may complete as many
    transactions as you like (i.e., buy one and sell one share of the stock
    multiple times) with the following restrictions:

        After you sell your stock, you cannot buy stock on the next day (i.e.,
        cooldown one day).

    Note: You may not engage in multiple transactions simultaneously (i.e., you
    must sell the stock before you buy again).

    =============================================
    FUNCTION: int maxProfit(vector<int>& prices);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: prices = [1,2,3,0,2]
    Output: 3
    Explanation: transactions = [buy, sell, cooldown, buy, sell]


    --- Example 2 ---
    Input: prices = [1]
    Output: 0


    *** Constraints ***
    1 <= prices.length <= 5000
    0 <= prices[i] <= 1000

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  69.41% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Top_Down__Memoization {
private:
    int memo[5001][3];

public:
    int maxProfit(std::vector<int>& prices)
    {
        const int N = prices.size();

        /* Initialize */
        for (int i = 0; i < 5001; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                memo[i][j] = INT_MIN;
            }
        }

        return solve(0, 0, prices);
    }

private:
    // prev_action:  0->Neutral, 1->Bought, 2->Sold
    int solve(int idx, int prev_action, vector<int>& prices)
    {
        const int N = prices.size();

        if (idx == N)
            return 0;

        if (memo[idx][prev_action] != INT_MIN)
            return memo[idx][prev_action];

        /* Skip */
        int skip = INT_MIN;
        if (prev_action == 2) // Sold yesterday
            skip = solve(idx + 1,     0      , prices); // Today = Cooldown day
        else
            skip = solve(idx + 1, prev_action, prices);

        /* Take */
        int take = INT_MIN;
        switch (prev_action)
        {
            case 0: // Neutral
                take = -prices[idx] + solve(idx + 1, 1, prices); // Buy now
                break;

            case 1: // Bought but didn't sell yet
                take =  prices[idx] + solve(idx + 1, 2, prices); // Sell now
                break;

            case 2: // Cooldown day
                take = INT_MIN;
                break;
        }

        return memo[idx][prev_action] = max(skip, take);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as idea above, however this one uses Bottom-Up Tabulation technique
    instead.

    The logic is, thus, "inverted" in a way.

    Usually, either Top-Down Memoization or Bottom-Up Tabulation is MUCH easier
    to write.

    For this problem--at least for me--it's MUCH easier to write Memoization.
    However, it's always beneficial to write both, in order to practice.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  47.76% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Bottom_Up_Tabulation {
public:
    int maxProfit(vector<int>& prices)
    {
        const int N = prices.size();
        vector<vector<int>> dp(N+2, vector<int>(3, INT_MIN));

        /* Base case */
        dp[N][0] = 0;
        dp[N][1] = 0;
        dp[N][2] = 0;

        for (int i = N-1; i >= 0; i--)
        {
            dp[i][0] = max(    0      + dp[i+1][0],  // Skip
                           -prices[i] + dp[i+1][1]); // Buy  on this day

            dp[i][1] = max(    0      + dp[i+1][1],  // Skip
                            prices[i] + dp[i+1][2]); // Sell on this day

            dp[i][2] = dp[i+1][0]; // Today is a cooldown day;
        }

        return dp[0][0];
    }
};
