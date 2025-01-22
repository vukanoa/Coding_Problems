/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    3290) Maximum Multiplication Score
    ==================================

    ============
    Description:
    ============

    You are given an integer array a of size 4 and another integer array b of
    size at least 4.

    You need to choose 4 indices i0, i1, i2, and i3 from the array b such that
    i0 < i1 < i2 < i3. Your score will be equal to the value
    a[0] * b[i0] + a[1} * b[i1] + a[2] * b[i2] + a[3] * b[i3].

    Return the maximum score you can achieve.

    =============================================================
    FUNCTION: long long maxScore(vector<int>& a, vector<int>& b);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: a = [3,2,5,6], b = [2,-6,4,-5,-3,2,-7]
    Output: 26
    Explanation: We can choose the indices 0, 1, 2, and 5.
                 The score will be 3 * 2 + 2 * (-6) + 5 * 4 + 6 * 2 = 26.

    --- Example 2 ---
    Input: a = [-1,4,5,-2], b = [-5,-1,-3,-2,-4]
    Output: -1
    Explanation: We can choose the indices 0, 1, 3, and 4. The score will be
                 (-1) * (-5) + 4 * (-1) + 5 * (-2) + (-2) * (-4) = -1.


    *** Constraints ***
    a.length == 4
    4 <= b.length <= 10^5
    -10^5 <= a[i], b[i] <= 10^5

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The is a typical Memoization skip-take approach.

    Since we have ONLY two options:
        1. Either we take the current element, or
        2. We skip the current element

    It's also very important to notice that:
        1. If you TAKE a[0], then you must take b[i], where 'i' is >= 0.
        2. If you TAKE a[1], then you must take b[i], where 'i' is >= 1.
        3. If you TAKE a[2], then you must take b[i], where 'i' is >= 2.
        4. If you TAKE a[3], then you must take b[i], where 'i' is >= 3.

    it's important to know that if you're at, say, position 2 in a, then you
    need to add two more PRODUCTS.

    But, do you realize that this is a state?
    It's verly likely that we can end at this very state for more than one
    combination, therefore we ought to use MEMOIZATION technique, to reduce the
    Time Complexity drastically.

*/

/* Time  Beats: 29.35% */
/* Space Beats: 27.69% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N * M) */
class Solution {
public:
    long long maxScore(vector<int>& a, vector<int>& b)
    {
        vector<vector<long long>> dp(a.size(), vector<long long>(b.size(), -1));

        return dfs(a, b, dp, 0, 0);
    }

private:
    long long dfs(vector<int>& a, vector<int>& b, vector<vector<long long>>& dp, int idx1, int idx2)
    {
        if (idx1 >= a.size())
            return 0;

        if (idx2 >= b.size())
            return LLONG_MIN;

        if (dp[idx1][idx2] != -1)
            return dp[idx1][idx2];

        long long t1 = a[idx1];
        long long t2 = b[idx2];

        long long take = dfs(a, b, dp, idx1+1, idx2+1);
        long long skip = dfs(a, b, dp, idx1  , idx2+1);

        if (take != LLONG_MIN)
            skip = max(skip, t1 * t2 + take);

        return dp[idx1][idx2] = skip;
    }
};
