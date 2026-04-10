/*
    ============
    === EASY ===
    ============

    =====================================================
    3740) Minimum Distance Between Three Equal Elements I
    =====================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    A tuple (i, j, k) of 3 distinct indices is good if nums[i] == nums[j] ==
    nums[k].

    The distance of a good tuple is abs(i - j) + abs(j - k) + abs(k - i), where
    abs(x) denotes the absolute value of x.

    Return an integer denoting the minimum possible distance of a good tuple.
    If no good tuples exist, return -1.

    =================================================
    FUNCTION: int minimumDistance(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1,1,3]
    Output: 6
    Explanation:
    The minimum distance is achieved by the good tuple (0, 2, 3).
    (0, 2, 3) is a good tuple because nums[0] == nums[2] == nums[3] == 1. Its
    distance is abs(0 - 2) + abs(2 - 3) + abs(3 - 0) = 2 + 1 + 3 = 6.

    --- Example 2 ---
    Input: nums = [1,1,2,3,2,1,2]
    Output: 8
    Explanation:
    The minimum distance is achieved by the good tuple (2, 4, 6).
    (2, 4, 6) is a good tuple because nums[2] == nums[4] == nums[6] == 2. Its
    distance is abs(2 - 4) + abs(4 - 6) + abs(6 - 2) = 2 + 2 + 4 = 8.

    --- Example 3 ---
    Input: nums = [1]
    Output: -1
    Explanation:
    There are no good tuples. Therefore, the answer is -1.


    *** Constraints ***
    1 <= n == nums.length <= 100
    1 <= nums[i] <= n

*/

#include <climits>
#include <cstdlib>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation problem almost.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  31.72% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int minimumDistance(vector<int>& nums)
    {
        const int N = nums.size();
        int result = INT_MAX;

        unordered_map<int, vector<int>> umap;

        for (int i = 0; i < N; i++)
            umap[nums[i]].push_back(i);

        for (const auto& [num, indices] : umap)
        {
            if (umap[num].size() < 3)
                continue;

            int i = umap[num][0];
            int j = umap[num][1];
            int k = umap[num][2];

            int distance = abs(i - j) + abs(j - k) + abs(k - i);
            result = min(result, distance);

            int idx = 3;
            while (idx < umap[num].size())
            {
                i = j;
                j = k;
                k = umap[num][idx];

                distance = abs(i - j) + abs(j - k) + abs(k - i);
                result   = min(result, distance);

                // Increment
                idx++;
            }
        }

        return result == INT_MAX ? -1 : result;
    }
};
