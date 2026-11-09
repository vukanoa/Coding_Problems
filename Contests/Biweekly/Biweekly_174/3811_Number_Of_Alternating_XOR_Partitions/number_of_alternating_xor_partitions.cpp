/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    3811) Number of Alternating XOR Partitions
    ==========================================

    ============
    Description:
    ============

    You are given an integer array nums and two distinct integers target1 and
    target2.

    A partition of nums splits it into one or more contiguous, non-empty blocks
    that cover the entire array without overlap.

    A partition is valid if the bitwise XOR of elements in its blocks
    alternates between target1 and target2, starting with target1.

    Formally, for blocks b1, b2, …:

        XOR(b1) = target1
        XOR(b2) = target2 (if it exists)
        XOR(b3) = target1, and so on.

    Return the number of valid partitions of nums, modulo 109 + 7.

    =====
    Note: A single block is valid if its XOR equals target1. 
    =====

    ==========================================================================
    FUNCTION: int alternatingXOR(vector<int>& nums, int target1, int target2);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,1,4], target1 = 1, target2 = 5
    Output: 1
    Explanation:
        The XOR of [2, 3] is 1, which matches target1.
        The XOR of the remaining block [1, 4] is 5, which matches target2.
        This is the only valid alternating partition, so the answer is 1.

    --- Example 2 ---
    Input: nums = [1,0,0], target1 = 1, target2 = 0
    Output: 3
    Explanation:
        The XOR of [1, 0, 0] is 1, which matches target1.
        The XOR of [1] and [0, 0] are 1 and 0, matching target1 and target2.
        The XOR of [1, 0] and [0] are 1 and 0, matching target1 and target2.
        Thus, the answer is 3.

    --- Example 3 ---
    Input: nums = [7], target1 = 1, target2 = 7
    Output: 0
    Explanation:
        The XOR of [7] is 7, which does not match target1, so no valid
        partition exists.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i], target1, target2 <= 10^5
    target1 != target2

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.44% */
/* Space Beats: 6.12% */

/* Time  Complexity: O(N * X * 2 * 2) */ // where 'X' is max(nums)
/* Space Complexity: O(N * X * 2 * 2) */
class Solution_Should_Give_TLE_But_Actually_Passes {
private:
    const int MOD = 1e9 + 7;
    unordered_map<long long, int> memo;

public:
    int alternatingXOR(vector<int>& nums, int target1, int target2)
    {
        /* Clear Memo */
        memo.clear();

        /* Solve */
        return solve(0, 0, false, true, nums, target1, target2);
    }

private:
    // is_curr_t2 == 1 --> t2
    // is_curr_t2 == 0 --> t1
    long long solve(int idx, int xor_val, int is_curr_t2, int just_started, vector<int>& nums, int target1, int target2)
    {
        const int N = nums.size();

        if (idx == N)
        {
            if (just_started)
                return 0;

            return (xor_val == (is_curr_t2 ? target2 : target1)) ? 1 : 0;
        }

        /* Encode State */
        long long state = (1LL * idx          << 32) | // bits [32..63]
                          (1LL * xor_val      <<  2) | // bits [ 2..18]  // (since 2^17 > 10^5  and  2^16 < 10^5)
                          (1LL * is_curr_t2   <<  1) | // bit  1
                          (1LL * just_started <<  0);  // bit  0

        if (memo.count(state))
            return memo[state];

        int new_xor_val = xor_val ^ nums[idx];

        long long keep_curr_block = 0LL;
        long long end_curr_block  = 0LL;

        // Keep going
        keep_curr_block = solve(idx+1, new_xor_val, is_curr_t2, 0, nums, target1, target2);

        // End current block here (if possible)
        if (new_xor_val == (is_curr_t2 ? target2 : target1))
            end_curr_block = solve(idx+1, 0, !is_curr_t2, 1, nums, target1, target2);

        return memo[state] = (keep_curr_block + end_curr_block) % MOD;
    }
};
