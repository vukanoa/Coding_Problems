/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    3796) Find Maximum Value in a COnstrainer Sequence
    ==================================================

    ============
    Description:
    ============

    You are given an integer n, a 2D integer array restrictions, and an integer
    array diff of length n - 1. Your task is to construct a sequence of length
    n, denoted by a[0], a[1], ..., a[n - 1], such that it satisfies the
    following conditions:

        + a[0] is 0.

        + All elements in the sequence are non-negative.

        + For every index i (0 <= i <= n - 2), abs(a[i] - a[i + 1]) <= diff[i].

        + For each restrictions[i] = [idx, maxVal], the value at position idx
          in the sequence must not exceed maxVal (i.e., a[idx] <= maxVal).

    Your goal is to construct a valid sequence that maximizes the largest value
    within the sequence while satisfying all the above conditions.

    Return an integer denoting the largest value present in such an optimal
    sequence.

    ======================================================================================
    FUNCTION: int findMaxVal(int n, vector<vector<int>>& restrictions, vector<int>& diff);
    ======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10, restrictions = [[3,1],[8,1]], diff = [2,2,3,1,4,5,1,1,2]
    Output: 6
    Explanation:
        The sequence a = [0, 2, 4, 1, 2, 6, 2, 1, 1, 3] satisfies the given
        constraints (a[3] <= 1 and a[8] <= 1). The maximum value in the
        sequence is 6.

    --- Example 2 ---
    Input: n = 8, restrictions = [[3,2]], diff = [3,5,2,4,2,3,1]
    Output: 12
    Explanation:
        The sequence a = [0, 3, 3, 2, 6, 8, 11, 12] satisfies the given
        constraints (a[3] <= 2). The maximum value in the sequence is 12.


    *** Constraints ***
    2 <= n <= 10^5
    1 <= restrictions.length <= n - 1
    restrictions[i].length == 2
    restrictions[i] = [idx, maxVal]
    1 <= idx < n
    1 <= maxVal <= 10^6
    diff.length == n - 1
    1 <= diff[i] <= 10
    The values of restrictions[i][0] are unique.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 79.03% */
/* Space Beats: 92.74% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int findMaxVal(int n, vector<vector<int>>& restrictions, vector<int>& diff)
    {
        vector<int> upper_limit(n, 1e9);

        for (auto& entry : restrictions)
        {
            const int& idx     = entry[0];
            const int& max_val = entry[1];

            upper_limit[idx] = max_val;
        }

        for (int i = n-2; i >= 0; i--)
        {
            upper_limit[i] = min(upper_limit[i], upper_limit[i+1] + diff[i]);
        }
        upper_limit[0] = 0; // But it doesn't matter, we never consider it


        int result = 0;
        for (int i = 1; i < n; i++)
        {
            upper_limit[i] = min(upper_limit[i], upper_limit[i-1] + diff[i-1]);

            result = max(result, upper_limit[i]);
        }

        return result;
    }
};
