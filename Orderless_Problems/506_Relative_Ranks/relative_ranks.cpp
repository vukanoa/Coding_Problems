#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === EASY ===
    ============

    ===========================
    506) Relative Ranks
    ===========================

    ============
    Description:
    ============

    You are given an integer array score of size n, where score[i] is the score
    of the ith athlete in a competition. All the scores are guaranteed to be
    unique.

    The athletes are placed based on their scores, where the 1st place athlete
    has the highest score, the 2nd place athlete has the 2nd highest score, and
    so on. The placement of each athlete determines their rank:

        + The 1st place athlete's rank is "Gold Medal".

        + The 2nd place athlete's rank is "Silver Medal".

        + The 3rd place athlete's rank is "Bronze Medal".

        + For the 4th place to the nth place athlete, their rank is their
          placement number (i.e., the xth place athlete's rank is "x").

    Return an array answer of size n where answer[i] is the rank of the ith
    athlete.

    ===============================================================
    FUNCTION: vector<string> findRelativeRanks(vector<int>& score);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: score = [5,4,3,2,1]
    Output: ["Gold Medal","Silver Medal","Bronze Medal","4","5"]
    Explanation: The placements are [1st, 2nd, 3rd, 4th, 5th].


    --- Example 2 ---
    Input: score = [10,3,8,9,4]
    Output: ["Gold Medal","5","Bronze Medal","Silver Medal","4"]
    Explanation: The placements are [1st, 5th, 3rd, 2nd, 4th].


    *** Constraints ***
    n == score.length
    1 <= n <= 10^4
    0 <= score[i] <= 10^6
    All the values in score are unique.

*/

/*
    ------------
    --- IDEA ---
    ------------

    From an integer vector "score", create a vector of pair<int, int>, where
    the first element in pair is going to be the score of that player and the
    second element in pair is going to be the index at which we've found that
    score in our original vector "score".

    Afterwards, we're going to sort it in a descending order by the first value
    i.e. by the score of a player.

    Consider this example:

              score = [10, 3, 8, 9, 4]
                        0  1  2  3  4

    We are going to create:

        score_pairs = [ {10,0}, {3,1}, {8,2}, {9,3}, {4,4} ]
                           0      1      2      3      4



    After sorting "score_pairs" by the first value in descending order:

        score_pairs = [ {10,0}, {9,3}, {8,2}, {4,4}, {3,1} ]
                           0      1      2      3      4


    At the end we create a vector of strings called "results" of the same size
    as both the vector "score" and "score_pairs".

    Now we simply iterate through our sorted vector of pairs "sorted_pairs" and
    we assign certain string representation to results at index which is
    represented by the second value in the pair in vector of pairs called
    "sorted_pairs".

    1. {10,0}        // i = 0
           |_____
                |
                v
        results[0] = "Gold Medal"


    2. {9.3}         // i = 1
          |______
                |
                v
        results[3] = "Silver Medal"


    3. {8.2}         // i = 2
          |______
                |
                v
        results[2] = "Bronze Medal"


    4. {4,4}         // i = 3
          |
          |______     ------- i+1
                |     |
                v     v
        results[4] = "4"



    4. {3,1}         // i = 4
          |
          |______     ------- i+1
                |     |
                v     v
        results[1] = "5"


    results ["Gold Medal", "5", "Bronze Medal", "Silver Medal", "4"]
                  0         1         2                3         4

    At the end we return "results".

*/

/* Time  Beats: 84.20% */
/* Space Beats: 82.42% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<std::string> findRelativeRanks(std::vector<int>& score)
    {
        const int n = score.size();

        std::vector<std::pair<int, int>> score_pairs;
        for (int i = 0; i < n; i++)
            score_pairs.push_back( {score[i], i} );

        // Sort in descending order
        std::sort(score_pairs.begin(), score_pairs.end(), std::greater<>());


        std::vector<std::string> results(n, "");
        for (int i = 0; i < n; i++)
        {
            int curr_score = score_pairs[i].first;
            int position   = score_pairs[i].second;

            switch (i)
            {
                case 0:
                    results[position] = "Gold Medal";
                    break;

                case 1:
                    results[position] = "Silver Medal";
                    break;

                case 2:
                    results[position] = "Bronze Medal";
                    break;

                default:
                    results[position] = std::to_string(i+1);
            }
        }

        return results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Equivalent to the Solution above, implemented in a different way.

*/

/* Time  Beats: 78.51% */
/* Space Beats: 24.86% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    std::vector<std::string> findRelativeRanks(std::vector<int>& score)
    {
        const int n = score.size();
        std::vector<int> sorted_score = score;

        std::sort(sorted_score.begin(), sorted_score.end(), greater<int>());

        std::vector<std::string> medals = {"Gold Medal", "Silver Medal", "Bronze Medal"};
        std::unordered_map<int, string> umap_rank;

        for (int i = 0; i < n; i++)
        {
            if (i < 3)
                umap_rank[sorted_score[i]] = medals[i];
            else
                umap_rank[sorted_score[i]] = std::to_string(i + 1);
        }

        std::vector<std::string> result;
        for (const int& s : score)
            result.push_back(umap_rank[s]);

        return result;
    }
};
