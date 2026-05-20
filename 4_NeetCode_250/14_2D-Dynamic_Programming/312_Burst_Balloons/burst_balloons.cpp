/*
    ============
    === HARD ===
    ============

    ===========================
    312) Burst Balloons
    ===========================

    ============
    Description:
    ============

    You are given n balloons, indexed from 0 to n - 1. Each balloon is painted
    with a number on it represented by an array nums. You are asked to burst
    all the balloons.

    If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i +
    1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it
    as if there is a balloon with a 1 painted on it.

    Return the maximum coins you can collect by bursting the balloons wisely.

    ==========================================
    FUNCTION: int maxCoins(vector<int>& nums);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,1,5,8]
    Output: 167
    Explanation:
    nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
    coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167

    --- Example 2 ---
    Input: nums = [1,5]
    Output: 10

    *** Constraints ***
    n == nums.length
    1 <= n <= 300
    0 <= nums[i] <= 100

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 45.90% */
/* Space Beats: 90.80% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N^2) */
class Solution_Top_Down__Memoization {
private:
    int memo[302][302];

public:
    int maxCoins(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> new_nums(N + 2, 1);
        for (int i = 0; i < N; i++)
            new_nums[i + 1] = nums[i];

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(1, N, new_nums);
    }

private:
    int solve(int L, int R, vector<int>& new_nums)
    {
        if (L > R)
            return 0;

        if (memo[L][R] != -1)
            return memo[L][R];

        int result = 0;
        for (int i = L; i <= R; i++)
        {
            int coins = new_nums[L - 1] * new_nums[i] * new_nums[R + 1];

            coins += solve(L  , i-1, new_nums) +
                     solve(i+1, R  , new_nums);

            result = max(result, coins);
        }

        return memo[L][R] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 61.85% */
/* Space Beats: 55.77% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N^2) */
class Solution_Bottom_Up__Tabulation {
public:
    int maxCoins(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> new_nums(N + 2, 1);
        for (int i = 0; i < N; i++)
            new_nums[i + 1] = nums[i];

        vector<vector<int>> dp(N + 2, vector<int>(N + 2, 0));
        for (int L = N; L >= 1; L--)
        {
            for (int R = L; R <= N; R++)
            {
                for (int i = L; i <= R; i++)
                {
                    int coins = new_nums[L - 1] * new_nums[i] * new_nums[R + 1];

                    coins += dp[L    ][i - 1] +
                             dp[i + 1][R    ];

                    dp[L][R] = max(dp[L][R], coins);
                }
            }
        }

        return dp[1][N];
    }
};
