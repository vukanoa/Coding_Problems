#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    1937) Maximum Number of Points with Cost
    ========================================

    ============
    Description:
    ============

    You are given an m x n integer matrix points (0-indexed). Starting with 0
    points, you want to maximize the number of points you can get from the
    matrix.

    To gain points, you must pick one cell in each row. Picking the cell at
    coordinates (r, c) will add points[r][c] to your score.

    However, you will lose points if you pick a cell too far from the cell that
    you picked in the previous row. For every two adjacent rows r and r + 1
    (where 0 <= r < m - 1), picking cells at coordinates (r, c1) and (r + 1,
    c2) will subtract abs(c1 - c2) from your score.

    Return the maximum number of points you can achieve.

    abs(x) is defined as:

    x for x >= 0.
    -x for x < 0.

    ===========================================================
    FUNCTION: long long maxPoints(vector<vector<int>>& points);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[1,2,3],[1,5,1],[3,1,1]]
    Output: 9
    Explanation:
    The blue cells denote the optimal cells to pick, which have coordinates
    (0,2), (1, 1), and (2, 0).
    You add 3 + 5 + 3 = 11 to your score.  However, you must subtract
    abs(2 - 1) + abs(1 - 0) = 2 from your score.  Your final score is:
    11 - 2 = 9.


    --- Example 2 ---
    Input: points = [[1,5],[2,3],[4,2]]
    Output: 11
    Explanation:
    The blue cells denote the optimal cells to pick, which have coordinates (0,
    1), (1, 1), and (2, 0).  You add 5 + 3 + 4 = 12 to your score.  However,
    you must subtract abs(1 - 1) + abs(1 - 0) = 1 from your score.  Your final
    score is 12 - 1 = 11.


    *** Constraints ***
    m == points.length
    n == points[r].length
    1 <= m, n <= 105
    1 <= m * n <= 105
    0 <= points[r][c] <= 105

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 95.10% */
/* Space Beats: 31.06% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(COLS)        */
class Solution {
public:
    long long maxPoints(vector<vector<int>>& points)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int ROWS = points.size();
        const int COLS = points[0].size();

        vector<long long> dp_row = vector<long long>(points[0].begin(), points[0].end()); // 0th row is the same as in points

        for (int r = 1; r < ROWS; r++)
        {
            vector<long long> dp_next_row = vector<long long>(points[r].begin(), points[r].end());

            vector<long long> left (COLS, 0);
            vector<long long> right(COLS, 0);

            left[0] = dp_row[0];
            for (int c = 1; c < COLS; c++)
                left[c] = max(dp_row[c], left[c-1] - 1);


            right[COLS - 1] = dp_row[COLS - 1];
            for (int c = COLS-2; c >= 0; c--)
                right[c] = max(dp_row[c], right[c+1] - 1);

            for (int c = 0; c < COLS; c++)
                dp_next_row[c] += max(left[c], right[c]);

            dp_row = dp_next_row;
        }

        return *std::max_element(dp_row.begin(), dp_row.end());
    }
};
