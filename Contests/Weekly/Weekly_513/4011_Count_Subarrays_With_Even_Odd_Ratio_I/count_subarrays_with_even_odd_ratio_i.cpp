/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    4011) Count Subarrays with Even Odd Ratio
    =========================================

    ============
    Description:
    ============

    You are given an integer array nums and two integers a and b.

    For a subarray, let:

        x be the number of even elements.
        y be the number of odd elements.

    The ratio of even to odd elements in a subarray is defined as x / y, where
    ratios are compared by their exact rational values.

    A subarray is considered valid if:

        y > 0, and
        x / y <= a / b.

    Return the number of valid subarrays in nums.

    ===================================================================
    FUNCTION: int countRatioSubarrays(vector<int>& nums, int a, int b);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1,2], a = 3, b = 2
    Output: 7
    The following are the valid subarrays:
    Subarray     Values         Even Count  Odd Count    Ratio
    nums[0..0]    [1]               0           1        0 / 1
    nums[0..1]    [1, 2]            1           1        1 / 1
    nums[0..2]    [1, 2, 1]         1           2        1 / 2
    nums[0..3]    [1, 2, 1, 2]      2           2        2 / 2
    nums[1..2]    [2, 1]            1           1        1 / 1
    nums[2..2]    [1]               0           1        0 / 1
    nums[2..3]    [1, 2]            1           1        1 / 1
    Thus, the number of valid subarrays is 7.


    --- Example 2 ---
    Input: nums = [2,2,1], a = 2, b = 1
    Output: 3
    Explanation:
    The following are the valid subarrays:
    Subarray     Values    Even Count    Odd Count    Ratio
    nums[0..2]    [2, 2, 1]    2            1         2 / 1
    nums[1..2]    [2, 1]       1            1         1 / 1
    nums[2..2]    [1]          0            1         0 / 1
    Thus, the number of valid subarrays is 3.


    --- Example 3 ---
    Input: nums = [2,2,2], a = 1, b = 1
    Output: 0
    Explanation:
    Every subarray contains 0 odd numbers, so no subarray is valid.


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 1000
    1 <= a, b <= 1000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. Brute-Force is allowed due to small Constraints.

*/

/* Time  Beats: 28.02% */
/* Space Beats: 80.72% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int countRatioSubarrays(vector<int>& nums, int a, int b)
    {
        const int N = nums.size();
        int result = 0;

        double ratio = 1.0 * a / b;

        for (int i = 0; i < N; i++)
        {
            int even = 0;
            int odd  = 0;
            for (int j = i; j < N; j++)
            {
                if (nums[j] & 1) // Odd
                    ++odd;
                else
                    ++even;

                if (odd > 0 && (1.0 * even / odd) <= ratio)
                    ++result;
            }
        }

        return result;
    }
};
