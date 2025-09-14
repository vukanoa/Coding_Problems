/*
    ============
    === HARD ===
    ============

    ===================================
    3686) Number of Stable Subsequences
    ===================================

    ============
    Description:
    ============

    You are given an integer array nums.

    A subsequence is stable if it does not contain three consecutive elements
    with the same parity when the subsequence is read in order
    (i.e., consecutive inside the subsequence).

    Return the number of stable subsequences.

    Since the answer may be too large, return it modulo 10^9 + 7.

    =========================================================
    FUNCTION: int countStableSubsequences(vector<int>& nums);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,5]
    Output: 6
    Explanation:
    Stable subsequences are [1], [3], [5], [1, 3], [1, 5], and [3, 5].
    Subsequence [1, 3, 5] is not stable because it contains three consecutive
    odd numbers. Thus, the answer is 6.

    --- Example 2 ---
    Input: nums = [2,3,4,2]
    Output: 14
    Explanation:
    The only subsequence that is not stable is [2, 4, 2], which contains three
    consecutive even numbers. All other subsequences are stable. Thus, the
    answer is 14.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Standard Take-Skip Memoization. State is: [L_parity][R_parity][idx]

    Where L_parity and R_parity can either be: 0, 1 or 2
*/

/* Time  Beats: 16.67% */
/* Space Beats:  8.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    const int MOD = 1e9 + 7;
    long long memo[3][3][100001];

public:
    int countStableSubsequences(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        if (N == 1)
            return 1;

        if (N == 2)
            return 3;

        /* Memset, i.e. Allocate  */
        memset(memo, -1, sizeof(memo));

        return solve(0, 0, 0, nums);
    }

private:
    int solve(int L_parity, int R_parity, int idx, vector<int>& nums)
    {
        const int N = nums.size();

        if (idx == N)
        {
            if (L_parity != 0 || R_parity != 0) // If not both are 0
                return 1;

            return 0;
        }

        if (memo[L_parity][R_parity][idx] != -1)
            return memo[L_parity][R_parity][idx];

        long long skip = 0LL;
        long long take = 0LL; // If we're here this one is stable

        if ((L_parity != R_parity) ||
            (L_parity == R_parity && R_parity != (nums[idx] & 1 ? 1 : 2)))
        {
            take = solve(R_parity, nums[idx] & 1 ? 1 : 2, idx+1, nums);
        }

        skip = solve(L_parity, R_parity, idx+1, nums);

        return memo[L_parity][R_parity][idx] = (skip + take) % MOD;
    }
};
