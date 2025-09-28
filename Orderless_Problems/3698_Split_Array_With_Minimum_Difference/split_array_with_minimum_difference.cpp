/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    3698) Split Array With Minimum Difference
    =========================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Split the array into exactly two subarrays, left and right, such that left
    is is strictly increasing and right strictly decreasing.

    Return the minimum possible absolute difference between the sums of left
    and right. If no valid split exists, return -1.

    ==================================================
    FUNCTION: long long splitArray(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,2]
    Output: 2

    --- Example 2 ---
    Input: nums = [1,2,4,3]
    Output: 4

    --- Example 3 ---
    Input: nums = [3,1,2]
    Output: -1


    *** Constraints ***
    2 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Messy Implementation.

*/

/* Time  Beats: 78.26% */
/* Space Beats: 77.62% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long splitArray(vector<int>& nums)
    {
        const int N = nums.size();

        if (N == 2)
            return abs(nums[0] - nums[1]);

        long long left_sum = 1LL * nums[0];

        int right_idx = 1;
        for (int i = 1; i < N; i++)
        {
            if (nums[i-1] >= nums[i])
            {
                right_idx = i;
                break;
            }

            left_sum += nums[i];
            right_idx++;
        }

        int last_left_idx = right_idx - 1;
        if (right_idx == N)
        {
            vector<int> copy = nums;

            /* Sort */
            sort(copy.begin(), copy.end());

            if (copy == nums)
            {
                long long total_sum = accumulate(nums.begin(), nums.end(), 0LL);

                return abs((total_sum - nums.back()) - nums.back());
            }

            return abs((left_sum - nums.back()) - nums.back());
        }

        long long right_sum = 1LL * nums[right_idx];

        right_idx++;
        while (right_idx < N)
        {
            if (nums[right_idx - 1] <= nums[right_idx])
                return -1;

            right_sum += nums[right_idx];
            right_idx++;
        }


        return min(abs((left_sum - nums[last_left_idx]) - (right_sum + nums[last_left_idx])), abs(left_sum - right_sum));
    }
};
