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

    There are two wasy to do this problem. One way is to iterate from the left,
    as you would by default. However this poses a small problem. You need to
    be cognizant and very careful not to make a mistake.

    Try going through the code with a few examples and you'll understand the
    reason behind these initial values to "prev" and "curr".

    But it is not trivial and easy to come up with. So keep that in mind.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  80.57% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Standard {
public:
    int rob(std::vector<int>& nums)
    {
        int n = nums.size();

        int prev = 0;
        int curr = nums[0]; // This way we don't have to cover the edge case

        for (int i = 1; i < n; i++) // Starts from 1
        {
            int tmp = std::max(curr, nums[i] + prev);

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
    "default value" elements(0s in this case)

    On the other hand, you DO NOT have that flexibility when working
    left-to-right.

    As you can see, in the previous Solution up above, we need to have "prev"
    variable set to 0 at the beginning, but we had to set "curr" to nums[start]

    We also, then, had to begin our for-loop from start+1's index.

    That's WAAAY too much additional work that we DO NOT have to do if we go
    from the back.

    We are going from the back and we are checking non-adjacent houses to the
    right at each iteration. Specifically only the house that is two places to
    the right.

    To do this, we simply push two additional default-values to our "dp" vector
    or when we use two-pointer to optimize Space Complexity we set both of our
    "closer" and "farther" to 0.(We'll do this in Solution below, don't worry
    about it right now)

    And that's it. Now we start from the last element which is at end-1(this is
    fundamental stuff. If there is an array of size X, then X-1 is the last
    index).

    So, we simply start from N-1 and we do not have to worry about anything.

    This is the advantage of going backwards. If you CAN choose, ALWAYS choose
    to go backwards since you have more flebixility.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  11.31% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_From_The_Back {
public:
    int rob(std::vector<int>& nums)
    {
        const int n = nums.size();
        vector<int> dp(nums.size() + 2, 0);

        for (int i = n-1; i >= 0; i--)
            dp[i] = max(nums[i] + dp[i+2], dp[i+1]);

        return dp[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Here we are just using "closer" and "farther" instead of an entire "dp"
    vector, thus optimizing Space Complexity.

    This way we've reduced it from O(n) to O(1) Space.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  43.04% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Improved_From_The_Back {
public:
    int rob(std::vector<int>& nums)
    {
        const int n = nums.size();
        int farther = 0; // Farther to the right, i.e. 2nd to the right
        int closer  = 0; // Closer  to the right, i.e. 1st to the right

        for (int i = n-1; i >= 0; i--)
        {
            int tmp = max(nums[i] + farther, closer);

            farther = closer;
            closer  = tmp;
        }

        return closer;
    }
};
