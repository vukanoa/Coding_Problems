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
class Solution_Memoizaiton {
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




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Tabulation, i.e. "Bottom-Up" Solutions are a little less intuitive to me
    than "Memoization" ones, but it's not too bad.

    You need to have base cases done before you start "solving" and you also
    need to have the index as the outer most loop.

    Those are the general rules, you do more of them you'll notice some unique
    patterns and it'll become more and more easy to implement them.

    Especially if you've already solved it using Memoization. It becomes almost
    trivial to convert one to the other and vice-versa.

*/

/* Time  Beats:  8.33% */
/* Space Beats: 32.75% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Tabulation {
private:
    const int MOD = 1e9 + 7;

public:
    int countStableSubsequences(vector<int>& nums)
    {
        const int N = nums.size();

        if (N == 1)
            return 1;

        if (N == 2)
            return 3;

        vector<vector<vector<int>>> dp(3, vector<vector<int>>(3, vector<int>(100002, 0LL)));

        // Base case
        for (int L_parity = 0; L_parity < 3; L_parity++)
        {
            for (int R_parity = 0; R_parity < 3; R_parity++)
            {
                if (L_parity != 0 || R_parity != 0)
                    dp[L_parity][R_parity][N] = 1;
                else
                    dp[L_parity][R_parity][N] = 0;
            }
        }


        // Fill table BACKWARDS!
        for (int idx = N-1; idx >= 0; idx--)
        {
            int curr_num_parity = (nums[idx] & 1) ? 1 : 2;

            for (int L_parity = 0; L_parity < 3; L_parity++)
            {
                for (int R_parity = 0; R_parity < 3; R_parity++)
                {
                    long long skip = dp[L_parity][R_parity][idx + 1];
                    long long take = 0LL;

                    if ((L_parity != R_parity) || 
                        (L_parity == R_parity && R_parity != curr_num_parity))
                    {
                        take = dp[R_parity][curr_num_parity][idx + 1];
                    }

                    dp[L_parity][R_parity][idx] = (skip + take) % MOD;
                }
            }
        }

        return dp[0][0][0];
    }
};
