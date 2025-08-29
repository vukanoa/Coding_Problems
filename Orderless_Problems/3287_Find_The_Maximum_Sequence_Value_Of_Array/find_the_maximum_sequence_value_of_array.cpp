/*
    ============
    === HARD ===
    ============

    ==============================================
    3287) Find the Maximum Sequence Value of Array
    ==============================================

    ============
    Description:
    ============

    You are given an integer array nums and a positive integer k.

    The value of a sequence seq of size 2 * x is defined as:

        (seq[0] OR seq[1] OR ... OR seq[x - 1]) XOR (seq[x] OR seq[x + 1] OR
        ... OR seq[2 * x - 1]).

    Return the maximum value of any subsequence of nums having size 2 * k.

    =================================================
    FUNCTION: int maxValue(vector<int>& nums, int k);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,6,7], k = 1
    Output: 5
    Explanation:
    The subsequence [2, 7] has the maximum value of 2 XOR 7 = 5.

    --- Example 2 ---
    Input: nums = [4,2,5,6,7], k = 2
    Output: 2
    Explanation:
    The subsequence [4, 5, 6, 7] has the maximum value of (4 OR 5) XOR
    (6 OR 7) = 2.


    *** Constraints ***
    2 <= nums.length <= 400
    1 <= nums[i] < 27
    1 <= k <= nums.length / 2

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 69.79% */
/* Space Beats: 60.43% */

/* Time  Complexity: O(N * k * Max_mask) */
/* Space Complexity: O(N * k * Max_mask) */
class Solution {
private:
    bool visited_left [401][201][128] = {};
    bool visited_right[401][201][128] = {};

public:
    int maxValue(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int result = 0;

        vector<int> left_bitmask_min_idx (128, INT_MAX);
        vector<int> right_bitmask_max_idx(128);

        exploreFromLeft (0    , nums, k, k, 0, left_bitmask_min_idx );
        exploreFromRight(N - 1, nums, k, k, 0, right_bitmask_max_idx);

        for (int left_mask = 0; left_mask < 128; ++left_mask)
        {
            for (int right_mask = 0; right_mask < 128; ++right_mask)
            {
                if (left_bitmask_min_idx[left_mask] < right_bitmask_max_idx[right_mask])
                    result = max(result, left_mask ^ right_mask);
            }
        }

        return result;
    }

private:
    void exploreFromLeft(int curr_idx,
                         vector<int>& nums,
                         int remaining_selections,
                         int required_selections,
                         int curr_bitmask,
                         vector<int>& left_bitmask_min_idx)
    {
        if (remaining_selections == 0)
        {
            left_bitmask_min_idx[curr_bitmask] = min(left_bitmask_min_idx[curr_bitmask], curr_idx - 1);
        }
        else if (curr_idx + required_selections < nums.size() && !visited_left[curr_idx][remaining_selections][curr_bitmask])
        {
            visited_left[curr_idx][remaining_selections][curr_bitmask] = true;

            exploreFromLeft(curr_idx + 1, nums, remaining_selections    , required_selections, curr_bitmask                 , left_bitmask_min_idx); // SKIP curr element
            exploreFromLeft(curr_idx + 1, nums, remaining_selections - 1, required_selections, curr_bitmask | nums[curr_idx], left_bitmask_min_idx); // TAKE curr element
        }
    }

    void exploreFromRight(int curr_idx,
                          vector<int>& nums,
                          int remaining_selecitons,
                          int required_selections,
                          int curr_bitmask,
                          vector<int>& right_bitmask_max_idx)
    {
        if (remaining_selecitons == 0)
        {
            right_bitmask_max_idx[curr_bitmask] = max(right_bitmask_max_idx[curr_bitmask], curr_idx + 1);
        }
        else if (curr_idx >= required_selections && !visited_right[curr_idx][remaining_selecitons][curr_bitmask])
        {
            visited_right[curr_idx][remaining_selecitons][curr_bitmask] = true;

            exploreFromRight(curr_idx - 1, nums, remaining_selecitons    , required_selections, curr_bitmask                 , right_bitmask_max_idx); // SKIP curr element
            exploreFromRight(curr_idx - 1, nums, remaining_selecitons - 1, required_selections, curr_bitmask | nums[curr_idx], right_bitmask_max_idx); // TAKE curr element
        }
    }
};
