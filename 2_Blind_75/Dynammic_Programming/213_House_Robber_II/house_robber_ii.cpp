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




/*
    ------------
    --- IDEA ---
    ------------

    This is an important "trick" and something you absolutely SHOULD be aware
    of.

    If there is no specific need to go from left-to-right, ALWAYS choose to go
    backwards, i.e. right-to-left.

    Why?
    (This is VERY important)

    When you go from the back, you have some flexibillity that you do NOT have
    when going from the front.

    Specifically, when creating a vector it's VERY EASY to simply extend the
    vector by pushing to additional elements, usually "dummy" elements or
    "default value" elements.

    On the other hand, you DO NOT have that flexibility when working
    left-to-right.

    As you can see, in the previous two Solution up above, we need to have
    "prev" variable set to 0 at the beginning, but we had to set "curr" to
    nums[start]. We also, then, had to begin our for-loop from start+1's index.

    That's waaay too much additional work that we DO NOT have to do if we go
    from the back.

    We are going from the back and we are checking non-adjacent houses to the
    right at each iteration. Specifically only the house that is two places to
    the right.

    To do this, we simply push two additional default-values to our "dp"
    vector, or when we use two-pointer to optimize Space Complexity we set both
    of our "first_nei" and "second_nei" to 0.

    And that's it. Now we start from the last element which is at end-1(this is
    fundamental stuff. If there is an array of size X, then X-1 is the last
    index).

    So, we simply start from end-1 and we do not have to worry about anything.

    This is the advantage of going backwards. If you CAN choose, ALWAYS choose
    to go backwards since you have more flebixility.


    Also:
    1. "first_nei"  can be named "closer_nei"
    2. "second_nei" can be named "farther_nei"

*/

/* Time  Beats: 100.00% */
/* Space Beats:  72.78% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_3_From_The_Back_Trick {
public:
    int rob(vector<int>& nums)
    {
        const int n = nums.size();

        if (n == 1)
            return nums[0];

        return max(house_robber(nums, 0, n-1), house_robber(nums, 1, n));
    }

private:
    int house_robber(vector<int>& nums, int begin, int end)
    {
        int first_nei  = 0; // Closer  neighbor to the right
        int second_nei = 0; // Farther neighbor to the right

        for (int i = end-1; i >= begin; i--)
        {
            int curr = max(nums[i] + second_nei, first_nei);

            second_nei = first_nei;
            first_nei  = curr;
        }

        return first_nei;
    }
};
