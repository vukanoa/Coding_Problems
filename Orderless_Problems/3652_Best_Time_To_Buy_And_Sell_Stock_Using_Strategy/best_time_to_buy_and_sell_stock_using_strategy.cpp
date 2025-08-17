/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    3652) Best Time to Buy and Sell Stock using Strategy
    ====================================================

    ============
    Description:
    ============

    You are given two integer arrays prices and strategy, where:

        + prices[i] is the price of a given stock on the ith day.

        + strategy[i] represents a trading action on the ith day, where:
            -1 indicates buying one unit of the stock.
            0 indicates holding the stock.
            1 indicates selling one unit of the stock.

    You are also given an even integer k, and may perform at most one
    modification to strategy. A modification consists of:

        + Selecting exactly k consecutive elements in strategy.
        + Set the first k / 2 elements to 0 (hold).
        + Set the last k / 2 elements to 1 (sell).

    The profit is defined as the sum of strategy[i] * prices[i] across all days.

    Return the maximum possible profit you can achieve.

    =====
    Note: There are no constraints on budget or stock ownership, so all buy and
          sell operations are feasible regardless of past actions.
    =====

    =================================================================================
    FUNCTION: long long maxProfit(vector<int>& prices, vector<int>& strategy, int k);
    =================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: prices = [4,2,8], strategy = [-1,0,1], k = 2
    Output: 10

    --- Example 2 ---
    Input: prices = [5,4,3], strategy = [1,1,0], k = 2
    Output: 9


    *** Constraints ***
    2 <= prices.length == strategy.length <= 10^5
    1 <= prices[i] <= 10^5
    -1 <= strategy[i] <= 1
    2 <= k <= prices.length
    k is even

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Tricky prblem for a Q1 on a Contest.

    TODO

*/

/* Time  Beats: 37.50% */
/* Space Beats: 37.50% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k)
    {
        const int N = prices.size();
        long long result = 0;

        vector<long long> prefix_sum;
        for (const int& p : prices)
            prefix_sum.push_back(1LL * p);

        /* Prefix Sum */
        partial_sum(prefix_sum.begin(), prefix_sum.end(), prefix_sum.begin());

        vector<long long> prefix_mul(N, 0);
        prefix_mul[0] = 1LL * prices[0] * strategy[0];

        for (int i = 1; i < N; i++)
            prefix_mul[i] += 1LL * prefix_mul[i-1] + 1LL * prices[i] * strategy[i];

        result = prefix_mul.back();

        for (int i = k-1; i < N; i++)
        {
            long long x;

            if (i == k-1)
            {
                x = prefix_mul.back() - prefix_mul[i] + (prefix_sum[i] - prefix_sum[i - (k/2)]);

            }
            else
            {
                x = prefix_mul.back() - prefix_mul[i] + (prefix_sum[i] - prefix_sum[i - (k/2)]) + prefix_mul[i - k];
            }

            if (x > result)
                result = x;
        }

        return result;
    }
};
