/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    3332) Maximum Points Tourists Can Earn
    ======================================

    ============
    Description:
    ============

    You are given two integers, n and k, along with two 2D integer arrays,
    stayScore and travelScore.

    A tourist is visiting a country with n cities, where each city is directly
    connected to every other city. The tourist's journey consists of exactly k
    0-indexed days, and they can choose any city as their starting point.

    Each day, the tourist has two choices:

    Stay in the current city: If the tourist stays in their current city curr
    during day i, they will earn stayScore[i][curr] points. Move to another
    city: If the tourist moves from their current city curr to city dest, they
    will earn travelScore[curr][dest] points.

    Return the maximum possible points the tourist can earn.

    =======================================================================================================
    FUNCTION: int maxScore(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore);
    =======================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, k = 1, stayScore = [[2,3]], travelScore = [[0,2],[1,0]]
    Output: 3
    Explanation:
    The tourist earns the maximum number of points by starting in city 1 and staying in that city.

    --- Example 2 ---
    Input: n = 3, k = 2, stayScore = [[3,4,2],[2,1,2]], travelScore = [[0,2,1],[2,0,4],[3,2,0]]
    Output: 8
    Explanation:
    The tourist earns the maximum number of points by starting in city 1, staying in that city on day 0, and traveling to city 2 on day 1.


    *** Constraints ***
    1 <= n <= 200
    1 <= k <= 200
    n == travelScore.length == travelScore[i].length == stayScore[i].length
    k == stayScore.length
    1 <= stayScore[i][j] <= 100
    0 <= travelScore[i][j] <= 100
    travelScore[i][i] == 0

*/

#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Classic Memoization problem with states.

*/

/* Time  Beats: 28.18% */
/* Space Beats: 12.24% */

/* Time  Complexity: O(n^2 * k) */
/* Space Complexity: O(n * k)   */
class Solution {
public:
    int maxScore(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore)
    {
        int result = 0;
        vector<vector<int>> dp(n, vector<int>(k,-1));

        for(int i = 0; i < n; i++)
            result = max(result, dfs(i, 0 , n, k, stayScore, travelScore, dp));

        return result;
    }

private:
    int dfs(int city, int day, int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore, vector<vector<int>>& dp)
    {
        if (city >= n || day > k-1)
            return 0;

        if (dp[city][day] != -1)
            return dp[city][day];

        int stay = stayScore[day][city] + dfs(city, day+1, n, k, stayScore, travelScore, dp);
        int move = 0;
        for (int next_city = 0; next_city < n; next_city++)
            move = max(move, travelScore[city][next_city] + dfs(next_city, day+1, n, k, stayScore, travelScore, dp));

        return dp[city][day] = max(move, stay);
    }
};
