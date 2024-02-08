#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    167) Two Sum II - Input Is Sorted
    =================================

    ============
    Description:
    ============

    Given a 1-indexed array of integers numbers that is already sorted in
    non-decreasing order, find two numbers such that they add up to a specific
    target number. Let these two numbers be numbers[index1] and numbers[index2]
    where 1 <= index1 < index2 < numbers.length.

    Return the indices of the two numbers, index1 and index2, added by one as
    an integer array [index1, index2] of length 2.

    The tests are generated such that there is exactly one solution. You may
    not use the same element twice.

    Your solution must use only constant extra space.

    ===============================================================
    FUNCTION: vector<int> twoSum(vector<int>& numbers, int target);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: numbers = [2,7,11,15], target = 9
    Output: [1,2]
    Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We
                 return [1, 2].


    --- Example 2 ---
    Input: numbers = [2,3,4], target = 6
    Output: [1,3]
    Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We
                 return [1, 3].


    --- Example 3 ---
    Input: numbers = [-1,0], target = -1
    Output: [1,2]
    Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].


    *** Constraints ***
    2 <= numbers.length <= 3 * 10^4
    -1000 <= numbers[i] <= 1000
    numbers is sorted in non-decreasing order.
    -1000 <= target <= 1000
    The tests are generated such that there is exactly one solution.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Since the Input is sorted everytime check:
        if (nums[left] + nums[right] == target)
            return {left+1, right+1};

    Otherwise, check if the sum is greater or lower than the current sum.

    If it's greater, then:
        right--; // Since that will decrease the sum since it's non-decreasing
                 // order of the Input "numbers"
    else
        left++; // This will increase the sum in next iteration since the Input
                // is sorted in non-decreasing order
*/

/* Time  Beats: 92.91% */
/* Space Beats: 29.01% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target)
    {
        int left  = 0;
        int right = numbers.size() - 1;

        while (left < right)
        {
            int sum = numbers[left] + numbers[right];

            if (sum == target)
                return {left+1, right+1}; // Because indexing starts with 1

            if (sum > target)
                right--;
            else
                left++;
        }

        return {0, 0}; // This will never happen
    }
};
