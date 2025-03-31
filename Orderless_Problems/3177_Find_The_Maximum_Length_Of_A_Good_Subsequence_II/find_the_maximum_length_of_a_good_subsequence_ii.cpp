/*
    ============
    === HARD ===
    ============

    ======================================================
    3177) Find the Maximum Length of a Good Subsequence II
    ======================================================

    ============
    Description:
    ============

    You are given an integer array nums and a non-negative integer k.

    A sequence of integers seq is called good if there are at most k indices i
    in the range [0, seq.length - 2] such that seq[i] != seq[i + 1].

    Return the maximum possible length of a good of nums.

    ======================================================
    FUNCTION: int maximumLength(vector<int>& nums, int k);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1,1,3], k = 2
    Output: 4
    Explanation:
    The maximum length subsequence is [1,2,1,1,3].


    --- Example 2 ---
    Input: nums = [1,2,3,4,5,1], k = 0
    Output: 2
    Explanation:
    The maximum length subsequence is [1,2,3,4,5,1].


    *** Constraints ***
    1 <= nums.length <= 5 * 10^3
    1 <= nums[i] <= 10^9
    0 <= k <= min(50, nums.length)

*/

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 56.97% */
/* Space Beats: 35.15% */

/* Time  Complexity: O(N * K) --> O(N * 1) --> O(N) */
/* Space Complexity: O(N * K) --> O(N * 1) --> O(N) */
class Solution {
public:
    int maximumLength(vector<int>& nums, int k)
    {
        vector<unordered_map<int, int>> dp(k + 1);
        vector<int> result(k + 1, 0);

        for (const int& num : nums)
        {
            for (int curr_k = k; curr_k >= 0; curr_k--)
            {
                dp[curr_k][num] = max(dp[curr_k][num] + 1, (curr_k > 0 ? result[curr_k - 1] + 1 : 0));

                result[curr_k] = max(result[curr_k], dp[curr_k][num]);
            }
        }

        return result[k];
    }
};
