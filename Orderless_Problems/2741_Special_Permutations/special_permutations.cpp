/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2741) Special Permutations
    ===========================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums containing n distinct positive
    integers. A permutation of nums is called special if:

        For all indexes 0 <= i < n - 1, either nums[i] % nums[i+1] == 0 or
        nums[i+1] % nums[i] == 0.

    Return the total number of special permutations. As the answer could be
    large, return it modulo 10^9 + 7.

    =============================================
    FUNCTION: int specialPerm(vector<int>& nums);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,6]
    Output: 2
    Explanation: [3,6,2] and [2,6,3] are the two special permutations of nums.

    --- Example 2 ---
    Input: nums = [1,4,3]
    Output: 2
    Explanation: [3,1,4] and [4,1,3] are the two special permutations of nums.


    *** Constraints ***
    2 <= nums.length <= 14
    1 <= nums[i] <= 10^9

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

/* Time  Beats: 95.74% */
/* Space Beats: 88.83% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N * 2^N) */
class Solution {
private:
    int memo[1 << 14][14];
    const int MOD = 1e9 + 7;

public:
    int specialPerm(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0;

        memset(memo, -1, sizeof(memo));

        for (int i = 0; i < N; i++)
        {
            int all_unused = (1 << N) - 1;
            int one_used   = all_unused ^ (1 << (N-1 - i));

            result += solve(one_used, i, nums) % MOD;
            result %= MOD;
        }

        return static_cast<int>(result);
    }

private:
    int solve(int used_numbers, int idx_prev_used, vector<int>& nums)
    {
        const int N = nums.size();

        if (used_numbers == 0x00)
            return 1;

        if (memo[used_numbers][idx_prev_used] != -1)
            return memo[used_numbers][idx_prev_used];

        int max_permutations = 0;
        for (int i = 0; i < N; i++)
        {
            bool this_bit_is_set = used_numbers & (1 << (N-1 - i));

            if (this_bit_is_set)
            {
                if (nums[idx_prev_used] % nums[i] != 0 && nums[i] % nums[idx_prev_used] != 0)
                    continue;

                int use_this_bit = used_numbers ^ (1 << (N-1 - i));

                max_permutations += (solve(use_this_bit, i, nums) % MOD) % MOD;
                max_permutations %= MOD;
            }
        }

        return memo[used_numbers][idx_prev_used] = max_permutations;
    }
};
