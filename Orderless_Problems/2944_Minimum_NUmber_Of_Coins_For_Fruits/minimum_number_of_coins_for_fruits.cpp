/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    2944) Minimum Number of Coins for Fruits
    ========================================

    ============
    Description:
    ============

    You are given an 0-indexed integer array prices where prices[i] denotes the
    number of coins needed to purchase the (i + 1)th fruit.

    The fruit market has the following reward for each fruit:

        If you purchase the (i + 1)th fruit at prices[i] coins, you can get any
        number of the next i fruits for free.

    Note that even if you can take fruit j for free, you can still purchase it
    for prices[j - 1] coins to receive its reward.

    Return the minimum number of coins needed to acquire all the fruits.

    ================================================
    FUNCTION: int minimumCoins(vector<int>& prices);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: prices = [3,1,2]
    Output: 4
    Explanation:
        Purchase the 2nd fruit with prices[1] = 1 coin, you are allowed to take
        the 3rd fruit for free. Take the 3rd fruit for free. Note that even
        though you could take the 2nd fruit for free as a reward of buying 1st
        fruit, you purchase it to receive its reward, which is more optimal.

    --- Example 2 ---
    Input: prices = [1,10,1,1]
    Output: 2
    Explanation:
    Purchase the 1st fruit with prices[0] = 1 coin, you are allowed to take the
    2nd fruit for free. Take the 2nd fruit for free. Purchase the 3rd fruit for
    prices[2] = 1 coin, you are allowed to take the 4th fruit for free. Take
    the 4th fruit for free.

    --- Example 3 ---
    Input: prices = [26,18,6,12,49,7,45,45]
    Output: 39
    Explanation:
    Purchase the 1st fruit with prices[0] = 26 coin, you are allowed to take
    the 2nd fruit for free. Take the 2nd fruit for free. Purchase the 3rd fruit
    for prices[2] = 6 coin, you are allowed to take the 4th, 5th and 6th (the
    next three) fruits for free. Take the 4th fruit for free. Take the 5th
    fruit for free. Purchase the 6th fruit with prices[5] = 7 coin, you are
    allowed to take the 8th and 9th fruit for free. Take the 7th fruit for
    free. Take the 8th fruit for free.

    Note that even though you could take the 6th fruit for free as a reward of
    buying 3rd fruit, you purchase it to receive its reward, which is more
    optimal.


    *** Constraints ***
    1 <= prices.length <= 1000
    1 <= prices[i] <= 105

*/

#include <climits>
#include <cstring>
#include <deque>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic "skip-take" Memoization problem.

*/

/* Time  Beats: 18.85% */
/* Space Beats: 28.05% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution {
public:
    int memo[1001][1002];

    int minimumCoins(vector<int>& prices)
    {
        memset(memo, -1, sizeof(memo));

        return solve(0, -1, prices);
    }

private:
    int solve(int idx, int prev, vector<int>& prices)
    {
        const int N = prices.size();

        if (idx >= N)
            return 0;

        if (memo[idx][prev + 1] != -1)
            return memo[idx][prev + 1];

        // Buy
        int buy = prices[idx] + solve(idx + 1, idx, prices);

        // Take
        int take_free = INT_MAX;
        if (idx - prev <= prev + 1)
            take_free = min(take_free, solve(idx + 1, prev, prices));

        return memo[idx][prev + 1] = min(buy, take_free);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 73.79% */
/* Space Beats: 37.24% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution_Deque {
public:
    int minimumCoins(vector<int>& prices)
    {
        const int N = prices.size();
        vector<int> dp(N+1, 0);

        deque<int> deque;

        for (int i = 0; i < N; i++)
        {
            while ( ! deque.empty() && (deque.front()+1)*2 < i+1)
                deque.pop_front();

            while ( ! deque.empty() && dp[deque.back()] + prices[deque.back()] >= dp[i] + prices[i])
                deque.pop_back();

            deque.push_back(i);

            dp[i + 1] = dp[deque.front()] + prices[deque.front()];
        }

        return dp[N];
    }
};
