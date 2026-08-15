/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    3702) Longest Subsequence With Non-Zero Bitwise XOR
    ===================================================

    ============
    Description:
    ============


    You are given an integer array nums.

    Return the length of the longest subsequence in nums whose bitwise XOR is
    non-zero. If no such subsequence exists, return 0.

    ===============================
    FUNCTION: `
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3]
    Output: 2
    Explanation:
    One longest subsequence is [2, 3]. The bitwise XOR is computed as
    2 XOR 3 = 1, which is non-zero.

    --- Example 2 ---
    Input: nums = [2,3,4]
    Output: 3
    Explanation:
    The longest subsequence is [2, 3, 4]. The bitwise XOR is computed as
    2 XOR 3 XOR 4 = 5, which is non-zero.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^9

*/

#include <numeric>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  92.93% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int longestSubsequence(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int total_xor    = 0;
        int zeroes_count = 0;

        for (const int& num : nums)
        {
            if (num == 0)
                zeroes_count++;

            total_xor ^= num;
        }

        if (zeroes_count == N) // All zeroes
            return 0;
        
        return total_xor == 0 ? N-1 : N;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   4.61% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int longestSubsequence(vector<int>& nums)
    {
        const int N = nums.size();

        int total_xor = accumulate(nums.begin(), nums.end(), 0, bit_xor<>());
        if (total_xor != 0)
            return N;

        unordered_set<int> uset(nums.begin(), nums.end());

        return (uset.size() == 1 && *uset.begin() == 0) ? 0 : N-1;
    }
};
