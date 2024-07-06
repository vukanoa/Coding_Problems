#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === HARD ===
    ============

    ===========================
    1862) Sum of Floored Pairs
    ===========================

    ============
    Description:
    ============

    Given an integer array nums, return the sum of floor(nums[i] / nums[j]) for
    all pairs of indices 0 <= i, j < nums.length in the array. Since the answer
    may be too large, return it modulo 109 + 7.

    The floor() function returns the integer part of the division.

    ===================================================
    FUNCTION: int sumOfFlooredPairs(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,5,9]
    Output: 10
    Explanation:
    floor(2 / 5) = floor(2 / 9) = floor(5 / 9) = 0
    floor(2 / 2) = floor(5 / 5) = floor(9 / 9) = 1
    floor(5 / 2) = 2
    floor(9 / 2) = 4
    floor(9 / 5) = 1
    We calculate the floor of the division for every pair of indices in the
    array then sum them up.


    --- Example 2 ---
    Input: nums = [7,7,7,7,7,7,7]
    Output: 49


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

/* Time  Beats: 18.18% */
/* Space Beats: 85.31% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort
class Solution {
public:
    int mod = 1e9 + 7;

    int sumOfFlooredPairs(std::vector<int>& nums)
    {
        const int n = nums.size();

        // Sort
        std::sort(nums.begin(),nums.end());

        int i = 0;
        long sum = 0;

        while(i < n)
        {
            auto x = std::upper_bound(nums.begin(),nums.end(),nums[i]);

            int j = x - nums.begin(), k = i, c = 2;

            long tmp_sum = 0;
            long duplicates = x - (nums.begin() + i);

            i = j;
            while(j < n)
            {
                int y = nums[k] * c;
                int ind = std::upper_bound(nums.begin(),nums.end(),y - 1) - nums.begin();
                tmp_sum = (tmp_sum + (ind - j) * (c - 1)) % mod;
                j = ind;
                c++;
            }

            tmp_sum = tmp_sum * duplicates + (duplicates * duplicates);
            sum = (sum + tmp_sum) % mod;
        }

        return sum;
    }
};
