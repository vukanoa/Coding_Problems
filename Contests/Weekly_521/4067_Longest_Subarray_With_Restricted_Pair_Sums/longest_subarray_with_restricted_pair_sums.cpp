/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    4067) Longest Subarray With Restricted Pair Sums
    ================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    A subarray nums[l..r] is valid if there are no three distinct indices i, j,
    and k such that l <= i, j, k <= r and:

        nums[i] + nums[j] == nums[k]

    Return the maximum length of a valid subarray of nums.

    =============================================
    FUNCTION: int maxSubarray(vector<int>& nums);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,5,3,2,1]
    Output: 3
    Explanation:
    Consider the subarray [3, 5, 3]. The pairs of elements at distinct indices
    have the following sums:
        3 + 5 = 8
        3 + 3 = 6, using the two different occurrences of 3
        5 + 3 = 8
    None of these sums is an element at the remaining index, so the subarray is
    valid.
    Every subarray of length 4 contains 2, 3, and 5 at distinct indices, where
    2 + 3 = 5. Therefore, no longer valid subarray exists, and the answer is 3.


    --- Example 2 ---
    Input: nums = [3,4,5,6]
    Output: 4
    Explanation:
    The sums obtained from every pair of elements at distinct indices are 7, 8,
    9, 9, 10, and 11. None of these values appears at the remaining index, so
    the entire array is valid.


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 500

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 87.92% */
/* Space Beats: 54.32% */

/* Time  Complexity: O(N * 500) */
/* Space Complexity: O(500)     */
class Solution {
private:
    bool is_invalid(const vector<int>& freq, int value_to_add)
    {
        for (int curr_val = 1; curr_val <= 500; curr_val++)
        {
            if (freq[curr_val] == 0)
                continue;

            int other_value = value_to_add - curr_val;

            if (other_value >= 0 && other_value <= 500)
            {
                if (other_value == curr_val && freq[curr_val] >= 2)
                    return true;

                if (other_value != curr_val && freq[other_value] > 0)
                    return true;
            }

            int sum_value = value_to_add + curr_val;

            if (sum_value >= 0 && sum_value <= 500)
            {
                if (freq[sum_value] > 0)
                    return true;
            }
        }

        return false;
    }

public:
    int maxSubarray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int left = 0;
        vector<int> freq(501, 0);

        for (int i = 0; i < N; i++)
        {
            while (left < i && is_invalid(freq, nums[i]))
            {
                --freq[nums[left]];
                ++left;
            }

            ++freq[nums[i]];
            result = max(result, i - left + 1);
        }

        return result;
    }
};
