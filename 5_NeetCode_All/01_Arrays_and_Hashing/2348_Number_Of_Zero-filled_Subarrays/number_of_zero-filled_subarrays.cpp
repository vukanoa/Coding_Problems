/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    2348) Number of Zero-Filled Subarrays
    =====================================

    ============
    Description:
    ============

    Given an integer array nums, return the number of subarrays filled with 0.

    A subarray is a contiguous non-empty sequence of elements within an array.

    ==========================================================
    FUNCTION: long long zeroFilledSubarray(vector<int>& nums);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,0,0,2,0,0,4]
    Output: 6
    Explanation:
    There are 4 occurrences of [0] as a subarray.
    There are 2 occurrences of [0,0] as a subarray.
    There is no occurrence of a subarray with a size more than 2 filled with 0.
    Therefore, we return 6.


    --- Example 2 ---
    Input: nums = [0,0,0,2,0,0]
    Output: 9
    Explanation:
    There are 5 occurrences of [0] as a subarray.
    There are 3 occurrences of [0,0] as a subarray.
    There is 1 occurrence of [0,0,0] as a subarray.
    There is no occurrence of a subarray with a size more than 3 filled with 0. Therefore, we return 9.


    --- Example 3 ---
    Input: nums = [2,10,2019]
    Output: 0
    Explanation: There is no subarray filled with 0. Therefore, we return 0.


    *** Constraints ***
    1 <= nums.length <= 105
    -109 <= nums[i] <= 109

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The most fundamental Sliding-Window problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  40.61% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long zeroFilledSubarray(std::vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0;

        int L = 0;
        int R = 0;
        while (R < N)
        {
            if (nums[R] == 0)
                result += R - L + 1;
            else
                L = R + 1;

            // Increment
            R++;
        }

        return result;
    }
};
