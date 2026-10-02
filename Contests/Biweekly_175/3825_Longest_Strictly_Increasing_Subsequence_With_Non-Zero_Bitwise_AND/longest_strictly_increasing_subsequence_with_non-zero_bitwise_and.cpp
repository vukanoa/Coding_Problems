/*
    ==============
    === MEDIUM ===
    ==============

    =======================================================================
    3825) Longest Strictly Increasing Subsequence With Non-Zero Bitwise AND
    =======================================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Return the length of the longest strictly increasing subsequence in nums
    whose bitwise AND is non-zero. If no such subsequence exists, return 0.

    ====================================================
    FUNCTION: int longestSubsequence(vector<int>& nums);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,4,7]
    Output: 2
    Explanation:
    One longest strictly increasing subsequence is [5, 7]. The bitwise AND is 5
    AND 7 = 5, which is non-zero.

    --- Example 2 ---
    Input: nums = [2,3,6]
    Output: 3
    Explanation:
    The longest strictly increasing subsequence is [2, 3, 6]. The bitwise AND
    is 2 AND 3 AND 6 = 2, which is non-zero.

    --- Example 3 ---
    Input: nums = [0,1]
    Output: 1
    Explanation:
    One longest strictly increasing subsequence is [1]. The bitwise AND is 1,
    which is non-zero.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^9

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    A non-zero AND means the elements MUST share AT LEAST one SET-bit.

    Once we know that--Simly perform a LIS(Longest Increasing Subsequence) for
    each bit.

    We go from 0 to 29, inclusive, because (2^30 - 1) is GREATER than 1e9 which
    is the maximum value for nums[i], according to the Constraints of this
    problem.

    We could go <32, but it's not necessary.

*/

/* Time  Beats: 97.97% */
/* Space Beats: 80.71% */

/* Time  Complexity: O(30 * N * logN) */
/* Space Complexity: O(N)             */
class Solution {
public:
    int longestSubsequence(vector<int>& nums)
    {
        int result = 0;

        // Up to (2^30 - 1) because 2^30 is GREATER than 10^9(MAX val for num)
        for (int ith_bit = 0; ith_bit < 30; ith_bit++)
        {
            vector<int> subseq; // LIS for a subsequence where ith_bit is SET

            for (const int& num : nums)
            {
                if ((num & (1 << ith_bit)))
                {
                    if (subseq.empty() || subseq.back() < num)
                    {
                        subseq.push_back(num);
                    }
                    else
                    {
                        *lower_bound(subseq.begin(), subseq.end(), num) = num;
                    }
                }
            }

            if (subseq.size() > result)
                result = subseq.size();
        }

        return result;
    }
};
