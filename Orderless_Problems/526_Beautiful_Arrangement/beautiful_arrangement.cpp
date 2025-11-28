/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    526) Beautiful Arrangement
    ===========================

    ============
    Description:
    ============

    Suppose you have n integers labeled 1 through n. A permutation of those n
    integers perm (1-indexed) is considered a beautiful arrangement if for
    every i (1 <= i <= n), either of the following is true:

        + perm[i] is divisible by i.
        + i is divisible by perm[i].

    Given an integer n, return the number of the beautiful arrangements that
    you can construct.

    ======================================
    FUNCTION: int countArrangement(int n);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2
    Output: 2
    Explanation:
    The first beautiful arrangement is [1,2]:
        - perm[1] = 1 is divisible by i = 1
        - perm[2] = 2 is divisible by i = 2
    The second beautiful arrangement is [2,1]:
        - perm[1] = 2 is divisible by i = 1
        - i = 2 is divisible by perm[2] = 1

    --- Example 2 ---
    Input: n = 1
    Output: 1


    *** Constraints ***
    1 <= n <= 15

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.97% */
/* Space Beats: 32.97% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(2^N)     */
class Solution {
public:
    int countArrangement(int n)
    {
        int total_masks = 1 << n;

        vector<int> dp(total_masks, 0);
        dp[0] = 1;

        for (int i = 0; i < total_masks; i++)
        {
            // How many numbers are already placed
            int curr_pos = __builtin_popcount(i);

            for (int num_idx = 0; num_idx < n; num_idx++)
            {
                // Check if (num_idx+1) is not yet used
                if ((i & (1 << num_idx)) == 0)
                {
                    int new_used_mask = i | (1 << num_idx);

                    if (((curr_pos + 1) % (num_idx + 1)) == 0 || ((num_idx + 1) % (curr_pos + 1)) == 0)
                        dp[new_used_mask] = dp[new_used_mask] + dp[i];
                }
            }
        }

        return dp[(1 << n) - 1];
    }
};
