#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    885) Spiral Matrix III
    ===========================

    ============
    Description:
    ============

    You start at the cell (rStart, cStart) of an rows x cols grid facing east.
    The northwest corner is at the first row and column in the grid, and the
    southeast corner is at the last row and column.

    You will walk in a clockwise spiral shape to visit every position in this
    grid. Whenever you move outside the grid's boundary, we continue our walk
    outside the grid (but may return to the grid boundary later.). Eventually,
    we reach all rows * cols spaces of the grid.

    Return an array of coordinates representing the positions of the grid in
    the order you visited them.

    ==========================================================================================
    FUNCTION: vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart);
    ==========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    // Go on LeetCode and look at the picture

    Input: rows = 1, cols = 4, rStart = 0, cStart = 0
    Output: [[0,0],[0,1],[0,2],[0,3]]

    --- Example 2 ---
    // Go on LeetCode and look at the picture

    Input: rows = 5, cols = 6, rStart = 1, cStart = 4
    Output:
    [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]

    *** Constraints ***
    1 <= rows, cols <= 100
    0 <= rStart < rows
    0 <= cStart < cols

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 86.90% */
/* Space Beats: 36.78% */

/* Time  Complexity: O(R * C) */
/* Space Complexity: O(1)     */
class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart)
    {
        int i = rStart;
        int j = cStart;

        /* Directions to move */
        int dir_i = 0;
        int dir_j = 1;

        int twice = 2;
        vector<vector<int>> result;

        int moves = 1;
        int next_moves = 2;

        while (result.size() < rows * cols)
        {
            if (i >= 0 && i < rows && j >= 0 && j < cols)
                result.push_back({i, j});

            i += dir_i;
            j += dir_j;

            moves -= 1;

            if (moves == 0)
            {
                int temp = dir_i;
                dir_i = dir_j;
                dir_j = -temp; // Right direction

                twice -= 1;
                if (twice == 0)
                {
                    twice = 2;
                    moves = next_moves;
                    next_moves++;
                }
                else
                    moves = next_moves - 1;
            }
        }

        return result;
    }
};
