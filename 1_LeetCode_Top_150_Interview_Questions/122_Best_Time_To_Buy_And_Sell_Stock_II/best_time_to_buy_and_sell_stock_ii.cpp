/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    122) Best Time to Buy And Sell Stock II
    =======================================

    ============
    Description:
    ============

    You are given an integer array prices where prices[i] is the price of a
    given stock on the ith day.

    On each day, you may decide to buy and/or sell the stock. You can only hold
    at most one share of the stock at any time. However, you can buy it then
    immediately sell it on the same day.

    Find and return the maximum profit you can achieve.

    =============================================
    FUNCTION: int maxProfit(vector<int>& prices);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: prices = [7,1,5,3,6,4]
    Output: 7
    Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5),
    profit = 5-1 = 4.
    Then buy on day 4 (price = 3) and sell on day 5 (price = 6),
    profit = 6-3 = 3.
    Total profit is 4 + 3 = 7.



    --- Example 2 ---
    Input: prices = [1,2,3,4,5]
    Output: 4
    Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5),
    profit = 5-1 = 4.
    Total profit is 4.



    --- Example 3 ---
    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: There is no way to make a positive profit, so we never buy the
    stock to achieve the maximum profit of 0.



    *** Constraints ***
    1 <= prices.length <= 3 * 104
    0 <= prices[i] <= 104

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.95% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Two_Pointers {
public:
    int maxProfit(vector<int>& prices)
    {
        const int N = prices.size();
        int result = 0;

        // Start from a valley
        int L = 0;
        while (L < N-1 && prices[L] > prices[L+1])
            L++;

        // Calculate profit at every local peak
        int R = L+1;
        while (R < N)
        {
            // Keep searching for the local peak
            while (R < N-1 && prices[R] <= prices[R+1])
                R++;
            
            result += prices[R] - prices[L];

            L = R+1;
            // Increment
            R++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is the most intuitive IDEA possible. It's also self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  47.71% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Intuitive {
public:
    int maxProfit(vector<int>& prices)
    {
        const int N = prices.size();
        int profit = 0;

        bool buying = true; // State
        for (int i = 0; i < N; i++)
        {
            if (buying)
            {
                if (i+1 < N && prices[i] < prices[i+1])
                {
                    profit -= prices[i];
                    buying = false;
                }
            }
            else // Selling
            {
                if (i+1 == N || prices[i] > prices[i+1])
                {
                    profit += prices[i];
                    buying = true;
                }
            }
        }

        return profit;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same Idea, though, much more neatly written.

    Though, now we don't count "end day - start day", but "today - yesterday".

    If today is larger than yesterday(i.e. we're going to make a profit), then
    take that profit into account.

*/

/* Time  Beats:  100% */
/* Space Beats: 79.41% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Neat {
public:
    int maxProfit(vector<int>& prices)
    {
        const int N = prices.size();
        int profit = 0;

        for (int i = 1; i < N; i++)
        {
            if (prices[i-1] < prices[i])
                profit += prices[i] - prices[i - 1];
        }

        return profit;
    }
};
