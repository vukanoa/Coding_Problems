/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3685) Subsequences Sum After Capping Elements
    =============================================

    ============
    Description:
    ============

    You are given an integer array nums of size n and a positive integer k.

    An array capped by value x is obtained by replacing every element nums[i]
    with min(nums[i], x).

    For each integer x from 1 to n, determine whether it is possible to choose
    a subsequence from the array capped by x such that the sum of the chosen
    elements is exactly k.

    Return a 0-indexed boolean array answer of size n, where answer[i] is true
    if it is possible when using x = i + 1, and false otherwise.

    ============================================================================
    FUNCTION: vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k);
    ============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,3,2,4], k = 5
    Output: [false,false,true,true]
    Explanation:
        For x = 1, the capped array is [1, 1, 1, 1]. Possible sums are
        1, 2, 3, 4, so it is impossible to form a sum of 5.

        For x = 2, the capped array is [2, 2, 2, 2]. Possible sums are
        2, 4, 6, 8, so it is impossible to form a sum of 5.

        For x = 3, the capped array is [3, 3, 2, 3]. A subsequence [2, 3] sums
        to 5, so it is possible.

        For x = 4, the capped array is [4, 3, 2, 4]. A subsequence [3, 2] sums
        to 5, so it is possible.


    --- Example 2 ---
    Input: nums = [1,2,3,4,5], k = 3
    Output: [true,true,true,true,true]
    Explanation:
    For every value of x, it is always possible to select a subsequence from
    the capped array that sums exactly to 3.


    *** Constraints ***
    1 <= n == nums.length <= 4000
    1 <= nums[i] <= n
    1 <= k <= 4000

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (This one requires detailed, slow, in-depth explanation)

*/

/* Time  Beats: 50.48% */
/* Space Beats: 93.60% */

/* Time  Complexity: O(N * logN + N * k) */
/* Space Complexity: O(logN + )          */ // logN is TC for C++'s Sort
class Solution {
public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k)
    {
        const int N = nums.size();
        vector<bool> answer(N, 0);

        /* Sort */
        sort(nums.begin(), nums.end());

        vector<bool> possible_sum(k + 1, false);
        possible_sum[0] = true;

        // possible_sum[i] = can we form sum i using elements STRICTLY LESS THAN curr_cap_value
        // answer[i]       = can we form sum k using all elements with each element capped at i
        int idx = 0;
        for (int curr_cap_val = 1; curr_cap_val <= N; curr_cap_val++)
        {
            while (idx < N && nums[idx] < curr_cap_val)
            {
                // Classic knapsack to find all sums possible using elements STRICTLY LESS THAN curr_cap_value
                for (int target_sum = k; target_sum >= nums[idx]; target_sum--)
                {
                    if (possible_sum[target_sum - nums[idx]])
                        possible_sum[target_sum] = true;
                }

                idx++;
            }

            int num_of_capped_elements = N - idx;

            int capped_elements_used = 0;
            while (capped_elements_used <= num_of_capped_elements && capped_elements_used * curr_cap_val <= k)
            {
                // Can we form the remainder using elements STRICTLY LESS THAN curr_cap_value
                // (that's what possible_sum represents)
                if (possible_sum[k - capped_elements_used * curr_cap_val])
                {
                    answer[curr_cap_val - 1] = true;
                    break;
                }

                // Increment
                capped_elements_used++;
            }
        }

        return answer;
    }
};
