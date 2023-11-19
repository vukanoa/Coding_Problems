#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ==============================
    977) Squares of a Sorted Array
    ==============================

    ============
    Description:
    ============

    Given an integer array nums sorted in non-decreasing order, return an array
    of the squares of each number sorted in non-decreasing order.


    Follow up: Squaring each element and sorting the new array is very trivial,
               could you find an O(n) solution using a different approach?


    =======================================================
    FUNCTION: vector<int> sortedSquares(vector<int>& nums);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [-4,-1,0,3,10]
    Output: [0,1,9,16,100]
    Explanation: After squaring, the array becomes [16,1,0,9,100].
    After sorting, it becomes [0,1,9,16,100].


    --- Example 2 ---
    Input: nums = [-7,-3,2,3,11]
    Output: [4,9,9,49,121]



    *** Constraints ***
    1 <= nums.length <= 10^4
    -104 <= nums[i] <= 10^4
    nums is sorted in non-decreasing order.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is the Naive approach, kind of. It's efficient, but we DON'T have to
    start "filling" our result vector from the smaller values. That's where
    the naiveness lies.

    The first one below demonstrates what it has to be done if we want to push
    smaller elements first.

    And the other Solution down below, the bottom one, shows how clean and easy
    it is if we start from the back and start "filling" with largest values
    first.

*/

/* Time  Beats: 97.65% */
/* Space Beats: 15.61% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // We shan't count "result" as additional memory
class Solution_1 {
public:
    std::vector<int> sortedSquares(std::vector<int>& nums)
    {
        int n = nums.size();

        int idx = 0;
        for (int i = 1; i < n; i++)
            idx = nums[i] < std::abs(nums[idx]) ? i : idx;

        std::vector<int> result;

        result.push_back(nums[idx] * nums[idx]);
        int left  = idx-1;
        int right = idx+1;

        while (left >= 0 && right < n)
        {
            if (std::abs(nums[left]) < std::abs(nums[right]))
                result.push_back(nums[left] * nums[left--]);
            else
                result.push_back(nums[right] * nums[right++]);
        }

        while (left >= 0)
            result.push_back(nums[left] * nums[left--]);

        while (right < n)
            result.push_back(nums[right] * nums[right++]);

        return result;
    }
};




/* Time  Beats: 99.64% */
/* Space Beats: 38.25% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    std::vector<int> sortedSquares(std::vector<int>& nums)
    {
        int n = nums.size();

        std::vector<int> result(n);

        int left  = 0;
        int right = n-1;

        int idx = n-1;
        while (left <= right)
        {
            if (std::abs(nums[left]) > std::abs(nums[right]))
                result[idx--] = nums[left] * nums[left++];
            else
                result[idx--] = nums[right] * nums[right--];
        }

        return result;
    }
};
