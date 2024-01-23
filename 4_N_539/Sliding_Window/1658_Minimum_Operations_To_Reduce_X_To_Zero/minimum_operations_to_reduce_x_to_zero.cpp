#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1658) Minimum Operations to Reduce X to Zero
    ============================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer x. In one operation, you
    can either remove the leftmost or the rightmost element from the array nums
    and subtract its value from x. Note that this modifies the array for future
    operations.

    Return the minimum number of operations to reduce x to exactly 0 if it is
    possible, otherwise, return -1.

    ======================================================
    FUNCTION: int minOperations(vector<int>& nums, int x);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,4,2,3], x = 5
    Output: 2
    Explanation: The optimal solution is to remove the last two elements to
                 reduce x to zero.


    --- Example 2 ---
    Input: nums = [5,6,7,8,9], x = 4
    Output: -1


    --- Example 3 ---
    Input: nums = [3,2,20,1,1,3], x = 10
    Output: 5
    Explanation: The optimal solution is to remove the last three elements and
                 the first two elements (5 operations in total) to reduce x to
                 zero.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^4
    1 <= x <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is one of those problems where they are deliberately trying to trick
    us with the Description.

    If you were to think about this problem in the way they are describing it,
    you'd quickly realize it's almost impossible to do it in an efficient way.

    What are they asking us to find?
        1. Minimum Operations(removals)
        2. Either remove the leftmost or the rightmost element from the array

    Instead, how you should think about this problem:
        1. MAXIMUM elements that are NOT the result
        2. Elements that are consecutive and:
           a) That are NOT on the edges
            OR
           b) That are at most connected to one edge

    So we want to get the biggest consecutive window of elements that are NOT
    the result, so that the remaining elements sum up to x.

    By MAXIMIZING our NON-RESULT elements, we are MINIMIZING the result
    elements.

    However, instead of finding different length windows that when subtracted
    from the total sum of the array and taking the biggest one, we can only
    search for a window that sums up to (total_sum - x) instead.

    Therefore, we'll use a Sliding Window technique.

*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************

    This is a good example to show how difficult it would be if we were to do
    it in a way they're describing.

    You can try to think of a Solution to solve it in a way they've described,
    but I'm going to simulate my Solution.


                    nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7

                    total_sum = 29
                    desired_middle_sum = total_sum - x ==> 29 - 7 => 22

                    curr_sum = 0

-------------------------------------------------------------------------------

    1.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L
                R

        curr_sum = 3

        if (curr_sum > desired_middle_sum) // It is NOT
            /

        if (curr_sum == desired_middle_sum) // It is NOT
            /

-------------------------------------------------------------------------------

    2.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L  R

        curr_sum = 5

        if (curr_sum > desired_middle_sum) // It is NOT
            /

        if (curr_sum == desired_middle_sum) // It is NOT
            /

-------------------------------------------------------------------------------

    3.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L     R

        curr_sum = 7

        if (curr_sum > desired_middle_sum) // It is NOT
            /

        if (curr_sum == desired_middle_sum) // It is NOT
            /

-------------------------------------------------------------------------------

    4.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L        R

        curr_sum = 16

        if (curr_sum > desired_middle_sum) // It is NOT
            /

        if (curr_sum == desired_middle_sum) // It is NOT
            /

-------------------------------------------------------------------------------

    5.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L           R

        curr_sum = 22

        if (curr_sum > desired_middle_sum) // It is NOT
            /

        if (curr_sum == desired_middle_sum) // IT is INDEED
            max_window = max(max_window, R - L + 1) ==> max(0, 5) ==> 5;

-------------------------------------------------------------------------------

    6.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L              R

        curr_sum = 23

        if (curr_sum > desired_middle_sum) // IT is INDEED
            curr_sum -= nums[L]
            L++


        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L              R

        curr_sum = 20

        if (curr_sum == desired_middle_sum) // It is NOT
            /

-------------------------------------------------------------------------------

    7.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                   L              R

        curr_sum = 21

        if (curr_sum > desired_middle_sum) // It is NOT
            /

        if (curr_sum == desired_middle_sum) // It is NOT
            /

-------------------------------------------------------------------------------

    8.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                   L                 R

        curr_sum = 23

        if (curr_sum > desired_middle_sum) // It is NOT
            curr_sum -= nums[L]
            L++


        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                      L              R

        curr_sum = 21

        if (curr_sum == desired_middle_sum) // It is NOT
            /

-------------------------------------------------------------------------------

    9.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                      L                 R

        curr_sum = 24

        if (curr_sum > desired_middle_sum) // IT is INDEED
            curr_sum -= nums[L]
            L++

        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                      L                 R


        curr_sum = 22

        if (curr_sum == desired_middle_sum) // IT is INDEED
            max_window = max(max_window, R - L + 1) ==> max(5, 7) ==> 7;


    return max_window; // 7
-------------------------------------------------------------------------------

*/

/* Time  Beats: 99.23% */
/* Space Beats: 34.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minOperations(std::vector<int>& nums, int x)
    {
        int total_sum = 0;
        for (int& num : nums)
            total_sum += num;

        int desired_middle_sum = total_sum - x;
        int curr_sum = 0;

        int left  = 0;
        int right = 0;

        int max_window = -1; // Middle window, that's why it's "maximum"
        while (right < nums.size())
        {
            curr_sum += nums[right];

            while (left <= right && curr_sum > desired_middle_sum)
                curr_sum -= nums[left++];

            if (curr_sum == desired_middle_sum)
                max_window = std::max(max_window, right - left + 1);

            right++;
        }

        return max_window == -1 ? -1 : nums.size() - max_window;
    }
};
