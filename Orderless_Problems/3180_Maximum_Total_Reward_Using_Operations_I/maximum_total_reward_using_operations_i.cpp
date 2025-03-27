/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3180) Maximum Total Reward Using Operations I
    =============================================

    ============
    Description:
    ============

    You are given an integer array rewardValues of length n, representing the
    values of rewards.

    Initially, your total reward x is 0, and all indices are unmarked. You are
    allowed to perform the following operation any number of times:

        + Choose an unmarked index i from the range [0, n - 1].

        + If rewardValues[i] is greater than your current total reward x, then
          add rewardValues[i] to x (i.e., x = x + rewardValues[i]), and mark
          the index i.

    Return an integer denoting the maximum total reward you can collect by
    performing the operations optimally.

    ========================================================
    FUNCTION: int maxTotalReward(vector<int>& rewardValues);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: rewardValues = [1,1,3,3]
    Output: 4
    Explanation: During the operations, we can choose to mark the indices 0 and
                 2 in order, and the total reward will be 4, which is the
                 maximum.

    --- Example 2 ---
    Input: rewardValues = [1,6,4,3,2]
    Output: 11
    Explanation: Mark the indices 0, 2, and 1 in order. The total reward will
                 then be 11, which is the maximum.


    *** Constraints ***
    1 <= rewardValues.length <= 2000
    1 <= rewardValues[i] <= 2000

*/

#include <algorithm>
#include <cstring>
#include <unordered_set>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    This is one by-the-book Memoization Problem. It doesn't get more basic than
    this.

    The difficult part was to observe that the answer will NEVER be above 4000.

    Proof:

        Lets say the last element we picked is X.

        The max possible value of reward before that is X-1.
        This implies max possible reward is X + (X-1) = 2*X-1.

        Since max value of X is 2000, so the max value of reward is 3999.

    With this information in mind we can use a function with parameters:
    sum and pos.

    sum --> sum of total rewards till that point
    pos --> current position in the array

    Using these two parameters we get a unique state.

    We can use a memo of the form dp[2001][4000].
    (pos < 2001 and sum < 4000)

    Make sure you filter out the duplicate elements out of the array as we will
    never be able to pick the same element twice

*/

/* Time  Beats: 20.13% */
/* Space Beats: 54.63% */

/*
    Time  Complexity: O(N * logN + N * S)

    Where 'S is the number of unique states. In our Problem S can be from
    1 to 4000.
*/
/*
    Space Complexity: O(N * S)

    Where 'S is the number of unique states. In our Problem S can be from
    1 to 4000.

*/
class Solution {
private:
    int memo[2001][4000]; // On the stack because it's a bit faster

public:
    int maxTotalReward(vector<int>& rewardValues)
    {
        /* Reserve space for the "memo" that is on the Stack */
        memset(memo, -1, sizeof(memo));

        /* Make Unique */
        unordered_set<int> uset(rewardValues.begin(), rewardValues.end());
        vector<int> uniq_nums(uset.begin(), uset.end());

        /* Sort */
        sort(uniq_nums.begin(), uniq_nums.end());

        return solve(0, 0, uniq_nums);
    }

private:
    int solve(int pos, int sum, vector<int>& uniq_vec)
    {
        if (pos == uniq_vec.size())
            return 0LL;

        if (memo[pos][sum] != -1)
            return memo[pos][sum];

        int take = 0;
        int skip = 0;

        if (uniq_vec[pos] > sum)
            take = uniq_vec[pos] + solve(pos + 1, uniq_vec[pos] + sum, uniq_vec);

        skip = solve(pos + 1, sum, uniq_vec);

        return memo[pos][sum] = max(take, skip);
    }
};
