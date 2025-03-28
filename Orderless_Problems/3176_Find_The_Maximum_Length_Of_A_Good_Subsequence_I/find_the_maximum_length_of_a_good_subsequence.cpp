/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    3176) Find the Maximum Length of a Good Subsequence I
    =====================================================

    ============
    Description:
    ============

    You are given an integer array nums and a non-negative integer k.

    A sequence of integers seq is called good if there are at most k indices i
    in the range [0, seq.length - 2] such that seq[i] != seq[i + 1].

    Return the maximum possible length of a good
    of nums.

    ======================================================
    FUNCTION: int maximumLength(vector<int>& nums, int k);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1,1,3], k = 2
    Output: 4
    Explanation:
    The maximum length subsequence is [1,2,1,1,3].

    --- Example 2 ---
    Input: nums = [1,2,3,4,5,1], k = 0
    Output: 2
    Explanation:
    The maximum length subsequence is [1,2,3,4,5,1].


    *** Constraints ***
    1 <= nums.length <= 500
    1 <= nums[i] <= 10^9
    0 <= k <= min(nums.length, 25)

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    By-the-book Memoization that used 3D array as "memo".

    To figure out that you can do "Memoization", always look at the
    Constraints.


    This:
        1 <= nums[i] <= 10^9

    Highly suggests that you do not try to make an array based on all possible
    nums[i], since that is most certainly going to end up giving you a MLE.

    On the other hand:
        1 <= nums.length <= 500
        0 <= k <= min(nums.length, 25)

    Both of these should SCREAM to you that you're allowed to either make some
    states and then do something with those or that you can be a little less
    cognizant when it comes to Time Complexity.

    Therefore, we concluce we can do a "Memoization" technique with 3D array
    "memo".

    How do we determine states?

    First, position(i.e. "index") is a no-brainer.

    Second, since k will be AT MOST 25, that should be another state.

    But is that enough?
    No, it is not.

    But how do we determine that we have another dimension?

    There's not a clear-cut way to determine this as it depends on the problem.

    However, it's as intuitive as it gets.
    We know that we'll have DIFFERENT lengths of subsequences with different
    k values at different positions.

    That should suggest you that we need 3D array.


    It's difficult to explain, the best way to learn it is to do as many DP
    Memoization problems that are easier and then come back. Hopefully, you'll
    come to understand it.

    It's not too bad, but don't feel discouraged if you couldn't solve it
    yourself.

*/

/* Time  Beats: 34.61% */
/* Space Beats: 28.32% */

/* Time  Complexity: O(N^2 * k) */
/* Space Complexity: O(N^2 * k) */
class Solution {
private:
    int memo[501][501][26];

public:
    int maximumLength(vector<int>& nums, int k)
    {
        memset(memo, -1, sizeof(memo));

        return solve(0, -1, k, nums);
    }

private:
    int solve(int pos, int prev_pos, int curr_k, vector<int>& nums)
    {
        if (pos == nums.size())
            return 0;

        if (memo[pos][prev_pos + 1][curr_k] != -1)
            return memo[pos][prev_pos + 1][curr_k];

        int take = 0;
        int skip = 0;

        if (prev_pos == -1) // I.e. the sequence has NOT started yet
        {
            take = 1 + solve(pos + 1, pos, curr_k, nums);
            skip = 0 + solve(pos + 1,  -1, curr_k, nums);
        }
        else
        {
            if (nums[prev_pos] == nums[pos]) // SAME as the end of the prev seq
            {
                take = 1 + solve(pos + 1, pos, curr_k, nums);
            }
            else // DIFFERENT as the end of prev seq
            {
                if (curr_k > 0) // Can concatenate more
                    take = 1 + solve(pos + 1, pos, curr_k - 1, nums);

                skip = 0 + solve(pos + 1, prev_pos, curr_k, nums);
            }
        }

        return memo[pos][prev_pos + 1][curr_k] = max(take, skip);
    }
};
