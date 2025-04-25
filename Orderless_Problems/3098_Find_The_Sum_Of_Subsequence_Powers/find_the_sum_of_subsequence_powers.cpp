/*
    ============
    === HARD ===
    ============

    =========================================
    3098) Find the Sum of Subsequences Powers
    =========================================

    ============
    Description:
    ============

    You are given an integer array nums of length n, and a positive integer k.

    The power of a subsequence is defined as the minimum absolute difference
    between any two elements in the subsequence.

    Return the sum of powers of all subsequences of nums which have length
    equal to k.

    Since the answer may be large, return it modulo 109 + 7.

    ====================================================
    FUNCTION: int sumOfPowers(vector<int>& nums, int k);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4], k = 3
    Output: 4
    Explanation: There are 4 subsequences in nums which have length 3:
                 [1,2,3], [1,3,4], [1,2,4], and [2,3,4]. The sum of powers is
                 |2 - 3| + |3 - 4| + |2 - 1| + |3 - 4| = 4.

    --- Example 2 ---
    Input: nums = [2,2], k = 2
    Output: 0
    Explanation: The only subsequence in nums which has length 2 is [2,2].
                 The sum of powers is |2 - 2| = 0.

    --- Example 3 ---
    Input: nums = [4,3,-1], k = 2
    Output: 10
    Explanation: There are 3 subsequences in nums which have length 2:
                 [4,3], [4,-1], and [3,-1].
                 The sum of powers is |4 - 3| + |4 - (-1)| + |3 - (-1)| = 10.


    *** Constraints ***
    2 <= n == nums.length <= 50
    -10^8 <= nums[i] <= 10^8
    2 <= k <= n

*/

#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is 0-1 Knapsack using Memoization.

    TODO

*/

/* Time  Beats: 51.18% */
/* Space Beats: 57.48% */

/* Time  Complexity: O(N^4) */
/* Space Complexity: O(N^4) */
class Solution {
public:
    const int MOD = 1e9 + 7;
    int memo[52][52][52][51];

    int sumOfPowers(vector<int>& nums, int k)
    {
        memset(memo, -1, sizeof(memo));

        /* Sort */
        sort(nums.begin(), nums.end());

        return solve(0, -1, -1, -1, k, nums);
    }

private:
    int solve(int pos, int last, int idx1, int idx2, int k, vector<int>& nums)
    {
        if (k == 0)
            return abs(nums[idx1] - nums[idx2]);

        if (pos >= nums.size())
            return 0;

        if (memo[last+1][idx1+1][idx2+1][k] != -1)
            return memo[last+1][idx1+1][idx2+1][k];

        int tmp1 = idx1;
        int tmp2 = idx2;

        if (last != -1 && (idx1 == -1 || idx2 == -1 || abs(nums[idx1] - nums[idx2]) > abs(nums[pos] - nums[last])) )
        {
            tmp1 = last;
            tmp2 = pos;
        }

        int take = solve(pos+1, pos,  tmp1, tmp2, k-1, nums) % MOD;
        int skip = solve(pos+1, last, idx1,  idx2,  k  , nums) % MOD;

        return memo[last+1][idx1+1][idx2+1][k] = (take + skip) % MOD;
    }
};
