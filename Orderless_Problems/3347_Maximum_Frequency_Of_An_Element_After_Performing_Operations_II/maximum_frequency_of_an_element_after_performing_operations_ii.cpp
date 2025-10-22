/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================================
    3347) Maximum Frequency of an Element After Performing Operations II
    ====================================================================

    ============
    Description:
    ============

    You are given an integer array nums and two integers k and numOperations.

    You must perform an operation numOperations times on nums, where in each
    operation you:

        + Select an index i that was not selected in any previous operations.
        + Add an integer in the range [-k, k] to nums[i].

    Return the maximum possible frequency of any element in nums after
    performing the operations.

    ========================================================================
    FUNCTION: int maxFrequency(vector<int>& nums, int k, int numOperations);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,4,5], k = 1, numOperations = 2
    Output: 2
    Explanation:
    We can achieve a maximum frequency of two by:
        Adding 0 to nums[1], after which nums becomes [1, 4, 5].
        Adding -1 to nums[2], after which nums becomes [1, 4, 4].

    --- Example 2 ---
    Input: nums = [5,11,20,20], k = 5, numOperations = 1
    Output: 2
    Explanation:
    We can achieve a maximum frequency of two by:
        Adding 0 to nums[1].


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    0 <= k <= 10^9
    0 <= numOperations <= nums.length

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 66.35% */
/* Space Beats: 91.00% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Because of the C++'s "Intro Sort"
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) 
    {
        const int N = nums.size();

        /* Sort */
        sort(nums.begin(), nums.end()); // O(logN)

        int max_freq = 1;

        for (int i = 0; i < N-1; i++) 
        {
            max_freq = max(calculate_max_frequency_within_range(nums, nums[i]    , k, numOperations), max_freq);
            max_freq = max(calculate_max_frequency_within_range(nums, nums[i] - k, k, numOperations), max_freq);
            max_freq = max(calculate_max_frequency_within_range(nums, nums[i] + k, k, numOperations), max_freq);
        }

        return max_freq;
    }

private:
    int calculate_max_frequency_within_range(vector<int>& nums, int target_number, int k, int numOperations) 
    {
        long long target_number_long = target_number;
        long long allowed_difference_long = k;

        int lower_index_of_target = lower_bound(nums.begin(), nums.end(), target_number_long) - nums.begin();
        int upper_index_of_target = upper_bound(nums.begin(), nums.end(), target_number_long) - nums.begin();

        int lower_index_of_range_start = lower_bound(nums.begin(), nums.end(), target_number_long - allowed_difference_long) - nums.begin();
        int upper_index_of_range_end   = upper_bound(nums.begin(), nums.end(), target_number_long + allowed_difference_long) - nums.begin();

        int elements_outside_target_range = (upper_index_of_range_end - upper_index_of_target) + (lower_index_of_target - lower_index_of_range_start);

        return min(numOperations, elements_outside_target_range) + (upper_index_of_target - lower_index_of_target);
    }
};
