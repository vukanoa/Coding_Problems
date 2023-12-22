#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    918) Maximum Sum Circular Subarray
    ==================================

    ============
    Description:
    ============

    Given a circular integer array nums of length n, return the maximum
    possible sum of a non-empty subarray of nums.

    A circular array means the end of the array connects to the beginning of
    the array. Formally, the next element of nums[i] is nums[(i + 1) % n] and
    the previous element of nums[i] is nums[(i - 1 + n) % n].

    A subarray may only include each element of the fixed buffer nums at most
    once. Formally, for a subarray nums[i], nums[i + 1], ..., nums[j], there
    does not exist i <= k1, k2 <= j with k1 % n == k2 % n.

    ========================================================
    FUNCTION: int maxSubarraySumCircular(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,-2,3,-2]
    Output: 3
    Explanation: Subarray [3] has maximum sum 3.

    --- Example 2 ---
    Input: nums = [5,-3,5]
    Output: 10
    Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10.

    --- Example 3 ---
    Input: nums = [-3,-2,-3]
    Output: -2
    Explanation: Subarray [-2] has maximum sum -2.


    *** Constraints ***
    n == nums.length
    1 <= n <= 3 * 10^4
    -3 * 10^4 <= nums[i] <= 3 * 10^4

*/

/*

[5, -3, 4, -6, -4, 8, 3, -1] 5, -3, 4, -6, -4, 8, 3, -1


[-5, -2, 5, 6, -2, -7, 0, 2, 8] [-5, -2, 5, 6, -2, -7, 0, 2]

[5, -3, 5]

*/

/*
    ------------
    --- IDEA ---
    ------------

    Kadane's algorithm + tricks for handling circular array.

    If the maximum subarray is in the middle or only connected to one of the
    edges of our array "nums", then that means we'd be able to retrieve the
    result of this problem by using a standard Kadane's Algorithm.

    However, the problem arises once we can use the property and the crux of
    this problem's description - We have a circular integer array.

    What does that mean?
    That means that if we had, for example, this array:
        Input: nums = [5,-3,5]

    Maximum subarray is not 7, but 10.
    How?

    Since the last element is connected to the first element, ergo a circular
    array, then instead of taking -3 into account, we can only take elements on
    the edges of the array and, thus, have a maximum subarray of 10.

    We are taking these:
                   -------     -------
                         |     |
        Input: nums = [5 | -3  | 5]
                         |     |
                   -------     -------

    So how should we do that with Kadane's algorithm?
    It's not super obvious, but not too difficult to figure out.

    We should do an inverse operation. Instead of searching for a maximum
    subarray, we're going to search for a minimum subarray.

    Why?

    Because by finding the minimum contiguous subarray(or just subarray, since
    that is what subarray means, but wanted to be explicit) we can find the
    value of the subarray that uses the crucial property of this problem -
    Circularity.

    By having a total sum of the entire array "nums" and by subtracting the
    minimum subarray, we're going to obtain the maximum value for a subarray
    where two ends of the array are connected, with one or more central
    elements excluded from the sum.

    In other words: total_sum - global_min;

    global_min is the value of the subarray with the lowest sum.

    Then at the end, we should return either:
        1. global_max (which is the result of the standard Kadane's algorithm)

            or

        2. total_sum - global_min


    =================
    === EDGE CASE ===
    =================
    However, there is one edge case.

    Consider this example:
        nums = [-8, -3, -8]

    At the end global_max would be -3 and global_min would be -19.

    However if we were to check what's greater out of these two:
        1. global_max, or
        2. total_sum - global_min

    We'd stumble upon a, not so obvious, edge case:
        global_max = -3
        total_sum - global_min = -19 - (-19) = -19 + 19 = 0

    So what's bigger? -3 or 0?
    Obviously 0, however that's not possible to get with this example since
    are obliged to take at least one element. We aren't allowed to consider an
    empty subarray, therefore we'd mistakenly return 0 instead of 3.

    So how should we circumvent this issue?

    Simply at the end of the "for loop", check if global_max is negative. If
    that happens to be the case, that means, certainly, that all the elements
    in our array "nums" are negative and that further means that global_max is
    the correct result.

    We're doing that at the very end of our function:

        // global_max will be negative if and only if all elements are negative
        return global_max < 0 ? global_max : std::max(global_max,
                                                      total_sum - global_min);
*/

/* Time  Beats: 75.95% */
/* Space Beats: 41.65% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxSubarraySumCircular(std::vector<int>& nums)
    {
        int total_sum = 0;

        int global_max = nums[0];
        int global_min = nums[0];

        int curr_max = 0;
        int curr_min = 0;

        for (int& n : nums)
        {
            total_sum += n;

            curr_max   = std::max(curr_max + n, n);
            curr_min   = std::min(curr_min + n, n);

            global_max = std::max(global_max, curr_max);
            global_min = std::min(global_min, curr_min);
        }

        // global_max will be negative if and only if all elements are negative
        return global_max < 0 ? global_max : std::max(global_max, total_sum - global_min);
    }
};
