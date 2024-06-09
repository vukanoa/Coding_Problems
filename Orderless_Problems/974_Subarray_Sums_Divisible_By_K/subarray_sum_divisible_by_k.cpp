#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    974) Subarray Sums Divisible by K
    =================================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, return the number of
    non-empty subarrays that have a sum divisible by k.

    A subarray is a contiguous part of an array.

    ========================================================
    FUNCTION: int subarraysDivByK(vector<int>& nums, int k);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,5,0,-2,-3,1], k = 5
    Output: 7
    Explanation: There are 7 subarrays with a sum divisible by k = 5:
    [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]


    --- Example 2 ---
    Input: nums = [5], k = 9
    Output: 0


    *** Constraints ***
    1 <= nums.length <= 3 * 10^4
    -10^4 <= nums[i] <= 10^4
    2 <= k <= 10^4

*/

class Solution {
public:
    int subarraysDivByK(std::vector<int>& nums, int k)
    {

    }
};



/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 39.34% */
/* Space Beats: 18.24% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int subarraysDivByK(std::vector<int>& nums, int k)
    {
        /*
            Initialize count of subarrays, prefix sum, and hash map for
            remainders.
        */
        int count = 0;
        int prefix_sum = 0;
        std::unordered_map<int, int> prefix_map;
        prefix_map[0] = 1; // To handle subarrays that start from the beginning

        for (int num : nums)
        {
            // Update prefix sum
            prefix_sum += num;

            // Calculate the remainder of the prefix sum divided by k
            int mod = prefix_sum % k;

            // Adjust negative remainders to be positive
            if (mod < 0)
                mod += k;

            // If this remainder has been seen before, it means there are
            // subarrays ending here that are divisible by k
            if (prefix_map.find(mod) != prefix_map.end())
            {
                count += prefix_map[mod];
                prefix_map[mod] += 1;
            }
            else
                prefix_map[mod] = 1;
        }

        return count; // Total number of subarrays divisible by k
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 89.59% */
/* Space Beats: 92.10% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k)
    {
        std::vector<int> mod_k(k, 0);
        mod_k[0] = 1;

        int prefix = 0;

        for(const int& num : nums)
        {
            prefix = (prefix + num) % k;
            prefix += (prefix < 0) ? k : 0;
            mod_k[prefix]++;
        }

        return accumulate(mod_k.begin(), mod_k.end(), 0, [](int sum, int num)
        {
            return sum + num * (num - 1) / 2;
        });
    }
};
