#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3097) Shortest Subarray With OR at Least K II
    =============================================

    ============
    Description:
    ============

    You are given an array nums of non-negative integers and an integer k.

    An array is called special if the bitwise OR of all of its elements is at
    least k.

    Return the length of the shortest special non-empty subarray of nums, or
    return -1 if no special subarray exists.

    ==============================================================
    FUNCTION: int minimumSubarrayLength(vector<int>& nums, int k);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3], k = 2
    Output: 1
    Explanation:
    The subarray [3] has OR value of 3. Hence, we return 1.


    --- Example 2 ---
    Input: nums = [2,1,8], k = 10
    Output: 3
    Explanation:
    The subarray [2,1,8] has OR value of 11. Hence, we return 3.


    --- Example 3 ---
    Input: nums = [1,2], k = 0
    Output: 1
    Explanation:
    The subarray [1] has OR value of 1. Hence, we return 1.


    *** Constraints ***
    1 <= nums.length <= 2 * 10^5
    0 <= nums[i] <= 10^9
    0 <= k <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 51.65% */
/* Space Beats: 97.77% */

/* Time  Complexity: O(n * 32) --> O(n) */
/* Space Complexity: O(32)     --> O(1) */
class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k)
    {
        vector<int> count(32, 0);
        int start = 0;
        int end   = 0;

        int min_length = INT_MAX;

        while (end < nums.size())
        {
            update_bits(count, nums[end], 1);

            while (start <= end && get_val(count) >= k)
            {
                min_length = min(min_length, end - start + 1);
                update_bits(count, nums[start], -1);
                start++;
            }

            end++;
        }

        return min_length == INT_MAX ? -1 : min_length;
    }

private:
    void update_bits(vector<int>& count, int num, int val)
    {
        for (int i = 0; i < 32; i++)
        {
            if ((num >> i) & 1)
                count[i] += val;
        }
    }

    int get_val(const vector<int>& count)
    {
        int result = 0;
        for (int i = 0; i < 32; i++)
        {
            if (count[i] > 0)
                result |= (1 << i);
        }

        return result;
    }
};
