#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>

#include <iomanip>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    1626) Best Team With No Conflicts
    =================================

    ============
    Description:
    ============

    You are the manager of a basketball team. For the upcoming tournament, you
    want to choose the team with the highest overall score. The score of the
    team is the sum of scores of all the players in the team.

    However, the basketball team is not allowed to have conflicts. A conflict
    exists if a younger player has a strictly higher score than an older
    player. A conflict does not occur between players of the same age.

    Given two lists, scores and ages, where each scores[i] and ages[i]
    represents the score and age of the ith player, respectively, return the
    highest overall score of all possible basketball teams.

    ====================================================================
    FUNCTION: int bestTeamScore(vector<int>& scores, vector<int>& ages);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: scores = [1,3,5,10,15], ages = [1,2,3,4,5]
    Output: 34
    Explanation: You can choose all the players.


    --- Example 2 ---
    Input: scores = [4,5,6,5], ages = [2,1,2,1]
    Output: 16
    Explanation: It is best to choose the last 3 players. Notice that you are
    allowed to choose multiple people of the same age.


    --- Example 3 ---
    Input: scores = [1,2,3,5], ages = [8,9,10,1]
    Output: 6
    Explanation: It is best to choose the first 3 players. 


    *** Constraints ***
    1 <= scores.length, ages.length <= 1000
    scores.length == ages.length
    1 <= scores[i] <= 10^6
    1 <= ages[i] <= 1000

*/

/* This code gives TLE, even though it's the same Time Complexity */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution_TLE_Memoization {
private:
    struct PairHash {
        int operator () (const std::pair<int, int>& p) const
        {
            auto h1 = std::hash<int>()(p.first);
            auto h2 = std::hash<int>()(p.second);

            return h2 ^ (h1 << 1);
        }
    };
public:
    int bestTeamScore(std::vector<int>& scores, std::vector<int>& ages)
    {
        const int n = scores.size();

        std::vector<std::pair<int, int>> pairs;
        for (int i = 0; i < n; i++)
            pairs.push_back(std::make_pair(scores[i], ages[i]));

        // Sort by scores
        std::sort(pairs.begin(), pairs.end());

        std::unordered_map<std::pair<int, int>, int, PairHash> dp;

        std::function<int(int,int)> dfs;
        dfs = [&](int i, int j) -> int
        {
            if (i == pairs.size())
                return 0;

            if (dp.find(std::make_pair(i, j)) != dp.end())
                return dp[std::make_pair(i, j)];

            int score = pairs[i].first;
            int age   = pairs[i].second;

            int curr_score = 0;
            int curr_age   = 0;
            if (j >= 0)
            {
                curr_score = pairs[j].first;
                curr_age   = pairs[j].second;
            }

            int result = 0;

            int add_this_score  = 0;
            int skip_this_score = 0;

            if (curr_age <= age)
                add_this_score = dfs(i+1, i) + score; // Add score

            skip_this_score = dfs(i+1, j);

            dp[std::make_pair(i, j)] = std::max(add_this_score, skip_this_score);

            return dp[std::make_pair(i, j)];
        };

        return dfs(0, -1);
    }
};





/*
    ------------
    --- IDEA ---
    ------------

    Very similar to LIS(Longest Increasing Subseqence), however this one is a
    bit more challenging because we have to check another condition(age in this
    case).

    It's important that we make a vector of pairs {score[i], age[i]};

    It's important to sort it by the scores and then we're just checking the
    age condition.

    Now it becomes almost equivalent to LIS.

*/

/* Time  Beats: 84.63% */
/* Space Beats: 65.18% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution {
public:
    int bestTeamScore(std::vector<int>& scores, std::vector<int>& ages)
    {
        const int n = scores.size();

        std::vector<std::pair<int, int>> pairs;
        for (int i = 0; i < n; i++)
            pairs.push_back(std::make_pair(scores[i], ages[i]));

        // Sort by scores
        std::sort(pairs.begin(), pairs.end());

        std::vector<int> dp(n);
        dp[0] = pairs[0].first;

        for (int i = 1; i < n; i++)
        {
            int max = pairs[i].first;
            for (int j = 0; j < i; j++)
            {
                if (pairs[j].second <= pairs[i].second)
                    max = std::max(max, dp[j] + pairs[i].first);
            }

            dp[i] = max;
        }

        return *std::max_element(dp.begin(), dp.end());
    }
};


int
main()
{
    Solution sol;

    /* Example 1 */
    // std::vector<int> scores = {1,3,5,10,15};
    // std::vector<int> ages   = {1,2,3,4,5};

    /* Example 2 */
    // std::vector<int> scores = {4,5,6,5};
    // std::vector<int> ages   = {2,1,2,1};

    /* Example 3 */
    // std::vector<int> scores = {1,2,3,5};
    // std::vector<int> ages   = {8,9,10,1};

    /* Example 4 */
    // std::vector<int> scores = {1,7,5,6,11};
    // std::vector<int> ages   = {1,2,3,4,5};

    /* Example 5 */
    std::vector<int> scores = {1,3,5,10,15};
    std::vector<int> ages   = {1,2,5,4,3};

    /* Example 6 */
    // std::vector<int> scores = {1,3,7,3,2,4,10,7,5};
    // std::vector<int> ages   = {4,5,2,1,1,2,4,1,4};


    std::cout << "\n\t===================================";
    std::cout << "\n\t=== BEST TEAM WITH NO CONFLICTS ===";
    std::cout << "\n\t===================================\n";



    /* Write Input */

    bool first = true;
    std::cout << "\n\tScores: [";
    for (auto x: scores)
    {
        if (!first)
            std::cout << ", ";

        std::cout << std::setw(2) << x;
        first = false;
    }
    std::cout << "]";

    first = true;
    std::cout << "\n\tAges:   [";
    for (auto x: ages)
    {
        if (!first)
            std::cout << ", ";

        std::cout << std::setw(2) << x;
        first = false;
    }
    std::cout << "]\n";

    

    /* Solution */
    int  result = sol.bestTeamScore(scores, ages);


    /* Write Output */
    std::cout << "\n\tResult: " << result;

    std::cout << "\n\n";
    return 0;
}
