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

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Top-Down Dynamic-Programming, It's called "Memoization".
    (and NOT memoRization!)

    It's a fundamental "Take-Skip Memoization" technique.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  72.27% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Memoization {
private:
    int memo[101];

public:
    int rob(vector<int>& nums)
    {
        const int N = nums.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(0, nums);
    }

    int solve(int i, vector<int>& nums)
    {
        const int N = nums.size();

        if (i >= N)
            return 0;

        if (memo[i] != -1)
            return memo[i];

        int take = nums[i] + solve(i+2, nums);
        int skip = 0       + solve(i+1, nums);

        return memo[i] = max(take, skip);
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
/* Space Beats:  59.47% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Tabulation {
public:
    int rob(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> dp(N+2, 0);

        for (int i = N-1; i >= 0; i--)
            dp[i] = max(dp[i+1], nums[i] + dp[i+2]);

        return dp[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea as above, however we can notice that we ONLY ever need at most
    next 2 states from "dp".

    So why keep an entire vector "dp" we can keep track of ONLY 2 VARIABLES?

    This reduces the Space Complexity from O(N) down to O(1).

*/

/* Time  Beats: 100.00% */
/* Space Beats:  75.27% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up_Optimized_From_the_Back {
public:
    int rob(vector<int>& nums)
    {
        const int N = nums.size();

        int next_next = 0;
        int next      = nums[N-1];

        for (int i = N-2; i >= 0; i--)
        {
            int curr = max(next, nums[i] + next_next);

            next_next = next;
            next      = curr;
        }

        return next;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, we just go left-to-right.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  75.27% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up_Optimized_From_the_Front {
public:
    int rob(vector<int>& nums)
    {
        const int N = nums.size();

        int prev_prev = 0;
        int prev      = nums[0];

        for (int i = 1; i < N; i++)
        {
            int curr = max(nums[i] + prev_prev, prev);

            prev_prev = prev;
            prev      = curr;
        }

        return prev;
    }
};
