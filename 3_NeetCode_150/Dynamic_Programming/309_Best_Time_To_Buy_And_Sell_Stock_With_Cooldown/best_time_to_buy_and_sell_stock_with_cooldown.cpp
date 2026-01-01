#include <iostream>
#include <vector>
#include <unordered_map>

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

/* Time  Beats: 22.25% */
/* Space Beats:  5.63% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
private:
    struct pair_hash
    {
        template <class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2> &p) const
        {
            auto h1 = std::hash<T1>()(p.first);
            auto h2 = std::hash<T2>()(p.second);

            return h1 ^ (h2 << 1);
        }
    };

public:
    int maxProfit(vector<int>& prices)
    {
        int n = prices.size();
        std::unordered_map<std::pair<int, bool>, int, pair_hash> cache;

        // State == true  ---> Buying
        // State == false ---> Selling
        return dfs(prices, 0, true, cache);
    }

private:
    int dfs(std::vector<int>& prices, int i, bool state, std::unordered_map<std::pair<int, bool>, int, pair_hash>& cache)
    {
        if (i >= prices.size())
            return 0;

        if (cache.count(std::make_pair(i, state)))
            return cache[std::make_pair(i, state)];

        int cool = dfs(prices, i+1,  state, cache);
        if (state == true) // state == buying
        {
            int buy  = dfs(prices, i+1, !state, cache) - prices[i];

            cache.insert({{i, state}, std::max(buy, cool)});
        }
        else // state == selling
        {
            int sell = dfs(prices, i+2, !state, cache) + prices[i];

            cache.insert({{i, state}, std::max(sell, cool)});
        }

        return cache[std::make_pair(i, state)];
    }
};




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
