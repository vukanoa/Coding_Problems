/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    983) Minimum Cost For Tickets
    =============================

    ============
    Description:
    ============

    You have planned some train traveling one year in advance. The days of the
    year in which you will travel are given as an integer array days. Each day
    is an integer from 1 to 365.

    Train tickets are sold in three different ways:

        a 1-day pass is sold for costs[0] dollars,
        a 7-day pass is sold for costs[1] dollars, and
        a 30-day pass is sold for costs[2] dollars.

    The passes allow that many days of consecutive travel.

        For example, if we get a 7-day pass on day 2, then we can travel for 7
        days: 2, 3, 4, 5, 6, 7, and 8.

    Return the minimum number of dollars you need to travel every day in the
    given list of days.

    ====================================================================
    FUNCTION: int mincostTickets(vector<int>& days, vector<int>& costs);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: days = [1,4,6,7,8,20], costs = [2,7,15]
    Output: 11
    Explanation: For example, here is one way to buy passes that lets you
    travel your travel plan:
    On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
    On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3,
    4, ..., 9.
    On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
    In total, you spent $11 and covered all the days of your travel.


    --- Example 2 ---
    Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
    Output: 17
    Explanation: For example, here is one way to buy passes that lets you
    travel your travel plan:
    On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1,
    2, ..., 30.
    On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
    In total, you spent $17 and covered all the days of your travel.


    *** Constraints ***
    1 <= days.length <= 365
    1 <= days[i] <= 365
    days is in strictly increasing order.
    costs.length == 3
    1 <= costs[i] <= 1000

*/

#include <climits>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Simple Memoization.

    There is a more efficient approach down below - Bottom-Up.

*/

/* Time  Beats:  9.79% */
/* Space Beats: 11.58% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Memoization {
public:
    int mincostTickets(std::vector<int>& days, std::vector<int>& costs)
    {
        std::unordered_map<int, int> dp;

        // O(30 * n) -> O(n)
        return dfs(days, costs, 0, dp);
    }

private:
    int dfs(std::vector<int>& days, std::vector<int>& costs, int i, std::unordered_map<int, int>& dp)
    {
        if (i == days.size())
            return 0;
        else if (dp.find(i) != dp.end())
            return dp[i];

        dp[i] = dfs(days, costs, i+1, dp) + *std::min_element(costs.begin(), costs.end());

        // O(30) -> O(1)
        for (int j = i+1; j < days.size(); j++)
        {
            if (days[j] < days[i] + 7)
                dp[i] = std::min(dp[i], costs[1] + dfs(days, costs, j+1, dp));

            if (days[j] < days[i] + 30)
                dp[i] = std::min(dp[i], costs[2] + dfs(days, costs, j+1, dp));
            else
                break;
        }

        return dp[i];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    LIS type of DP.

    LIS = Longest Increasing Subsequence.

*/

/* Time  Beats:   100% */
/* Space Beats: 66.45% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Bottom_Up {
public:
    int mincostTickets(std::vector<int>& days, std::vector<int>& costs)
    {
        const int n = days.size();
        std::vector<int> dp(n+1, 0);

        // O(30 * n) -> O(n)
        for (int i = n-1; i >= 0; i--)
        {
            dp[i] = dp[i+1] + *std::min_element(costs.begin(), costs.end());

            // O(30) -> O(1)
            for (int j = i+1; j < n; j++)
            {
                if (days[j] < days[i] + 7)
                    dp[i] = std::min(dp[i], costs[1] + dp[j + 1]);

                if (days[j] < days[i] + 30)
                    dp[i] = std::min(dp[i], costs[2] + dp[j + 1]);
                else
                    break;
            }
        }

        return dp[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Essentially the same as the above one, however it's a reversed process.
    We're starting from index 0 and then we always "go back" to determine the
    absolute minimum up to that day.

    In the above Solution we've done the other way. We started from the back
    and then we always "go forward" to determine the absolute minimum.

    I believe this one makes more sense, but it's the best to read them both.

    The crux of this Solutions is:
        1. What is the minimum $$ we have to spend if we only have the very
           first element in our vector 'days'?

        2. What is the minimum $$ we have to spend if we only have the first
           two elements in our vector 'days'?

        3. What is the minimum $$ we have to spend if we only have the first
           three elements in our vector 'days'?

        4. What is the minimum $$ we have to spend if we only have the first
           four elements in our vector 'days'?
        ...

        n. What is the minimum $$ we have to spend if we have all the elements
           in our vector 'days'?


    In each step(except step 1) we are are resting on the previous best
    calculations.

    I'd say that, in terms of thinking, it's a "combination" of Problems:
        1. Coin Change and
        2. LIS (Longest Increasing Subsequence)

    If you've solved these two and you genuinely understand the logic behind
    them, them you're almost certainly going to come up with a Solution for
    this one.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  92.79% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up_Reverse {
public:
    int mincostTickets(std::vector<int>& days, std::vector<int>& costs)
    {
        const int n = days.size();
        std::vector<int> dp(n, INT_MAX);
        dp[0] = std::min( {costs[0], costs[1], costs[2]} );

        for (int i = 1; i < n; i++)
        {
            /* 1-day pass */
            dp[i] = std::min(dp[i], costs[0] + dp[i-1]);

            int start = days[i];
            int x;

            /* 7-day pass */
            x = i-1;
            while (x >= 0 && days[x] > start-7)
                x--;

            if (x >= 0)
                dp[i] = std::min(dp[i], costs[1] + dp[x]);
            else
                dp[i] = std::min(dp[i], costs[1]);

            /* 30-day pass */
            x = i-1;
            while (x >= 0 && days[x] > start-30)
                x--;

            if (x >= 0)
                dp[i] = std::min(dp[i], costs[2] + dp[x]);
            else
                dp[i] = std::min(dp[i], costs[2]);
        }

        return dp[n-1];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but this one looks and feels much more similar to: "Coin
    Change" problem, and thus is much more readable and easier to grasp.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  45.35% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up_Like_Coin_Change {
public:
    int mincostTickets(std::vector<int>& days, std::vector<int>& costs)
    {
        vector<pair<int,int>> price_periods = {
            {costs[0],  1},
            {costs[1],  7},
            {costs[2], 30}
        };

        vector<int> dp(days.back() + 1, INT_MAX);
        dp[0] = 0;

        int idx_unprocessed_day = 0;
        for (int i = 1; i <= days.back(); i++)
        {
            if (days[idx_unprocessed_day] == i)
            {
                for (const auto& [price, period] : price_periods)
                {
                    int prev_day = std::max(0, i - period);
                    dp[i] = std::min(dp[i], price + dp[prev_day]);
                }

                idx_unprocessed_day++;
            }
            else
            {
                dp[i] = dp[i-1];
            }
        }

        return dp[days.back()];
    }
};
