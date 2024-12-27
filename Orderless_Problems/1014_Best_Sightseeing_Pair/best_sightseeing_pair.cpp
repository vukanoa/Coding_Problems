/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1014) Best Sightseeing Pair
    ===========================

    ============
    Description:
    ============

    You are given an integer array values where values[i] represents the value
    of the ith sightseeing spot. Two sightseeing spots i and j have a distance
    j - i between them.

    The score of a pair (i < j) of sightseeing spots is:
        values[i] + values[j] + i - j
    the sum of the values of the sightseeing spots, minus the distance between
    them.

    Return the maximum score of a pair of sightseeing spots.

    ===========================================================
    FUNCTION: int maxScoreSightseeingPair(vector<int>& values);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: values = [8,1,5,2,6]
    Output: 11
    Explanation: i = 0, j = 2, values[i] + values[j] + i - j = 8 + 5 + 0 - 2 = 11

    --- Example 2 ---
    Input: values = [1,2]
    Output: 2

    *** Constraints ***
    2 <= values.length <= 5 * 10^4
    1 <= values[i] <= 1000

*/

#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    There are N^2 possibilities, but that would be way to inefficient. Thus,
    we can improve our Time Complexity substantially by pre-computing elements.

    Since for each 'i' we'll consider 'j' that is on the right of 'i'(i.e. i<j)
    and since the total sum of the pair is calculate like this:

        values[i] + values[j] + i - j

    We can pre compute, going backwards, what is the biggest element minus its
    index.

    Why are we subtracting its index?
    Because that also goes into the equation.

    Let's take a look at out Example 1:
        values = [8,1,5,2,6]
        Output: 11

        We can precompute it like this:

            values = [8,1,5,2,6]
                dp = [8,3,3,2,2]

        Where did we get these 3s and 2s? And why those numbers?

        We start from the very last element at index N-1.
        We set its value in "dp" to be values[N-1] - (N-1).

        Now we start by 2nd to last element and we do this:

            dp[i] = max(values[i] - i, dp[i+1]);

        Meaning - The biggest of from this position onwards, all the way to the
        right is either:
            1) Current values minus its index, or
            2) Some right value minus its corresponding index

        Once we finish that, we simply iterate over "values" and for each elem,
        we do this: (except for the very last element, since that one doesn't
        have an element to its right)

            result = max(result, values[i] + i + dp[i+1])

    That's the entire idea. It's pretty simple.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  24.68% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values)
    {
        const int N = values.size();
        int result = 0;

        vector<int> dp(N, 0);
        dp[N-1] = values[N-1] - (N-1);

        for (int i = N-2; i >= 0; i--)
            dp[i] = max(values[i] - i, dp[i+1]);

        for (int i = 0; i < N-1; i++)
            result = max(result, values[i] + i + dp[i+1]);

        return result;
    }
};
