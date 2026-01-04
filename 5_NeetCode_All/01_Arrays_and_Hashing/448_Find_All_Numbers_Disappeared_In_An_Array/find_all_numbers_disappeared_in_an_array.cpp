#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    =============================================
    448) Find All Numbers Disappeared In An Array
    =============================================

    ============
    Description:
    ============

    Given an array nums of n integers where nums[i] is in the range [1, n],
    return an array of all the integers in the range [1, n] that do not appear
    in nums.

    Follow up: Could you do it without extra space and in O(n) runtime? You may
    assume the returned list does not count as extra space.

    ================================================================
    FUNCTION: vector<int> findDisappearedNumbers(vector<int>& nums);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,3,2,7,8,2,3,1]
    Output: [5,6]


    --- Example 2 ---
    Input: nums = [1,1]
    Output: [2]


    *** Constraints ***
    n == nums.length
    1 <= n <= 10^5
    1 <= nums[i] <= n

*/

/*
    ------------
    --- IDEA ---
    ------------

    We're told a very valuable and important piece of information:
    "Given an array nums of n integers where nums[i] is in the range [1, n]..."


    What that means is that, no matter how many duplicate numbers we have,
    every single(only one of the duplicates)distinct number can be at the right
    position if we reorder it.

    So, how can we order them?
    We can order them in various ways.

    The very first thing that comes to mind is: Sorting. However, that would
    take an O(n * logn) Time Complexity, which isn't very efficient for this
    problem.

    However, let's for a second forget how to reorder them in such a way. Let's
    just think about what would we get if we were able to be in that position.

    Example:
                0  1  2  3  4  5  6  7
        nums = [4, 3, 2, 7, 8, 2, 3, 1]


    If we, somehow, reorder this vector in a way that every distinct element
    gets to be in its right spot, we'd have this:

                0  1  2  3  4  5  6  7
        nums = [1, 2, 3, 4, 3, 2, 7, 8]


    Would this help us solve our problem?
    Definitely!

    We'd only have to iterate over this vector and check if element at i-th
    position is the same as "i+1", i.e. if (nums[i] != i+1)

    If it is not, that means the element "i+1" is NOT present in our vector
    "nums" and thus we shall include it in our "result" vector.

    nums = [7, 3, 2, 4, 8, 2, 3, 1]
    nums = [3, 3, 2, 4, 8, 2, 7, 1]
    nums = [2, 3, 3, 4, 8, 2, 7, 1]
    nums = [3, 2, 3, 4, 8, 2, 7, 1]
    nums = [3, 2, 3, 4, 1, 2, 7, 8]
    nums = [1, 2, 3, 4, 3, 2, 7, 8]

*/

/* Time  Beats: 97.65% */
/* Space Beats: 61.22% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Follow_Up_1 {
public:
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            while (nums[i] != nums[nums[i] - 1])
                std::swap(nums[i], nums[nums[i] - 1]);
        }

        std::vector<int> results;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != i+1)
                results.push_back(i+1);
        }

        return results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.00% */
/* Space Beats: 55.00% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Follow_Up_2 {
public:
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums)
    {
        int i = 0;
        while (i < nums.size())
        {
            if (nums[i] != nums[nums[i]-1] && i != nums[i]-1)
                swap(nums[i], nums[nums[i]-1]);
            else
                i++;
        }

        std::vector<int> results;
        for (int i = 0; i < nums.size(); i++)
        {
            if (i+1 != nums[i])
                results.push_back(i+1);
        }

        return results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.22% */
/* Space Beats: 90.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Follow_Up_Neat {
public:
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums)
    {
        for (int& num : nums)
        {
            int idx = std::abs(num) - 1;
            nums[idx] = -1 * std::abs(nums[idx]);
        }

        std::vector<int> results;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > 0)
                results.push_back(i + 1);
        }

        return results;
    }
};
