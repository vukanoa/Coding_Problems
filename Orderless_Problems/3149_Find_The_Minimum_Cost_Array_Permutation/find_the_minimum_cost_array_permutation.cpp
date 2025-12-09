/*
    ============
    === HARD ===
    ============

    =============================================
    3149) Find the Minimum Cost Array Permutation
    =============================================

    ============
    Description:
    ============

    You are given an array nums which is a permutation of [0, 1, 2, ..., n -
    1]. The score of any permutation of [0, 1, 2, ..., n - 1] named perm is
    defined as:
    
    score(perm) = |perm[0] - nums[perm[1]]| + |perm[1] - nums[perm[2]]| + ... + |perm[n - 1] - nums[perm[0]]|
    
    Return the permutation perm which has the minimum possible score. If
    multiple permutations exist with this score, return the one that is
    lexicographically among them.

    =========================================================
    FUNCTION: vector<int> findPermutation(vector<int>& nums);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,0,2]
    Output: [0,1,2]
    Explanation: The lexicographically smallest permutation with minimum cost
                  is [0,1,2]. The cost of this permutation is |0 - 0| + |1 - 2|
                  + |2 - 1| = 2.

    --- Example 2 ---
    Input: nums = [0,2,1]
    Output: [0,2,1]
    Explanation: The lexicographically smallest permutation with minimum cost
                 is [0,2,1]. The cost of this permutation is |0 - 1| + |2 - 2|
                 + |1 - 0| = 2.

    *** Constraints ***
    2 <= n == nums.length <= 14
    nums is a permutation of [0, 1, 2, ..., n - 1].

*/

#include <climits>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 73.47% */
/* Space Beats: 54.08% */

/* Time  Complexity: O(N^2 * 2^N) */
/* Space Complexity: O(N   * 2^N) */
class Solution {
private:
    int next_index[14][16384];
    int dp[14][16384];

public:
    vector<int> findPermutation(vector<int>& nums)
    {
        memset(dp, -1, sizeof(dp));

        solve(1, 0, nums);

        vector<int> permutation;
        permutation.push_back(0);

        unsigned int taken_mask = 1;

        while (__builtin_popcount(taken_mask) < nums.size())
        {
            int curr = permutation.back();
            int next = next_index[curr][taken_mask];

            permutation.push_back(next);

            taken_mask |= (1 << next);
        }

        return permutation;
    }

private:
    int solve(unsigned int taken_mask, int current_index, vector<int>& nums)
    {
        const int N = nums.size();

        if (__builtin_popcount(taken_mask) == nums.size())
            return abs(current_index - nums[0]);

        if (dp[current_index][taken_mask] < 0)
        {
            dp[current_index][taken_mask] = INT_MAX;

            for (int candidate_index = 1; candidate_index < N; candidate_index++)
            {
                bool already_taken = (taken_mask & (1 << candidate_index)) != 0;

                if (already_taken)
                    continue; // skip this number

                // take this number
                int next_taken_mask = taken_mask | (1 << candidate_index);
                int cost = abs(current_index - nums[candidate_index]) + solve(next_taken_mask, candidate_index, nums);

                if (cost < dp[current_index][taken_mask])
                {
                    dp[current_index][taken_mask] = cost;
                    next_index[current_index][taken_mask] = candidate_index;
                }
            }
        }

        return dp[current_index][taken_mask];
    }
};
