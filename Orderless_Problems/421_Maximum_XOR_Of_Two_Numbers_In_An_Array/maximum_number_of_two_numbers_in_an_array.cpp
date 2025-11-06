/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    421) Maximum XOR of Two Numbers in an Array
    ===========================================

    ============
    Description:
    ============

    Given an integer array nums, return the maximum result of nums[i] XOR
    nums[j], where 0 <= i <= j < n.

    ================================================
    FUNCTION: int findMaximumXOR(vector<int>& nums);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,10,5,25,2,8]
    Output: 28
    Explanation: The maximum result is 5 XOR 25 = 28.

    --- Example 2 ---
    Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
    Output: 127


    *** Constraints ***
    1 <= nums.length <= 2 * 10^5
    0 <= nums[i] <= 2^31 - 1

*/

#include <unordered_set>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    We are iteratively determining what would be each bit of the final result
    from left to right, i.e. from MSB to LSB.

    We're narrowing down the candidate group iteration by iteration. Example:
    
        a, b, c, d, ..., z          // 26 integers in total

    In first iteration, if we find that:

        a, d, e, h, u

    differs on the MSB(Most Significant Bit), then we're sure that MSB is set.

    In second iteration, we're trying to see if among:

        a, d, e, h, u

    there are at least TWO numbers that make the 2nd MSB differ.
    If there is, then definitely, then 2nd MSB will be set in the final result.

    At this point, maybe the group will shrink from:

        a, d, e, h, u

    to

        a, e, h

    Implicitly, every iteration, we are NARROWING down the candidate group,
    however we do NOT have to track how the group is shrinking, we ONLY care
    about the final result.

*/

/* Time  Beats: 17.97% */
/* Space Beats: 19.26% */

/* Time  Complexity: O(32 * N) ---> O(N) */
/* Space Complexity: O(1)                */
class Solution {
public:
    int findMaximumXOR(vector<int>& nums)
    {
        int result = 0;
        int mask = 0;

        for (int i = 31; i >= 0; i--)
        {
            mask |= (1 << i);

            unordered_set<int> prefixes;
            for (const int& num : nums)
                prefixes.insert(num & mask);

            int candidate = result | (1 << i);

            for (const int& prefix : prefixes)
            {
                if (prefixes.count(candidate ^ prefix))
                {
                    result = candidate;
                    break;
                }
            }
        }

        return result;
    }
};
