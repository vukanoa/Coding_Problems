#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === EASY ===
    ============

    ===========================================================
    1608) Special Array With X Elements Greater Than or Equal X
    ===========================================================

    ============
    Description:
    ============

    You are given an array nums of non-negative integers. nums is considered
    special if there exists a number x such that there are exactly x numbers in
    nums that are greater than or equal to x.

    Notice that x does not have to be an element in nums.

    Return x if the array is special, otherwise, return -1. It can be proven
    that if nums is special, the value for x is unique.

    ==============================================
    FUNCTION: int specialArray(vector<int>& nums);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,5]
    Output: 2
    Explanation: There are 2 values (3 and 5) that are greater than or equal to
                 2.


    --- Example 2 ---
    Input: nums = [0,0]
    Output: -1
    Explanation: No numbers fit the criteria for x.
    If x = 0, there should be 0 numbers >= x, but there are 2.
    If x = 1, there should be 1 number >= x, but there are 0.
    If x = 2, there should be 2 numbers >= x, but there are 0.
    x cannot be greater since there are only 2 numbers in nums.


    --- Example 3 ---
    Input: nums = [0,4,3,0,4]
    Output: 3
    Explanation: There are 3 values that are greater than or equal to 3.


    *** Constraints ***
    1 <= nums.length <= 100
    0 <= nums[i] <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 40.78% */
/* Space Beats: 19.80% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1) */
class Solution_Binary_Search {
public:
    int specialArray(std::vector<int>& nums)
    {
        const int N = nums.size();

        // Sort the Input
        std::sort(nums.begin(), nums.end());

        for (int candidate_num = 1; candidate_num <= N; candidate_num++)
        {
            if (candidate_num == binary_search(nums, candidate_num))
                return candidate_num;
        }

        return -1;
    }

private:
    int binary_search(std::vector<int>& nums, int curr_num)
    {
        const int N = nums.size();

        int left  = 0;
        int right = N - 1;

        int first_index = N; // Out of Bounds at the beginning

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (curr_num <= nums[mid])
            {
                first_index = mid;
                right = mid - 1;
            }
            else
                left = mid + 1;
        }

        return N - first_index;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  9.22% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Suffix_Sum {
public:
    int specialArray(std::vector<int>& nums)
    {
        const int N = nums.size();

        std::vector<int> frequency(N+1, 0);

        for (const int& num : nums)
            frequency[std::min(N, num)]++;

        int num_greater_equal = 0;

        for (int candidate_num = N; candidate_num > 0; candidate_num--)
        {
            num_greater_equal += frequency[candidate_num];

            if (candidate_num == num_greater_equal)
                return candidate_num;
        }

        return -1;
    }
};
