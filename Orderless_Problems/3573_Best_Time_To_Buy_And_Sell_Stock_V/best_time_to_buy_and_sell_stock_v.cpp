/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    3573) Best Time to Buy and Sell Stock V
    =======================================

    ============
    Description:
    ============

    You are given an integer array prices where prices[i] is the price of a
    stock in dollars on the ith day, and an integer k.

    You are allowed to make at most k transactions, where each transaction can
    be either of the following:

        + Normal transaction: Buy on day i, then sell on a later day j
        where i < j. You profit prices[j] - prices[i].

        + Short selling transaction: Sell on day i, then buy back on a later
        day j where i < j. You profit prices[i] - prices[j].

    Note that you must complete each transaction before starting another.
    Additionally, you can't buy or sell on the same day you are selling or
    buying back as part of a previous transaction.

    Return the maximum total profit you can earn by making at most k
    transactions.

    ==============================================================
    FUNCTION: long long maximumProfit(vector<int>& prices, int k);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: prices = [1,7,9,8,2], k = 2
    Output: 14
    Explanation:
    We can make $14 of profit through 2 transactions:
        A normal transaction: buy the stock on day 0 for $1 then sell it on day 2 for $9.
        A short selling transaction: sell the stock on day 3 for $8 then buy back on day 4 for $2.


    --- Example 2 ---
    Input: prices = [12,16,19,19,8,1,19,13,9], k = 3
    Output: 36
    Explanation:
    We can make $36 of profit through 3 transactions:
        A normal transaction: buy the stock on day 0 for $12 then sell it on day 2 for $19.
        A short selling transaction: sell the stock on day 3 for $19 then buy back on day 4 for $8.
        A normal transaction: buy the stock on day 5 for $1 then sell it on day 6 for $19.


    *** Constraints ***
    2 <= prices.length <= 10^3
    1 <= prices[i] <= 10^9
    1 <= k <= prices.length / 2

*/

#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.01% */
/* Space Beats: 5.02% */

/* Time  Complexity: O(N * K) */
/* Space Complexity: O(N * K) */
class Solution {
private:
    vector<vector<vector<vector<long long>>>> memo;

public:
    long long maximumProfit(vector<int>& prices, int k)
    {
        const int N = prices.size();

        // memo[i][k_rem][shortsell][bought] = max profit from day i with k_rem transactions
        memo.assign(N + 1, vector(k + 1, vector(2, vector<long long>(2, -1))));

        return solve(0, k, false, false, prices);
    }

private: 
    long long solve(int i, int k, bool short_sell, bool bought, const vector<int>& prices)
    {
        const int N = prices.size();

        // If past last day:
        if (i == N) 
            return (short_sell || bought) ? LLONG_MIN / 2 : 0;

        // If no transactions left:
        if (k == 0)
        {
            if (!short_sell && !bought) 
                return 0;

            return LLONG_MIN / 2;
        }

        // Return memo if computed
        if (memo[i][k][short_sell][bought] != -1)
            return memo[i][k][short_sell][bought];

        long long best = LLONG_MIN;

        if (!short_sell && !bought)
        {
            // 1) Start a short-sell (will close later)
            long long start_short =  prices[i] + solve(i + 1, k, true, false, prices);

            // 2) Start a normal buy
            long long start_buy   = -prices[i] + solve(i + 1, k, false, true, prices);

            // 3) Skip today
            long long skip        = solve(i + 1, k, false, false, prices);

            best = max( {start_short, start_buy, skip} );
        }
        else if (short_sell)
        {
            // 1) Close the short-sell: consume one transaction
            long long close_short = -prices[i] + solve(i + 1, k - 1, false, false, prices);

            // 2) Hold short position, i.e. "skip", meainig don't buy yet
            long long hold_short  = solve(i + 1, k, true, false, prices);

            best = max(close_short, hold_short);
        }
        else // Bought
        {
            // 1) Close the buy: sell and consume one transaction
            long long close_buy = prices[i] + solve(i + 1, k - 1, false, false, prices);

            // 2) Hold the stock
            long long hold_buy  = solve(i + 1, k, false, true, prices);

            best = max(close_buy, hold_buy);
        }

        // Memoize and return
        return memo[i][k][short_sell][bought] = best;
    }
};
