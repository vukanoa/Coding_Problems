/*
    ============
    === EASY ===
    ============

    ====================================
    121) Best Time to Buy and Sell Stock
    ====================================

    ============
    Description:
    ============

    You are given an array "prices" where "prices[i]" is the price of a given
    stock on the "i"-th day.

    You want to maximize your profit by choosing a single day to buy one stock
    and choosing a different day in the future to sell that stock.

    Return the maximum profit you can achieve from this transaction. If you
    cannot achieve any profit, return 0.

    ============================================
    FUNCTION: int maxProfit(vector<int>& prices);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  prices = [7, 1, 5, 3, 6, 4]
    Output: 5

    --- Example 2 ---
    Input:  prices = [7, 6, 4, 3, 1]
    Output: 0

    *** Constraints ***
    1 <= prices.length <= 10^5
    0 <= prices[i] <= 10^4

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Fundamental "Sliding Window" technique.

    Put L at day_0 and R at day_1, initially.

    If at any point we find that prices[R] is LOWER than prices[L], then L
    becomes R, meaning we want to buy at that new time.

    However, in any case, we want to count the maximum difference between:
        
        prices[R] - prices{L]

    At any given time.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  59.81% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxProfit(vector<int>& prices)
    {
        const int N = prices.size();
        int result = 0;

        int L = 0;
        int R = 1;
        while (R < N)
        {
            if (prices[L] > prices[R])
                L = R;

            result = max(result, prices[R] - prices[L]);

            // Increment
            R++;
        }

        return result;
    }
};
