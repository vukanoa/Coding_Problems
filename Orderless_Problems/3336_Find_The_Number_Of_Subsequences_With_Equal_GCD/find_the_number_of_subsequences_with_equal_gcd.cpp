/*
    ============
    === HARD ===
    ============

    ====================================================
    3336) Find the Number of Subsequences with Equal GCD
    ====================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Your task is to find the number of pairs of non-empty (seq1, seq2) of nums
    that satisfy the following conditions:

        + The subsequences seq1 and seq2 are disjoint, meaning no index of nums
          is common between them.

        + The of the elements of seq1 is equal to the GCD of the elements of
          seq2.

    Return the total number of such pairs.

    Since the answer may be very large, return it modulo 109 + 7.

    ======================================================
    FUNCTION: int subsequencePairCount(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4]
    Output: 10

    --- Example 2 ---
    Input: nums = [10,20,30]
    Output: 2

    --- Example 3 ---
    Input: nums = [1,1,1,1]
    Output: 50


    *** Constraints ***
    1 <= nums.length <= 200
    1 <= nums[i] <= 200

*/

#include <cstring>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Classic Skip-Take Memoization.

*/

/* Time  Beats: 47.82% */
/* Space Beats: 62.61% */

/* Time  Complexity: O(M * N^2 * logN) */
/* Space Complexity: O(M * N^2)        */
class Solution_Top_Down__Memoization {
private:
    static const int MOD = 1e9 + 7;
    int memo[201][201][201];

public:

    int subsequencePairCount(vector<int>& nums)
    {
        /* Memset */
        memset(memo, -1, sizeof(memo));

        return solve(0, 0, 0, nums);
    }

private:
    int solve(int idx, int seq1_gcd, int seq2_gcd, vector<int>& nums)
    {
        const int N = nums.size();

        if (idx == N)
            return (seq1_gcd != 0 && seq1_gcd == seq2_gcd);

        if (memo[idx][seq1_gcd][seq2_gcd] != -1)
            return memo[idx][seq1_gcd][seq2_gcd];

        int result = 0;

        // Skip
        result = solve(idx + 1, seq1_gcd, seq2_gcd, nums);

        // Take in seq1
        int new_seq1_gcd = (seq1_gcd == 0) ? nums[idx] : gcd(seq1_gcd, nums[idx]);
        result = (result + solve(idx + 1, new_seq1_gcd, seq2_gcd, nums)) % MOD;

        // Take in seq2
        int new_seq2_gcd = (seq2_gcd == 0) ? nums[idx] : gcd(seq2_gcd, nums[idx]);
        result = (result + solve(idx + 1, seq1_gcd, new_seq2_gcd, nums)) % MOD;

        return memo[idx][seq1_gcd][seq2_gcd] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Bottom-Up implementation, same idea.

*/

/* Time  Beats: 13.04% */
/* Space Beats:  9.56% */

/* Time  Complexity: O(M * N^2 * logN) */
/* Space Complexity: O(M * N^2)        */
class Solution_Bottom_Up__Tabulation {
public:
    int subsequencePairCount(vector<int>& nums)
    {
        const int N = nums.size();
        const int MOD = 1e9 + 7;

        // dp[i][g1][g2]  -->  After processing first 'i' elements
        vector<vector<vector<int>>> dp(N + 1,vector<vector<int>>(201, vector<int>(201, 0)));
        dp[0][0][0] = 1;

        for (int i = 0; i < N; i++)
        {
            int num = nums[i];

            for (int seq1_gcd = 0; seq1_gcd <= 200; seq1_gcd++)
            {
                for (int seq2_gcd = 0; seq2_gcd <= 200; seq2_gcd++)
                {
                    if (dp[i][seq1_gcd][seq2_gcd] == 0)
                        continue;

                    long long ways = dp[i][seq1_gcd][seq2_gcd];

                    ////////////////
                    /// SKIP num ///
                    ////////////////
                    dp[i + 1][seq1_gcd][seq2_gcd] = (dp[i + 1][seq1_gcd][seq2_gcd] +
                                                     dp[i    ][seq1_gcd][seq2_gcd]) % MOD;

                    ////////////////////////
                    /// TAKE num in seq1 ///
                    ////////////////////////
                    int new_seq1_gcd = (seq1_gcd == 0) ? num : gcd(seq1_gcd, num);

                    dp[i + 1][new_seq1_gcd][seq2_gcd] = (dp[i + 1][new_seq1_gcd][seq2_gcd] +
                                                         dp[i    ][    seq1_gcd][seq2_gcd]) % MOD;

                    ////////////////////////
                    /// TAKE num in seq2 ///
                    ////////////////////////
                    int new_seq2_gcd = (seq2_gcd == 0) ? num : gcd(seq2_gcd, num);

                    dp[i + 1][seq1_gcd][new_seq2_gcd] = (dp[i + 1][seq1_gcd][new_seq2_gcd] +
                                                         dp[i    ][seq1_gcd][    seq2_gcd]) % MOD;
                }
            }
        }

        long long result = 0;
        for (int curr_gcd = 1; curr_gcd <= 200; curr_gcd++)
            result = (result + dp[N][curr_gcd][curr_gcd]) % MOD;

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however this one a better Space Complexity by an order of M.

*/

/* Time  Beats: 30.43% */
/* Space Beats: 22.61% */

/* Time  Complexity: O(M * N^2 * logN) */
/* Space Complexity: O(N^2)            */
class Solution_Bottom_Up__Tabulation__Space_Optimized {
public:
    static const int MOD = 1e9 + 7;

    int subsequencePairCount(vector<int>& nums) {

        vector<vector<int>> curr(201, vector<int>(201, 0));
        curr[0][0] = 1;

        for (const int& num : nums)
        {
            vector<vector<int>> next(201, vector<int>(201, 0));

            for (int seq1_gcd = 0; seq1_gcd <= 200; seq1_gcd++)
            {
                for (int seq2_gcd = 0; seq2_gcd <= 200; seq2_gcd++)
                {
                    if (curr[seq1_gcd][seq2_gcd] == 0)
                        continue;

                    ////////////////
                    /// SKIP num ///
                    ////////////////
                    next[seq1_gcd][seq2_gcd] = (next[seq1_gcd][seq2_gcd] +
                                                curr[seq1_gcd][seq2_gcd]) % MOD;

                    ////////////////////////
                    /// TAKE num in seq1 ///
                    ////////////////////////
                    int new_seq1_gcd = (seq1_gcd == 0 ? num : gcd(seq1_gcd, num));

                    next[new_seq1_gcd][seq2_gcd] = (next[new_seq1_gcd][seq2_gcd] +
                                                    curr[    seq1_gcd][seq2_gcd]) % MOD;

                    ////////////////////////
                    /// TAKE num in seq2 ///
                    ////////////////////////
                    int new_seq2_gcd = (seq2_gcd == 0 ? num : gcd(seq2_gcd, num));

                    next[seq1_gcd][new_seq2_gcd] = (next[seq1_gcd][new_seq2_gcd] +
                                                    curr[seq1_gcd][    seq2_gcd]) % MOD;
                }
            }

            swap(curr, next);
        }

        long long result = 0;
        for (int curr_gcd = 1; curr_gcd <= 200; curr_gcd++)
            result = (result + curr[curr_gcd][curr_gcd]) % MOD;

        return result;
    }
};
