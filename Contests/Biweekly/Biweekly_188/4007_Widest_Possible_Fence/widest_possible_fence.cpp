/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    4007) Widest Possible Fence
    ===========================

    ============
    Description:
    ============

    You are given an integer array planks, where planks[i] represents the
    height of the ith wooden plank. Each plank has a width of 1 unit.

    You want to build a fence consisting of planks that all have the same
    height.

    You may either use a plank as is, or combine exactly two distinct original
    planks into a single plank whose height equals the sum of their heights.
    Each original plank can be used at most once, and not all original planks
    need to be used.

    Return the maximum possible width of the fence that can be built.

    ================================================
    FUNCTION: int maximumWidth(vector<int>& planks);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: planks = [1,3,2,5,7,5,4,2,1]
    Output: 4
    Explanation:
    We can have four planks of height 5.
        planks[3] = 5
        planks[5] = 5
        planks[0] + planks[6] = 1 + 4 = 5
        planks[1] + planks[2] = 3 + 2 = 5
    Hence, the maximum width is 4.

    --- Example 2 ---
    Input: planks = [2,3,7]
    Output: 1
    Explanation:
        It is impossible to form two planks of the same height, even after
        combining two distinct original planks.
        Since not all original planks need to be used, we can choose any one
        plank as the fence.
        Therefore, the maximum possible width is 1.


    *** Constraints ***
    1 <= planks.length <= 1000
    1 <= planks[i] <= 10^9

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.02% */
/* Space Beats: 5.53% */

/* Time  Complexity: O(N + UNIQUE_HEIGHTS_SIZE^2) */
/* Space Complexity: O(    UNIQUE_HEIGHTS_SIZE^2) */
class Solution {
public:
    int maximumWidth(vector<int>& planks)
    {
        unordered_map<long long, int> freq;

        for (const int& height : planks)
            ++freq[height];

        vector<long long> unique_heights;
        for (const auto& [height, frequency] : freq)
            unique_heights.push_back(height);

        const int UNIQUE_HEIGHTS_SIZE = unique_heights.size();

        unordered_map<long long, int> how_many_pairs_can_sum_up_to;
        for (int i = 0; i < UNIQUE_HEIGHTS_SIZE; i++)
        {
            long long height        = unique_heights[i];
            long long target_height = 2 * height;

            // Pairs of two IDENTICAL heights (e.g. 7 + 7 = 14)
            how_many_pairs_can_sum_up_to[target_height] += freq[height] / 2;
        }

        for (int i = 0; i < UNIQUE_HEIGHTS_SIZE; i++)
        {
            long long height_1 = unique_heights[i];

            for (int j = i+1; j < UNIQUE_HEIGHTS_SIZE; j++)
            {
                long long height_2 = unique_heights[j];

                how_many_pairs_can_sum_up_to[height_1 + height_2] += min(freq[height_1], freq[height_2]);
            }
        }

        int result = 1;

        for (const auto& [h, f] : freq)
            result = max(result, f + how_many_pairs_can_sum_up_to[h]);

        for (const auto& [h, f] : how_many_pairs_can_sum_up_to)
            result = max(result, freq[h] + f);

        return result;
    }
};
