#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === HARD ===
    ============

    ========================================
    992) Subarrays with K Different Integers
    ========================================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, return the number of good
    subarrays of nums.

    A good array is an array where the number of different integers in that
    array is exactly k.

        For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.

    A subarray is a contiguous part of an array.

    ===============================================================
    FUNCTION: int subarraysWithKDistinct(vector<int>& nums, int k);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1,2,3], k = 2
    Output: 7
    Explanation: Subarrays formed with exactly 2 different integers: [1,2],
                 [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]

    --- Example 2 ---
    Input: nums = [1,2,1,3,4], k = 3
    Output: 3
    Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3],
                 [2,1,3], [1,3,4].


    *** Constraints ***
    1 <= nums.length <= 2 * 10^4
    1 <= nums[i], k <= nums.length

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.19% */
/* Space Beats: 94.64% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_3-Way_Sliding_Window {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k)
    {
        unordered_map<int, int> umap_count;

        int result = 0;

        int left_far  = 0; // Left
        int left_near = 0; // Middle
        int right     = 0; // Right

        while (right < nums.size())
        {
            umap_count[nums[right]]++;

            while (umap_count.size() > k)
            {
                umap_count[nums[left_near]]--;

                if (umap_count[nums[left_near]] == 0)
                    umap_count.erase(nums[left_near]);

                left_near++;
                left_far = left_near;
            }

            while (umap_count[nums[left_near]] > 1)
            {
                umap_count[nums[left_near]]--;
                left_near++;
            }

            if (umap_count.size() == k)
                result += left_near - left_far + 1;

            right++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (This indeed has one additional pass, but it is MUCH simpler to understand)

    This one uses two standard Sliding-Window techniques instead of 3-way
    Sliding-Window.

*/

/* Time  Beats: 84.21% */
/* Space Beats: 62.88% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k)
    {
        int sub_with_max_element_k = subarray_with_atmost_X(nums, k);
        int reduced_sub_with_max_k = subarray_with_atmost_X(nums, k-1);

        return (sub_with_max_element_k - reduced_sub_with_max_k);
    }

private:
    int subarray_with_atmost_X(vector<int>& nums, int k)
    {
        unordered_map<int,int> umap_count;

        int left  = 0;
        int right = 0;

        int result = 0;

        while (right < nums.size())
        {
            umap_count[nums[right]]++;

            while (umap_count.size() > k)
            {
                umap_count[nums[left]]--;

                if (umap_count[nums[left]] == 0)
                    umap_count.erase(nums[left]);

                left++;
            }

            result += right - left + 1; // Basically the size of subarray;
            right++;
        }

        return result;
    }
};
