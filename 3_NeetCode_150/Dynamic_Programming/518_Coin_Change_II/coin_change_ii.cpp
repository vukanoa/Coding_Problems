#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================
    518) Coin Change II
    ===================

    ============
    Description:
    ============

    You are given an integer array coins representing coins of different
    denominations and an integer amount representing a total amount of money.

    Return the number of combinations that make up that amount. If that amount
    of money cannot be made up by any combination of the coins, return 0.

    You may assume that you have an infinite number of each kind of coin.

    The answer is guaranteed to fit into a signed 32-bit integer.

    =====================================================
    FUNCTION: int change(int amount, vector<int>& coins);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: amount = 5, coins = [1,2,5]
    Output: 4
    Explanation: there are four ways to make up the amount:
    5=5
    5=2+2+1
    5=2+1+1+1
    5=1+1+1+1+1


    --- Example 2 ---
    Input: amount = 3, coins = [2]
    Output: 0
    Explanation: the amount of 3 cannot be made up just with coins of 2.


    --- Example 3 ---
    Input: amount = 10, coins = [10]
    Output: 1

    *** Constraints ***
    1 <= coins.length <= 300
    1 <= coins[i] <= 5000
    All the values of coins are unique.
    0 <= amount <= 5000

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is a classical "Unbounded Knapsack" type of Dynamic Programming
    Problem.


    Indexes -->  0     1     2     3     4     5
       |
       |         5     4     3     2     1     0     <---  Amounts
       v      +-----+-----+-----+-----+-----+-----+
       0    1 |     |     |     |     |     |  1  |
              +-----+-----+-----+-----+-----+-----+
       1    2 |     |     |     |     |     |  1  |
              +-----+-----+-----+-----+-----+-----+
       2    5 |     |     |     |     |     |  1  |
            ^ +-----+-----+-----+-----+-----+-----+
            |
            |
    coins----


    So what does, say, dp[1][3] represents?
    It's as if we were asking - "How many combinations sum up to the amount of
    2(3 was just the index) using coins [2, 5](So all the coins from this row
    DOWNWARDS! We don't use coin 1)?"

    So it's a sub-problem. Instead of doing this:
        coins  = [1, 2, 5]
        amount = 5

    We're doing:
        coins  = [2, 5]
        amount = 2

    But what do values inside these cells represent?
    They represent in how many ways can we sum up to the given amount. That's
    why last column(that designates amount 0) is always 1. Why? Because you can
    sum up to 0 using any given set of coins, even if we're not given any set
    of coins(i.e. coins are empty, i.e. coins.size() == 0), we can still
    "sum up" to the amount=0 ii only one way.


    First we must sort all of the coins so that we're certain that
    row=2(starting from 0) represent the 3rd smallest coin(at index 2).

    The we're starting from the position:
        i = coins.size() - 1
        j = amount - 1

    You may wonder - "Why are we starting j from amount-1 if we've constructed
    a matrix of size amount+1?"

    Because the very last column, in any way, designates amount=0 which is
    always going to be 1, so we don't need or can calculate those in a same
    way, those are the base cases.

    So we start from:
        i = coins.size() - 1
        j = amount - 1

    and we go "backwards" until we hit j == -1, then we go "up" and start again
    from j = amount - 1;

    That way, our result of the entire example will be at dp[0][0].

    At the end our matrix "dp" will look like this:


    Indexes -->  0     1     2     3     4     5
       |
       |         5     4     3     2     1     0     <---  Amounts
       v      +-----+-----+-----+-----+-----+-----+
       0    1 |  4  |  3  |  2  |  2  |  1  |  1  |
              +-----+-----+-----+-----+-----+-----+
       1    2 |  1  |  1  |  0  |  1  |  0  |  1  |
              +-----+-----+-----+-----+-----+-----+
       2    5 |  1  |  0  |  0  |  0  |  0  |  1  |
            ^ +-----+-----+-----+-----+-----+-----+
            |
            |
    coins----

*/

/* Time  Beats: 30.53% */
/* Space Beats: 29.20% */

/* Time  Complexity: O(coins.size() * amount) */
/* Space Complexity: O(coins.size() * amount) */
class Solution {
public:
    int change(int amount, vector<int>& coins)
    {
        std::sort(coins.begin(), coins.end());
        std::vector<std::vector<int>> dp(coins.size(), std::vector(amount+1, 0));

        // Fill the last Column of all Rows with 1's, since there is one way to
        // sum up to amount=0 with any amount of coins or even no coins.
        for (int i = 0; i < coins.size(); i++)
            dp[i][amount] = 1;

        for (int i = coins.size()-1; i >= 0; i--)
        {
            for (int j = amount-1; j >= 0; j--)
            {
                int right = 0;
                int down  = 0;

                int curr_amount = amount - j;

                // Right
                if (curr_amount - coins[i] >= 0)
                    right = dp[i][amount - (curr_amount - coins[i])];

                // Down
                if (i+1 < coins.size())
                    down = dp[i+1][j];

                dp[i][j] = right + down;
            }
        }

        return dp[0][0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The IDEA is equivalent, however we can see that we don't have to keep track
    of the whole matrix "dp". We can notice that once we're calculating a value
    for a certain cell, we only use current row and the row below.

    Therefore, it's almost equivalent as the optimization in LeetCode Problem:
        63. "Unique Paths"
    So check that one, it'll be easier afterwards.

    We're always "inheriting" the value from the row below, the only question
    is if we're going to add the "right" portion to it or not.

*/

/* Time  Beats: 61.48% */
/* Space Beats: 71.19% */

/* Time  Complexity: O(coins.size() * amount) */
/* Space Complexity: O(amount) */
class Solution {
public:
    int change(int amount, vector<int>& coins)
    {
        std::sort(coins.begin(), coins.end());

        std::vector<int> dp(amount+1, 0);
        dp[amount] = 1;

        for (int i = coins.size()-1; i >= 0; i--)
        {
            for (int j = amount-1; j >= 0; j--)
            {
                int curr_amount = amount - j;

                /*
                    (Down is always "inherited" since we're using only 1 array
                     and not a matrix)
                */
                // Right
                if (curr_amount - coins[i] >= 0)
                    dp[j] += dp[amount - (curr_amount - coins[i])];
            }
        }

        return dp[0];
    }
};
