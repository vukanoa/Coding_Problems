#include <iostream>

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

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    
*/

/* Time  Beats:  100% */
/* Space Beats: 29.31% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
    int maxProfit(std::vector<int>& prices)
    {
        int n = prices.size();
        std::vector<std::vector<int>> dp(n+2, std::vector<int>(2, 0));

        for(int i = n-1; i >= 0; i--)
        {
            dp[i][0] = std::max( prices[i] + dp[i+2][1], 0 + dp[i+1][0]); // Sell
            dp[i][1] = std::max(-prices[i] + dp[i+1][0], 0 + dp[i+1][1]); // Buy
        }

        return dp[0][1];
    }
};
