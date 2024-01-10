#include <iostream>
#include <vector>

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
public:
    double new21Game(int n, int k, int maxPts)
    {
        std::unordered_map<int, double> cache;

        return dfs(n, k, maxPts, 0, cache);
    }

private:
    double dfs(int n,
               int k,
               int maxPts,
               int score,
               std::unordered_map<int, double>& cache)
    {
        if (score >= k)
            return score <= n ? 1.0 : 0.0;

        if (cache.find(score) != cache.end())
            return cache[score];

        double probability = 0;

        for (int i = 1; i <= maxPts; i++)
            probability += dfs(n, k, maxPts, score + i, cache);

        cache[score] = 1.0 * probability / maxPts;

        return cache[score];
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
        if(k == 0 || n >= k + maxPts)
            return 1.0;

        std::vector<double> dp(n+1);
        dp[0] = 1.0;

        double curr_sum = 1.0;
        double result = 0.0;
        for(int i = 1; i < n+1; i++)
        {
            dp[i] = curr_sum / maxPts;

             if(i < k)
                 curr_sum += dp[i];
             else
                result += dp[i];

             if(i >= maxPts)
                 curr_sum -= dp[i-maxPts];
        }

        return result;
    }
};
