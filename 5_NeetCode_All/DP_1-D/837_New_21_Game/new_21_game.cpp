/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    837) New 21 Game
    ===========================

    ============
    Description:
    ============

    Alice plays the following game, loosely based on the card game "21".

    Alice starts with 0 points and draws numbers while she has less than k
    points. During each draw, she gains an integer number of points randomly
    from the range [1, maxPts], where maxPts is an integer. Each draw is
    independent and the outcomes have equal probabilities.

    Alice stops drawing numbers when she gets k or more points.

    Return the probability that Alice has n or fewer points.

    Answers within 10-5 of the actual answer are considered accepted.

    =====================================================
    FUNCTION: double new21Game(int n, int k, int maxPts);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10, k = 1, maxPts = 10
    Output: 1.00000
    Explanation: Alice gets a single card, then stops.


    --- Example 2 ---
    Input: n = 6, k = 1, maxPts = 10
    Output: 0.60000
    Explanation: Alice gets a single card, then stops.
    In 6 out of 10 possibilities, she is at or below 6 points.


    --- Example 3 ---
    Input: n = 21, k = 17, maxPts = 10
    Output: 0.73278


    *** Constraints ***
    0 <= k <= n <= 10^4
    1 <= maxPts <= 10^4

*/

#include <numeric>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This code gives TLE, but it's an important Solution to understand for this
    problem.

*/

/* This code gives TLE */

/* Time  Complexity: O(k^2) */
/* Space Complexity: O(k)   */
class Solution_TLE {
private:
    unordered_map<int, double> memo;
public:
    double new21Game(int n, int k, int maxPts)
    {
        return dfs(n, k, maxPts, 0);
    }

private:
    double dfs(int n, int k, int maxPts, int score)
    {
        if (score >= k)
            return score <= n ? 1.0 : 0.0;

        if (memo.find(score) != memo.end())
            return memo[score];

        double probability = 0.0;

        for (int i = 1; i <= maxPts; i++)
            probability += dfs(n, k, maxPts, score + i);

        memo[score] = 1.0 * probability / maxPts;

        return memo[score];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 82.83% */
/* Space Beats: 61.37% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    double new21Game(int n, int k, int maxPts)
    {
        if (k == 0 || n >= k + maxPts)
            return 1.0;

        double result = 0.0;

        vector<double> dp(n+1);
        dp[0] = 1.0;

        double curr_sum = 1.0;
        for(int i = 1; i < n+1; i++)
        {
            dp[i] = curr_sum / maxPts;

             if (i < k)
                 curr_sum += dp[i];
             else
                result += dp[i];

             if (i >= maxPts)
                 curr_sum -= dp[i - maxPts];
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 6.59% */
/* Space Beats: 5.41% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    double new21Game(int n, int k, int maxPts)
    {
        if (k == 0)
            return 1.0;

        double window_sum = 0.0;
        for (int i = k; i < k + maxPts; i++)
            window_sum += (i <= n) ? 1 : 0;

        unordered_map<int, double> dp; // Start at score -> probability

        for (int i = k-1; i >= 0; i--)
        {
            dp[i] = window_sum / maxPts;

            double remove = 0;

            if (i + maxPts <= n)
                remove = (dp.find(i + maxPts) != dp.end()) ? dp[i + maxPts] : 1;

            window_sum += dp[i] - remove;
        }

        return dp[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is here for didactic purposes. Only to better explain how we've
    incrementally arrive a the below Solution.

*/

class Solution_TLE_2 {
public:
    double new21Game(int n, int k, int maxPts)
    {
        vector<double> dp(n + 1);
        dp[0] = 1;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= maxPts; j++)
            {
                if (i - j >= 0 && i - j < k)
                    dp[i] += dp[i - j] / maxPts;
            }
        }

        return accumulate(dp.begin() + k, dp.end(), 0.0);
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  6.59% */
/* Space Beats: 26.82% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Optimized {
public:
    double new21Game(int n, int k, int maxPts)
    {
        vector<double> dp(n + 1);
        dp[0] = 1; // dp <==> probability_at_score

        double window_sum_probability = k > 0 ? 1 : 0;
        for (int i = 1; i <= n; i++)
        {
            dp[i] = window_sum_probability / maxPts;

            if (i < k)
                window_sum_probability += dp[i];

            if (i - maxPts >= 0 && i - maxPts < k)
                window_sum_probability -= dp[i - maxPts];

        }

        return accumulate(dp.begin() + k, dp.end(), 0.0);
    }
};
