#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    1590) Make Sum Divisible by P
    =============================

    ============
    Description:
    ============

    Given an array of positive integers nums, remove the smallest subarray
    (possibly empty) such that the sum of the remaining elements is divisible
    by p. It is not allowed to remove the whole array.

    Return the length of the smallest subarray that you need to remove, or -1
    if it's impossible.

    A subarray is defined as a contiguous block of elements in the array.

    ====================================================
    FUNCTION: int minSubarray(vector<int>& nums, int p);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,1,4,2], p = 6
    Output: 1
    Explanation: The sum of the elements in nums is 10, which is not divisible
                 by 6. We can remove the subarray [4], and the sum of the
                 remaining elements is 6, which is divisible by 6.


    --- Example 2 ---
    Input: nums = [6,3,5,2], p = 9
    Output: 2
    Explanation: We cannot remove a single element to get a sum divisible by 9.
                 The best way is to remove the subarray [5,2], leaving us with
                 [6,3] with sum 9.


    --- Example 3 ---
    Input: nums = [1,2,3], p = 3
    Output: 0
    Explanation: Here the sum is 6. which is already divisible by 3. Thus we do
                 not need to remove anything.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    1 <= p <= 10^9

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 88.43% */
/* Space Beats: 73.78% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int minSubarray(vector<int>& nums, int p)
    {
        // Use long long to avoid overflow
        long long totalSum = std::accumulate(nums.begin(), nums.end(), 0L);

        int remainder = totalSum % p;

        // If the total sum is already divisible by p, return 0
        if (remainder == 0)
            return 0;

        return findSmallestSubarray(nums, p, remainder);
    }

private:
    int findSmallestSubarray(vector<int>& nums, int p, int remainder)
    {
        long long prefix_sum = 0; // Use long long to avoid overflow
        int min_length = nums.size();

        unordered_map<int, int> prefix_map;
        prefix_map[0] = -1; // Initial condition for no subarray

        for (int i = 0; i < nums.size(); i++)
        {
            prefix_sum += nums[i];
            int target_remainder = (prefix_sum % p - remainder + p) % p;

            if (prefix_map.find(target_remainder) != prefix_map.end())
                min_length = min(min_length, i - prefix_map[target_remainder]);

            prefix_map[prefix_sum % p] = i;
        }

        return min_length < nums.size() ? min_length : -1;
    }
};
