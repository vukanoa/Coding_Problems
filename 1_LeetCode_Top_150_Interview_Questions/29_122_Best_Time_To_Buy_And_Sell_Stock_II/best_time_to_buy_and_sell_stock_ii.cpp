#include <iostream>

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


/*
	------------
	--- IDEA ---
	------------

	Similar to the first version of this problem.

	Don't buy today if tomorrow if cheaper.
	But here we buy on the first day and then we're just asking if tomorrow's
	price is decreasing, then immediately sell today, and if it's not the end
	of the array(given period) then buy it again on that day when it's cheaper.


	Input: prices = [7, 1, 5, 3, 6, 4]
	                 0  1  2  3  4  5

	But on day 0.

	Tomorrow is cheaper, immediately sell and buy tomorrow.

	Now we bought at price 1(on day 1).

	Tomorrow(Day 2) is not cheaper - Do nothing.

	Tomorrow(Day 3) is cheaper than yesterday(Day 2) - Immediately sell:
		max_profit += (5 - 1) => max_profit += 4
	
	Buy on Day 3 again since that is not the last day.

	Tomorrow(Day 4) is not cheaper than today(Day 3) - Do nothing.

	Tomorrow(Day 5) is indeed cheaper than today(Day 4) - Immediately sell.

	However, since Day 5 is the last Day(Starting from Day 0), we don't want to
	buy it since we would just lose money because we can't sell it afterwards.

	Since we're not subtracting our profit when we're buying, we don't even
	have to worry about that.

	That's the whole idea.

*/

/* Time  Beats: 74.56% */
/* Space Beats: 79.41% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int start = 0;
        int end = 1;

        int max_profit = 0;

        while (end < prices.size())
        {
            if (prices[end - 1] > prices[end])
            {
                max_profit += prices[end - 1] - prices[start];
                start = end;
            }

            end++;
        }

        if (start != prices.size() - 1)
            max_profit += prices[prices.size() - 1] - prices[start];

        return max_profit;
    }
};




/*
	------------
	--- IDEA ---
	------------

	Same Idea, though, much more neatly written.

	Though, now we don't count "end day - start day", but "today - yesterday"
	if today is larger than yesterday(i.e. we're going to make a profit).
	
*/

/* Time  Beats:  100% */
/* Space Beats: 79.41% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Neat{
public:
	int maxProfit(vector<int>& prices)
	{
		int profit = 0;

		for (int i = 1; i < prices.size(); i++)
		{
			if (prices[i] > prices[i - 1])
				profit += prices[i] - prices[i - 1];
		}

			return profit;
		}
};
