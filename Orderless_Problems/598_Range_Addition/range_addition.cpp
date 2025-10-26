/*
    ============
    === EASY ===
    ============

    ===========================
    598) Range Addition II
    ===========================

    ============
    Description:
    ============

    You are given an m x n matrix M initialized with all 0's and an array of
    operations ops, where ops[i] = [ai, bi] means M[x][y] should be
    incremented by one for all 0 <= x < ai and 0 <= y < bi.

    Count and return the number of maximum integers in the matrix after
    performing all the operations.

    ===============================================================
    FUNCTION: int maxCount(int m, int n, vector<vector<int>>& ops);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: m = 3, n = 3, ops = [[2,2],[3,3]]
    Output: 4
    Explanation: The maximum integer in M is 2, and there are four of it in M.
                 So return 4.

    --- Example 2 ---
    Input: m = 3, n = 3,
    ops = [[2,2],[3,3],[3,3],[3,3],[2,2],[3,3],[3,3],[3,3],[2,2],[3,3],[3,3],[3,3]]
    Output: 4

    --- Example 3 ---
    Input: m = 3, n = 3, ops = []
    Output: 9


    *** Constraints ***
    1 <= m, n <= 4 * 10^4
    0 <= ops.length <= 10^4
    ops[i].length == 2
    1 <= ai <= m
    1 <= bi <= n

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  73.76% */

/* Time  Complexity: O(k) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops)
    {
        int ROWS = m;
        int COLS = n;

        int k = ops.size();
        for (int i = 0; i < k; i++)
        {
            int L = ops[i][0]; // Row limit from operation
            int R = ops[i][1]; // Column limit from operation

            // Update the minimum dimensions based on operations
            COLS = min(COLS, R); // Update column limit
            ROWS = min(ROWS, L); // Update row limit
        }

        // Return the count of integers with the maximum value
        return COLS * ROWS;
    }
};
