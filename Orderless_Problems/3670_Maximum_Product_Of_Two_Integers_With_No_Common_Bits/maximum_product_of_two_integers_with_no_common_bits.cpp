/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    3670) Maximum Product of Two Integers With No Common Bits
    =========================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Your task is to find two distinct indices i and j such that the product
    nums[i] * nums[j] is maximized, and the binary representations of nums[i]
    and nums[j] do not share any common set bits.

    Return the maximum possible product of such a pair. If no such pair exists,
    return 0.

    ==================================================
    FUNCTION: long long maxProduct(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,5,6,7]
    Output: 12
    Explanation:
    The best pair is 3 (011) and 4 (100). They share no set bits and 3 * 4 = 12.

    --- Example 2 ---
    Input: nums = [5,6,4]
    Output: 0
    Explanation:
    Every pair of numbers has at least one common set bit. Hence, the answer is 0.

    --- Example 3 ---
    Input: nums = [64,8,32]
    Output: 2048
    Explanation:
    No pair of numbers share a common bit, so the answer is the product of the
    two maximum elements, 64 and 32 (64 * 32 = 2048).


    *** Constraints ***
    2 <= nums.length <= 10^5
    1 <= nums[i] <= 10^6

*/

#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Requires in-depth explanation)

*/

/* Time  Beats: 54.52% */
/* Space Beats: 26.72% */

/* Time  Complexity: O(N + M * logM) */ // WHere 'M' is 2^msb
/* Space Complexity: O(M)            */
class Solution {
public:
    long long maxProduct(vector<int>& nums)
    {
        long long result = 0;
        const int MAX_N = *max_element(nums.begin(), nums.end());

        int msb = log2(MAX_N); // msb <==> Most Significant Bit

        int max_mask = (1 << (msb + 1)) - 1;
        vector<int> dp(max_mask + 1);

        for (const int& num : nums)
            dp[num] = num;

        for (int bit = 0; bit <= msb; bit++)
        {
            for (int mask = 0; mask < max_mask; mask++)
            {
                if (mask & (1 << bit))
                    dp[mask] = max(dp[mask], dp[mask ^ (1 << bit)]);
            }
        }

        for (const int& num : nums)
            result = max(result, 1LL * num * dp[max_mask ^ num]);

        return result;
    }
};
