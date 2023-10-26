#include <iostream>
#include <vector>
#include <climits>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2017) Grid Game
    ===========================

    ============
    Description:
    ============

    You are given a 0-indexed 2D array grid of size 2 x n, where grid[r][c]
    represents the number of points at position (r, c) on the matrix. Two
    robots are playing a game on this matrix.

    Both robots initially start at (0, 0) and want to reach (1, n-1). Each
    robot may only move to the right ((r, c) to (r, c + 1)) or down ((r, c) to
    (r + 1, c)).

    At the start of the game, the first robot moves from (0, 0) to (1, n-1),
    collecting all the points from the cells on its path. For all cells (r, c)
    traversed on the path, grid[r][c] is set to 0. Then, the second robot moves
    from (0, 0) to (1, n-1), collecting the points on its path. Note that their
    paths may intersect with one another.

    The first robot wants to minimize the number of points collected by the
    second robot. In contrast, the second robot wants to maximize the number of
    points it collects. If both robots play optimally, return the number of
    points collected by the second robot.

    =======================================================
    FUNCTION: long long gridGame(vector<vector<int>>& mat);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+              +-----+-----+-----+
    |  2  |  5  |  4  |              |  0  |  0  |  4  |
    +-----+-----+-----+     ==>      +-----+-----+-----+
    |  1  |  5  |  1  |              |  1  |  0  |  0  |
    +-----+-----+-----+              +-----+-----+-----+

    Input: grid = [[2,5,4],[1,5,1]]
    Output: 4
    Explanation: The optimal path taken by the first robot is shown in red, and
                 the optimal path taken by the second robot is shown in blue.
                 The cells visited by the first robot are set to 0.  The second
                 robot will collect 0 + 0 + 4 + 0 = 4 points.


    --- Example 2 ---
    +-----+-----+-----+              +-----+-----+-----+
    |  3  |  3  |  1  |              |  0  |  3  |  1  |
    +-----+-----+-----+     ==>      +-----+-----+-----+
    |  8  |  5  |  2  |              |  0  |  0  |  0  |
    +-----+-----+-----+              +-----+-----+-----+

    Input: grid = [[3,3,1],[8,5,2]]
    Output: 4
    Explanation: The optimal path taken by the first robot is shown in red, and
                 the optimal path taken by the second robot is shown in blue.
                 The cells visited by the first robot are set to 0.  The second
                 robot will collect 0 + 3 + 1 + 0 = 4 points.


    --- Example 3 ---
    +-----+-----+-----+-----+              +-----+-----+-----+-----+
    |  1  |  3  |  1  | 15  |              |  0  |  0  |  0  |  0  |
    +-----+-----+-----+-----+     ==>      +-----+-----+-----+-----+
    |  1  |  3  |  3  |  1  |              |  1  |  3  |  3  |  0  |
    +-----+-----+-----+-----+              +-----+-----+-----+-----+

    Input: grid = [[1,3,1,15],[1,3,3,1]]
    Output: 7
    Explanation: The optimal path taken by the first robot is shown in red, and
                 the optimal path taken by the second robot is shown in blue.
                 The cells visited by the first robot are set to 0.  The second
                 robot will collect 0 + 1 + 3 + 3 + 0 = 7 points.


    *** Constraints ***
    grid.length == 2
    n == grid[r].length
    1 <= n <= 5 * 104
    1 <= grid[r][c] <= 105

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 91.05% */
/* Space Beats: 54.10% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long gridGame(vector<vector<int>>& mat)
    {
        long long n = mat[0].size();

        long long result = LONG_MAX;
        long long row0 = 0;
        long long row1 = 0;

        for(int i = 0; i < n; i++)
        {
            row0 += mat[0][i];
            row1 += mat[1][i];
        }
        row0 += mat[1][n-1];
        row1 -= mat[1][n-1];

        long long score = 0;
        long long sum0  = 0;
        long long sum1  = 0;

        for(int i = 0; i < n; i++)
        {
            long long c1 = sum1;
            long long c2 = row0 - sum0 - mat[1][n-1] - mat[0][i];
            long long score = std::max(c1, c2);

            result = std::min(result, score);
            sum0 += mat[0][i];
            sum1 += mat[1][i];
        }

        return result;
    }
};
