#include <iostream>
#include <vector>
#include <stack>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    456) 123 Pattern
    ===========================

    ============
    Description:
    ============

    Given an array of n integers nums, a 132 pattern is a subsequence of three
    integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] <
    nums[k] < nums[j].

    Return true if there is a 132 pattern in nums, otherwise, return false.

    =================================================
    FUNCTION: bool find132pattern(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4]
    Output: false
    Explanation: There is no 132 pattern in the sequence.

    --- Example 2 ---
    Input: nums = [3,1,4,2]
    Output: true
    Explanation: There is a 132 pattern in the sequence: [1, 4, 2].

    --- Example 3 ---
    Input: nums = [-1,3,2,0]
    Output: true
    Explanation: There are three 132 patterns in the sequence: [-1, 3, 2],
                 [-1, 3, 0] and [-1, 2, 0].


    *** Constraints ***
    n == nums.length
    1 <= n <= 2 * 10^5
    -10^9 <= nums[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    Good Example:
        [5, 8, 1, 4, 5, 3, 7, 6, 3, 4, 9]

*/

/* Time  Beats: 11.09% */
/* Space Beats: 10.34% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_1 {
public:
    bool find132pattern(std::vector<int>& nums)
    {
        std::stack<std::pair<int, int>> stack; // {min_to_the_left, num}
        int curr_min = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            while (!stack.empty() && stack.top().second <= nums[i])
                stack.pop();

            if (!stack.empty() && stack.top().first < nums[i] && stack.top().second > nums[i])
                return true;

            stack.push({curr_min, nums[i]});
            curr_min = std::min(curr_min, nums[i]);
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Virtually the same IDEA, though implemented in another way. We are going
    backwards therefore we don't have to have a pair inside our stack.

*/
/* Time  Beats: 11.73% */
/* Space Beats:  5.67% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    bool find132pattern(std::vector<int>& nums)
    {
        std::stack<int> stack;
        int third = INT_MIN;

        for (int i = nums.size()-1; i >= 0; i--)
        {
            if (nums[i] < third)
                return true;

            while (!stack.empty() && stack.top() < nums[i])
            {
                third = stack.top();
                stack.pop();
            }

            stack.push(nums[i]);
        }

        return false;
    }
};
