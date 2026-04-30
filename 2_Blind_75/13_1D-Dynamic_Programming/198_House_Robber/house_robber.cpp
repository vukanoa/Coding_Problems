/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    198) House Robber
    ===========================

    ============
    Description:
    ============

    You are a professional robber planning to rob houses along a street. Each
    house has a certain amount of money stashed, the only constraint stopping
    you from robbing each of them is that adjacent houses have security systems
    connected and *it will automatically contact the police if two adjacent
    houses were broken into on the same night.*

    Given an integer array "nums" representing the amount of money of each
    house, return the maximum amount of money you can rob tonight without
    alerting the police.

    =====================================
    FUNCTION: int rob(vector<int>& nums);
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 2, 3, 1]
    Output: 4

    --- Example 2 ---
    Input:  nums = [2, 7, 9, 3, 1]
    Output: 12

    *** Constraints ***
    1 <= nums.length <= 100
    0 <= nums[i] <= 400

*/

#include <vector>
using namespace std;
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
    vector by pushing two additional elements, usually "dummy" elements or
    "default value" elements(0s in this case)

    On the other hand, you DO NOT have that flexibility when working
    left-to-right.

    Now we simply start from N-1 and we do not have to worry about anything.
    We know we won't go Out-of-Bounds with our indexing.

    This is the advantage of going backwards. If you CAN choose, ALWAYS choose
    to go backwards since you have more flebixility.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  11.31% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_From_The_Back {
public:
    int rob(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> dp(N+2, 0);

        for (int i = N-1; i >= 0; i--)
            dp[i] = max(nums[i] + dp[i+2], dp[i+1]);

        return dp[0];
    }
};
