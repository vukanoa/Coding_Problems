#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ====================================
    995) Number of Consectuive Bit Flips
    ====================================

    ============
    Description:
    ============

    You are given a binary array nums and an integer k.

    A k-bit flip is choosing a subarray of length k from nums and
    simultaneously changing every 0 in the subarray to 1, and every 1 in the
    subarray to 0.

    Return the minimum number of k-bit flips required so that there is no 0 in
    the array. If it is not possible, return -1.

    A subarray is a contiguous part of an array.

    =====================================================
    FUNCTION: int minKBitFlips(vector<int>& nums, int k);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,1,0], k = 1
    Output: 2
    Explanation: Flip nums[0], then flip nums[2].

    --- Example 2 ---
    Input: nums = [1,1,0], k = 2
    Output: -1
    Explanation: No matter how we flip subarrays of size 2, we cannot make the
    array become [1,1,1].

    --- Example 3 ---
    Input: nums = [0,0,0,1,0,1,1,0], k = 3
    Output: 3
    Explanation:
    Flip nums[0],nums[1],nums[2]: nums becomes [1,1,1,1,0,1,1,0]
    Flip nums[4],nums[5],nums[6]: nums becomes [1,1,1,1,1,0,0,0]
    Flip nums[5],nums[6],nums[7]: nums becomes [1,1,1,1,1,1,1,1]


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= k <= nums.length

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.31% */
/* Space Beats: 81.35% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minKBitFlips(std::vector<int>& nums, int k)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int N = nums.size();

        std::vector<bool> flipped(N-k+1, 0);  // Track where flips are made
        int count = 0;
        int flip_x = 0;

        for (int i = 0; i < N; i++)
        {
            if (i >= k)
                flip_x -= flipped[i-k]; // Outside of sized k window

            if ((flip_x & 1) == nums[i])   // Need to flip this window
            {
                if (i+k > N)
                    return -1;  // Not enough elements to flip

                flipped[i] = 1;  // Mark the flip

                flip_x++;  // flip
                count++;
            }
        }
        return count;
    }
};
