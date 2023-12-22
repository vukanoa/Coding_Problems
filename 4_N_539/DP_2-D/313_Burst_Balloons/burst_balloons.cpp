#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ===========================
    303) Burst Balloons
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

/*
    ------------
    --- IDEA ---
    ------------

    TODO (Tricky one)

*/

/* Time  Beats: 5.03% */
/* Space Beats: 53.44% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    int maxCoins(std::vector<int>& nums)
    {
        const int N = nums.size();

        std::vector<int> vec;

        vec.push_back(1);
        vec.insert(vec.end(), nums.begin(), nums.end());
        vec.push_back(1);

        std::vector<std::vector<int>> dp(N+1, std::vector<int>(N+1, -1));

        return dfs(1, vec.size() - 2, vec, dp);
    }

private:
    int dfs(
            int left,
            int right,
            std::vector<int>& vec,
            std::vector<std::vector<int>>& dp
           )
    {
        if (left > right)
            return 0;

        if (dp[left][right] != -1)
            return dp[left][right];

        dp[left][right] = 0;
        for (int i = left; i < right+1; i++)
        {
            int coins = vec[left - 1] * vec[i] * vec[right + 1];
            coins += dfs(left, i-1, vec, dp) + dfs(i+1, right, vec, dp);

            dp[left][right] = std::max(dp[left][right], coins);
        }

        return dp[left][right];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 54.95% */
/* Space Beats: 53.44% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    int maxCoins(std::vector<int>& nums)
    {
        int n = nums.size() + 2;

        std::vector<std::vector<int>> dp(n, std::vector<int>(n));
        std::vector<int> new_nums(n, 1);

        int i = 1;
        for(auto& num : nums)
            new_nums[i++] = num;

        for(int len = 2; len <= n; len++)
        {
            for(int i = 0; i <= n - len; i++)
            {
                int j = i + len - 1;
                for(int k = i + 1; k < j; k++)
                {
                    int coins = new_nums[i] * new_nums[k] * new_nums[j];
                    coins += dp[i][k] + dp[k][j];

                    dp[i][j] = std::max(dp[i][j], coins);
                }
            }
        }

        return dp[0][n - 1];
    }
};
