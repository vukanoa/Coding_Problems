/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    3952) Minimum Total Value of Covered Indices
    ============================================

    ============
    Description:
    ============

    You are given an integer array nums of length n and a binary string s of
    length n, where s[i] == '1' means index i initially contains a token and
    s[i] == '0' means it does not.

    You may perform the following operation any number of times:

        + Choose a token currently located at index i, where i > 0, such that
          this token has not been moved before.

        + Move this token from index i to index i - 1.

    An index is considered covered if it contains a token after all moves.

    Return an integer denoting the maximum total value of nums at the covered
    indices after optimally performing the operations.


    ==========================================================
    FUNCTION: long long maxTotal(vector<int>& nums, string s);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [9,2,6,1], s = "0101"
    Output: 15
    Explanation:
        Initially, indices 1 and 3 contain tokens.
        Move the token from index 3 to index 2.
        Move the token from index 1 to index 0.
        The covered indices are [0, 2], so the total value is nums[0] + nums[2]
        = 9 + 6 = 15.

    --- Example 2 ---
    Input: nums = [5,1,4], s = "001"
    Output: 4
    Explanation:
        Initially, only index 2 contains a token.
        It is optimal to leave the token at index 2.
        The covered index is [2], so the total value is nums[2] = 4.

    --- Example 3 ---
    Input: nums = [9,3,5], s = "011"
    Output: 14
    Explanation:
        Initially, indices 1 and 2 contain tokens.
        Move the token from index 1 to index 0.
        The covered indices are [0, 2], so the total value is nums[0] + nums[2]
        = 9 + 5 = 14.


    *** Constraints ***
    1 <= n == nums.length == s.length <= 10^5
    1 <= nums[i] <= 10^5
    s[i] is either '0' or '1'

*/

#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simple Take-Skip Memoization problem.

*/

/* Time  Beats: 40.89% */
/* Space Beats: 42.65% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    static constexpr int MAX_SIZE = 1e5;
    long long memo[MAX_SIZE + 1][2];

    long long maxTotal(vector<int>& nums, string s)
    {
        const int N = s.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(0, 0, nums, s);
    }

private:
    long long solve(int idx, int taken, vector<int>& nums, string& s)
    {
        const int N = s.size();

        if (idx >= N)
            return 0;

        if (memo[idx][taken] != -1)
            return memo[idx][taken];

        long long skip = solve(idx+1, 0, nums, s); /* Skip */
        long long take = 0LL;

        /* Take */
        if (s[idx] == '1' &&  ! taken)
            take = max(take, 1LL * nums[idx] + solve(idx+1, 0, nums, s));

        if (idx+1 < N && s[idx+1] == '1')
            take = max(take, 1LL * nums[idx] + solve(idx+1, 1, nums, s));

        return memo[idx][taken] = max(skip, take);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    If you inspect closely, you'll realize that we can actually be Greedy.

    First thing--Leading 1s MUST ALWAYS be taken. We cannot move any of those
    tokens to its left position, therefore we preprocess those first.

    Now every remaining CONTIGUOUS block of 1s we are also going to consider
    one element BEFORE the CONTIGUOUS block of 1s, also as a part of this
    "block", or segment.

    Why are we doing that?

    Because in order to maximize the segment, we want to maximize the
    contribution to the final "result". The optimal choise is to take ALL of
    the value in the segment EXCEPT the minimum one, since exlucding the
    MINIMUM one ALWAYS gives the max possible sum.

    And we can move the "token" only to the left, that's why we're processing
    ONE element BEFORE the current CONTIGUOUS block.

    Therefore, for each block of CONSECUTIVE 1s, we compute the sum of the
    entire segment(i.e. previous elemnt + contiguous block of elements) and we
    subtract the MINIMUM element in that segment.

*/

/* Time  Beats: 95.48% */
/* Space Beats: 94.81% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Greedy {
public:
    long long maxTotal(vector<int>& nums, string s)
    {
        const int N = nums.size();
        long long result = 0LL;

        int i = 0;
        while (i < N && s[i] == '1')
        {
            result += nums[i];

            // Increment
            i++;
        }

        while (i < N)
        {
            if (s[i] == '1')
            {
                int min_elem_within_segment = nums[i-1];

                /* Process the current Segment */
                long long sum_of_segment = nums[i-1];
                while (i < N && s[i] == '1')
                {
                    sum_of_segment += nums[i];

                    if (nums[i] < min_elem_within_segment)
                        min_elem_within_segment = nums[i];

                    // Increment
                    i++;
                }

                result += sum_of_segment - min_elem_within_segment;
            }

            // Increment
            i++;
        }

        return result;
    }
};
