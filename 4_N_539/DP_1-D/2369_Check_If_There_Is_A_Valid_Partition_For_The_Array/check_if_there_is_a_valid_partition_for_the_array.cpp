#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =======================================================
    2369) Check if There is a Valid Partition For The Array
    =======================================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums. You have to partition the
    array into one or more contiguous subarrays.

    We call a partition of the array valid if each of the obtained subarrays
    satisfies one of the following conditions:

        The subarray consists of exactly 2, equal elements. For example, the subarray [2,2] is good.
        The subarray consists of exactly 3, equal elements. For example, the subarray [4,4,4] is good.
        The subarray consists of exactly 3 consecutive increasing elements,
        that is, the difference between adjacent elements is 1. For example,
        the subarray [3,4,5] is good, but the subarray [1,3,5] is not.

    Return true if the array has at least one valid partition. Otherwise,
    return false.

    =================================================
    FUNCTION: bool validPartition(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,4,4,5,6]
    Output: true
    Explanation: The array can be partitioned into the subarrays [4,4] and
                 [4,5,6].  This partition is valid, so we return true.


    --- Example 2 ---
    Input: nums = [1,1,1,2]
    Output: false
    Explanation: There is no valid partition for this array.


    *** Constraints ***
    2 <= nums.length <= 10^5
    1 <= nums[i] <= 10^6

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is the Brute Force way of solving this problem.
    This code gives TLE(Time Limit Exceeded).

*/

/* Time  Complexity: O(2^n) */
/* Space Complexity: O(n) */
class Solution_Backtracking_Brute_Force {
public:
    bool validPartition(std::vector<int>& nums)
    {
        return backtracking(nums, {}, 0);
    }

private:
    bool backtracking(std::vector<int>& nums,
                      std::vector<int>  subarray,
                      int start)
    {
        if (start == nums.size())
            return true;

        for (int i = start; i < nums.size(); i++)
        {
            subarray.push_back(nums[i]);

            if (subarray.size() < 2)
                continue;

            if (subarray.size() == 2 && valid(subarray))
            {
                if (backtracking(nums, {}, i+1))
                    return true;

                continue;
            }
            else if (subarray.size() == 2 && !valid(subarray))
            {
                if (subarray[0] == subarray[1]-1)
                    continue;

                return false;
            }
            else
            {
                if (!valid(subarray))
                    return false;

                return backtracking(nums, {}, i+1);
            }
        }

        return false;
    }

    bool valid(std::vector<int>& subarray)
    {
        if (subarray.size() < 2 || subarray.size() > 3)
            return false;

        if (subarray.size() == 2)
            return subarray[0] == subarray[1];

        if (subarray[0] == subarray[1] && subarray[1] == subarray[2])
            return true;

        return subarray[0] == subarray[1]-1 && subarray[1] == subarray[2]-1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Transform the upper "Backtracking" Solution to DP Solution by caching the
    information.

*/

/* Time  Beats: 5.06% */
/* Space Beats: 5.06% */

/* Time  Complexity: O(2^n) */ // Same in the worst case, but faster on average
/* Space Complexity: O(n)   */
class Solution_Memoization {
public:
    bool validPartition(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<std::vector<bool>> dp(2, std::vector<bool>(n, false));

        return dfs(nums, {}, dp, 0);
    }

private:
    bool dfs(std::vector<int>& nums,
                      std::vector<int>  subarray,
                      std::vector<std::vector<bool>>& dp,
                      int start)
    {
        if (start == nums.size())
            return true;

        if (dp[0][start] || dp[1][start])
            return false;

        for (int i = start; i < nums.size(); i++)
        {
            subarray.push_back(nums[i]);

            if (subarray.size() < 2)
                continue;

            if (subarray.size() == 2 && valid(subarray))
            {
                if (dfs(nums, {}, dp, i+1))
                    return true;

                continue;
            }
            else if (subarray.size() == 2 && !valid(subarray))
            {
                if (subarray[0] == subarray[1]-1)
                    continue;

                dp[0][start] = true;

                return false;
            }
            else
            {
                if (!valid(subarray))
                {
                    dp[1][start] = true;
                    return false;
                }

                if (dfs(nums, {}, dp, i+1))
                    return true;

                dp[1][start] = true;
                return false;
            }
        }

        if (subarray.size() == 2)
            dp[0][start] = true;
        else if (subarray.size() == 3)
            dp[1][start] = true;

        return false;
    }

    bool valid(std::vector<int>& subarray)
    {
        if (subarray.size() < 2 || subarray.size() > 3)
            return false;

        if (subarray.size() == 2)
            return subarray[0] == subarray[1];

        if (subarray[0] == subarray[1] && subarray[1] == subarray[2])
            return true;

        return subarray[0] == subarray[1]-1 && subarray[1] == subarray[2]-1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is reminiscent of a "Word Break" problem from Blind75.

*/

/* Time  Beats: 75.19% */
/* Space Beats: 54.52% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_DP {
public:
    bool validPartition(std::vector<int>& nums)
    {
        int n = nums.size();

        std::vector<int> dp(n+1, false);
        dp[n]   = true;
        dp[n-2] = nums[n-2] == nums[n-1];

        for (int i = n-3; i >= 0; i--)
        {
            if ((valid_2(nums, i) && dp[i+2]) || (valid_3(nums, i) && dp[i+3]))
                dp[i] = true;
        }

        return dp[0];
    }

private:
    bool valid_2(std::vector<int>& nums, int i)
    {
        return nums[i] == nums[i+1];
    }

    bool valid_3(std::vector<int>& nums, int i)
    {
        if (nums[i] == nums[i+1] && nums[i+1] == nums[i+2])
            return true;

        return nums[i] == nums[i+1] - 1 && nums[i+1] == nums[i+2] - 1;
    }
};
