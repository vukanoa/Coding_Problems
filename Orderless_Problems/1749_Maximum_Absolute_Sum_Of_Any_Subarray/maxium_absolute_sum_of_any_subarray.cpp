/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    1749) Maximum Absolute Sum of Any Subarray
    ==========================================

    ============
    Description:
    ============


    You are given an integer array nums. The absolute sum of a subarray
    [numsl, numsl+1, ..., numsr-1, numsr] is
    abs(numsl + numsl+1 + ... + numsr-1 + numsr).

    Return the maximum absolute sum of any (possibly empty) subarray of nums.

    Note that abs(x) is defined as follows:

        If x is a negative integer, then abs(x) = -x.
        If x is a non-negative integer, then abs(x) = x.

    ================================================
    FUNCTION: int maxAbsoluteSum(vector<int>& nums);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,-3,2,3,-4]
    Output: 5
    Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.

    --- Example 2 ---
    Input: nums = [2,-5,1,-4,3,-2]
    Output: 8
    Explanation: The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = abs(-8) = 8.


    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    "pos" represents Max prefix sum so far, and
    "neg" represents Min prefix sum so far.

    Basically if the current element alone is greater than "pos", then take
    that as "pos" since that ensures we'll have the biggest sum so far.

    Similar is true for "neg".

    However, both "pos" and "neg" can be negative at the same time, that's why
    we have to take the ABSOLUTE value of both of this when we're potentially
    updating our "result".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  78.26% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int pos = 0; // Max prefix Sum, essentially "max positive"
        int neg = 0; // Min prefix Sum, essentially "max negative"

        for (int i = 0; i < N; i++)
        {
            pos = nums[i] > (pos + nums[i]) ? nums[i] : pos + nums[i];
            neg = nums[i] < (neg + nums[i]) ? nums[i] : neg + nums[i];

            result = max(result, max(abs(pos), abs(neg)));
        }

        return result;
    }
};
