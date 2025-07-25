#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    1248) Count Number of Nice Subarrays
    ====================================

    ============
    Description:
    ============

    Given an array of integers nums and an integer k. A continuous subarray is
    called nice if there are k odd numbers on it.

    Return the number of nice sub-arrays.

    ==========================================================
    FUNCTION: int numberOfSubarrays(vector<int>& nums, int k);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,2,1,1], k = 3
    Output: 2
    Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].

    --- Example 2 ---
    Input: nums = [2,4,6], k = 1
    Output: 0
    Explanation: There are no odd numbers in the array.

    --- Example 3 ---
    Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
    Output: 16

    *** Constraints ***
    1 <= nums.length <= 50000
    1 <= nums[i] <= 10^5
    1 <= k <= nums.length

*/

/* Time  Beats: 74.98% */
/* Space Beats: 36.89% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_One_Pass {
public:
    int numberOfSubarrays(std::vector<int>& nums, int k)
    {
        int result = 0;
        int count  = 0;

        int left  = 0;
        int right = 0;

        while (right < nums.size())
        {
            if (nums[right] & 1) // If it's odd
            {
                k--;
                count = 0;
            }

            while (k == 0)
            {
                count++;
                k += (nums[left++] & 1); // If it's odd
            }
            result += count;

            right++; // Extend window
        }

        return result;
    }
};





/* Time  Beats: 19.63% */
/* Space Beats: 16.63% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Hashing {
public:
    int numberOfSubarrays(vector<int>& nums, int k)
    {
        int curr_sum = 0;
        int subarrays = 0;
        unordered_map<int, int> prefix_sum;
        prefix_sum[curr_sum] = 1;

        for (int i = 0; i < nums.size(); i++)
        {
            curr_sum += nums[i] % 2;

            if (prefix_sum.find(curr_sum - k) != prefix_sum.end())
                subarrays = subarrays + prefix_sum[curr_sum - k];
            
            prefix_sum[curr_sum]++;
        }

        return subarrays;
    }
};
