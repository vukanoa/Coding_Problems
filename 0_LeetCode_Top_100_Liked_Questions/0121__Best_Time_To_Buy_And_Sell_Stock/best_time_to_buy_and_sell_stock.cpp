#include <iostream>
#include <vector>

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

/*
    ------------
    --- IDEA ---
    ------------

    Dynamic Programming.

    NOTE: This Solution is not optimal due to the use of additional vector.
    It also iterates through the vector 2 times instead of 1, however both of
    those are constants so the Time Complexity is O(n) in both Solutions.

    Since we have the insight in the stock market in the next n given days, we
    can calculate the maximum price of the stock from that day until the end of
    the period we're given.

    So we go from the back.
    How does that help us though?

    Consider this First Example:
        [7, 1, 5, 3, 6, 4]

    Our dp would look like:
        [7, 6, 6, 6, 6, 4]

    So intuitively you'd want to say:
    "Find minimum stock price in vector 'prices' and then subtract that from
    the corresponding higher stock price from that day onwards, which resides in
    vector 'dp'"

    However that would be incorrect. Consider this example:
        [ 7, 19, 1, 5, 3, 6, 4]

    Our dp would look like this:
        [19, 19, 6, 6, 6, 6, 4]

    If we were to take the minimum stock price in this given period, we would
    subtract 1 from its corresponding highest value from that day onwards, which
    in this case is 6, so the max would look like it's 5, which is wrong.

    We can clearly notice that the maximum is gained if we buy on day 0 and
    sell on the very next day, day 1.

    If we do that, then it's: 19 - 7 = 12 which is correct.

    So how do we get around this?
    Simply iterate through both of the vector simultaneously and subtract:
        dp[i] - prices[i]

    and if that is greater than the max profit until this point, then update
    variable max.

    Return max.

*/

/* Time  Beats:  5.30% */
/* Space Beats:  5.38% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_DP {
public:
    int maxProfit(std::vector<int>& prices)
    {
        int n = prices.size();
        std::vector<int> dp(n, 0);
        dp[n-1] = prices[n-1];

        // i + 1 is "previous", since we are iterating backwards
        for (int i = n-2; i >= 0; i--)
            dp[i] = std::max(dp[i + 1], prices[i]);

        int max = 0;
        for (int i = 0; i < n; i++)
            max = std::max(max, dp[i] - prices[i]);

        return max;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Sliding Window technique.

    Imagine a coordinate system.
    Values on the Y axis are the prices.
    Values on the X axis are the days.

    We put "left"  to point to 0th day.
    We put "right" to point to 1st day.

    If we find that prices[right] is lower than prices[left](which is the
    current day) then we make "left" point to "right" and we increment "right"
    by one.
    We don't want to buy it today if tomorrow's price is going to be lower.

    However, if prices[right] is greater than prices[left], meaning we would
    make some profit, then calculate if that profit is the maximum and also
    increment "right" by one, but only "right", "left" remains fixed.

    Once we get "right" pointer to the end of the array "prices" we are done.
    Just return "max".

    We are sure that this is the maximum since if we were to find out that some
    other value was lower than our fixed "left" pointer, we would've moved it
    and calculate profit from that point.

    We pass through the array only once, thus the Complexity is O(n).
*/

/* Time  Beats: 82.77% */
/* Space Beats: 57.32% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Sliding_Window {
public:
    int maxProfit(std::vector<int>& prices)
    {
        int left  = 0;
        int right = 1;

        int max = 0;

        while (right < prices.size())
        {
            if (prices[left] < prices[right])
                max = std::max(max, prices[right] - prices[left]);
            else
                left = right;

            right++;
        }

        return max;
    }
};


int
main()
{
    Solution_DP             sol_dp;
    Solution_Sliding_Window sol_sliding;

    /* Example 1 */
    std::vector<int> prices = {7, 1, 5, 3, 6, 4};

    /* Example 2 */
    // std::vector<int> prices = {7, 6, 4, 3, 1};

    std::cout << "\n\t=======================================";
    std::cout << "\n\t=== BEST TIME TO BUY AND SELL STOCK ===";
    std::cout << "\n\t=======================================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tPrices: [";
    for (auto x: prices)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    // int max = sol_dp.maxProfit(prices);
    int max = sol_sliding.maxProfit(prices);


    /* Write Output */
    std::cout << "\n\tMax profit is: " << max << "\n\n";


    return 0;
}
