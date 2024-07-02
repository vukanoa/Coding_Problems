#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    =================================
    1250) Check If It Is a Good Array
    =================================

    ============
    Description:
    ============

    Given an array nums of positive integers. Your task is to select some
    subset of nums, multiply each element by an integer and add all these
    numbers. The array is said to be good if you can obtain a sum of 1 from the
    array by any possible subset and multiplicand.

    Return True if the array is good otherwise return False.

    ==============================================
    FUNCTION: bool isGoodArray(vector<int>& nums);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [12,5,7,23]
    Output: true
    Explanation: Pick numbers 5 and 7.
    5*3 + 7*(-2) = 1


    --- Example 2 ---
    Input: nums = [29,6,10]
    Output: true
    Explanation: Pick numbers 29, 6 and 10.
    29*1 + 6*(-3) + 10*(-1) = 1


    --- Example 3 ---
    Input: nums = [3,6]
    Output: false


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    This problem is realated a Chinese theorem: Chinese remainder theorem,
    created in 5th centry.  Also well known as Hanson Counting.

    Explanation:

    If a % x = 0 and b % x = 0,
    appareantly we have (pa + qb) % x == 0
    If x > 1, making it impossible pa + qb = 1.

    Well, I never heard of Bezout's identity. Even though the intuition only
    proves the necessary condition, it's totally enough.

    The process of gcd, is exactly the process to get the factor. The problem
    just doesn't ask this part.

*/

/* Time  Beats: 17.86% */
/* Space Beats: 48.21% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isGoodArray(std::vector<int>& nums)
    {
        int result = nums[0];

        for (const int& num : nums)
            result = std::gcd(result, num);

        return result == 1;
    }
};
