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

    TODO

*/

/* Time  Beats: 72.20% */
/* Space Beats: 52.72% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Follow_Up_1 {
public:
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            while (nums[nums[i] - 1] != nums[i])
                std::swap(nums[nums[i] - 1], nums[i]);
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
