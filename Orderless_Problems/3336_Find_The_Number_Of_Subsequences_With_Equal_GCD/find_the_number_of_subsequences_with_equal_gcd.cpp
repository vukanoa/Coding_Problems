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

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N^3) */
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
