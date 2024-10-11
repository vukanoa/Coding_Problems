#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === HARD ===
    ============

    =======================================
    1799) Maximize Score After N Operations
    =======================================

    ============
    Description:
    ============

    You are given nums, an array of positive integers of size 2 * n. You must
    perform n operations on this array.

    In the ith operation (1-indexed), you will:

        Choose two elements, x and y.
        Receive a score of i * gcd(x, y).
        Remove x and y from nums.

    Return the maximum score you can receive after performing n operations.

    The function gcd(x, y) is the greatest common divisor of x and y.

    ==========================================
    FUNCTION: int maxScore(vector<int>& nums);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2]
    Output: 1
    Explanation: The optimal choice of operations is:
    (1 * gcd(1, 2)) = 1

    --- Example 2 ---
    Input: nums = [3,4,6,8]
    Output: 11
    Explanation: The optimal choice of operations is:
    (1 * gcd(3, 6)) + (2 * gcd(4, 8)) = 3 + 8 = 11

    --- Example 3 ---
    Input: nums = [1,2,3,4,5,6]
    Output: 14
    Explanation: The optimal choice of operations is:
    (1 * gcd(1, 5)) + (2 * gcd(2, 4)) + (3 * gcd(3, 6)) = 1 + 4 + 9 = 14


    *** Constraints ***
    1 <= n <= 7
    nums.length == 2 * n
    1 <= nums[i] <= 10^6

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 35.91% */
/* Space Beats: 46.32% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int maxScore(vector<int>& nums)
    {
        unordered_map<int, int> cache;
        return dfs(nums, 1, 0, cache);
    }

private:
    int dfs(const vector<int>& nums, int round, int state, unordered_map<int, int>& cache)
    {
        if (round > nums.size() / 2)
            return 0;

        if (cache.count(state) > 0)
            return cache[state];

        int result = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                int picked = (1 << i) | (1 << j);

                if ((state & picked) == 0)
                    result = max(result, round * __gcd(nums[i], nums[j]) + dfs(nums, round + 1, state | picked, cache));
            }
        }

        return cache[state] = result;
    }
};
