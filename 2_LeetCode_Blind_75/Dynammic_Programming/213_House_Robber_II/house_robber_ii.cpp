#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    213) House Robber II
    ===========================

    ============
    Description:
    ============

    You are a professional robber planning to rob houses along a street. Each
    house has a certain amount of money stashed. All houses at this place are
    arranged in a circle. That means the first house is the neighbor of the
    last one. Meanwhile, adjacent houses have a security system connected, and
    it will automatically contact the police if two adjacent houses were broken
    into on the same night.

    Given an integer array nums representing the amount of money of each house,
    return the maximum amount of money you can rob tonight without alerting the
    police.

    =====================================
    FUNCTION: int rob(vector<int>& nums);
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,2]
    Output: 3
    Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money
                 = 2), because they are adjacent houses.


    --- Example 2 ---
    Input: nums = [1,2,3,1]
    Output: 4
    Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
    Total amount you can rob = 1 + 3 = 4.


    --- Example 3 ---
    Input: nums = [1,2,3]
    Output: 3


    *** Constraints ***
    1 <= nums.length <= 100
    0 <= nums[i] <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    Since the very last house is the neighbor of the 0th house, we can't just
    do the same as in the first version of this problem.

    But it's not much different either.

    We have to do two "house robber"(first version) problems:
            1. From 0 to n-2
            2. From 1 to n-1
    
    And then just return max out of those two.

    We also didn't use a vector dp, but only two variables, to make this more
    efficient.
    So, since we haven't used it, it's maybe unclear.
    
    Ultimately we return max(dp[n - 2], dp[n - 1])

    That's it.

*/

/* Time  Beats:   100% */
/* Space Beats: 96.68% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int rob(std::vector<int>& nums)
    {
        int n = nums.size();

        return std::max(house_robber(nums, 0, n-1), house_robber(nums, 1, n));
    }

private:
    int house_robber(std::vector<int>& nums, int start, int end)
    {
        if (start == nums.size()) // Out of bounds(Expl: n=1, start=1, end=1)
            return 0;

        int prev = 0;
        int curr = nums[start];

        for (int i = start + 1; i < end; i++)
        {
            int tmp = std::max(curr, prev + nums[i]);

            prev = curr;
            curr = tmp;
        }

        return curr;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, implemented slightly differently.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  99.79% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int rob(vector<int>& nums)
    {
        if (nums.size() == 0)
            return 0;
        else if (nums.size() == 1)
            return nums[0];
        
        int rob_0 = house_robber(nums, 0, nums.size()-1);
        int rob_1 = house_robber(nums, 1, nums.size());

        return std::max(rob_0, rob_1);
    }

private:
    int house_robber(std::vector<int>& nums, int start, int end)
    {
        int prev = 0;
        int curr = nums[start];

        for (int i = start+1; i < end; i++)
        {
            int tmp = std::max(curr, prev + nums[i]);

            prev = curr;
            curr = tmp;
        }

        return curr;
    }
};
