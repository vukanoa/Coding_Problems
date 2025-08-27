/*
    ============
    === HARD ===
    ============

    =================================================
    3459) Length of Longest V-Shaped Diagonal Segment
    =================================================

    ============
    Description:
    ============


    You are given a 2D integer matrix grid of size n x m, where each element is
    either 0, 1, or 2.

    A V-shaped diagonal segment is defined as:

    The segment starts with 1.
    The subsequent elements follow this infinite sequence: 2, 0, 2, 0, ....
    The segment:
        + Starts along a diagonal direction (top-left to bottom-right,
          bottom-right to top-left, top-right to bottom-left, or bottom-left to
          top-right).
        + Continues the sequence in the same diagonal direction.
        + Makes at most one clockwise 90-degree turn to another diagonal
          direction while maintaining the sequence.


        (This one is difficult to draw in ASCII, please check out the problem
          on the LeetCode itself)

    Return the length of the longest V-shaped diagonal segment. If no valid
    segment exists, return 0.

    ========================================================
    FUNCTION: int lenOfVDiagonal(vector<vector<int>>& grid);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
    Explanation:
    The longest V-shaped diagonal segment has a length of 5 and follows these
    coordinates: (0,2) → (1,3) → (2,4), takes a 90-degree clockwise turn at
    (2,4), and continues as (3,3) → (4,2).

    --- Example 2 ---
    Input: grid = [[2,2,2,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
    The longest V-shaped diagonal segment has a length of 4 and follows these
    coordinates: (2,3) → (3,2), takes a 90-degree clockwise turn at (3,2), and
    continues as (2,1) → (1,0).

    --- Example 3 ---
    Input: grid = [[1,2,2,2,2],[2,2,2,2,0],[2,0,0,0,0],[0,0,2,2,2],[2,0,0,2,0]]
    Explanation:
    The longest V-shaped diagonal segment has a length of 5 and follows these
    coordinates: (0,0) → (1,1) → (2,2) → (3,3) → (4,4).

    --- Example 4 ---
    Input: grid = [[1]]
    Output: 1
    Explanation:
    The longest V-shaped diagonal segment has a length of 1 and follows these
    coordinates: (0,0).


    *** Constraints ***
    n == grid.length
    m == grid[i].length
    1 <= n, m <= 500
    grid[i][j] is either 0, 1 or 2.

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Skip-Take Memoization)

*/

/* Time  Beats: 83.96% */
/* Space Beats: 74.33% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
private:
    int directions[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
    int memo[501][501][4][2];

public:
    int lenOfVDiagonal(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        /* Memset */
        memset(memo, -1, sizeof(memo));

        int result = 0;
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                if (grid[i][j] == 1)
                {
                    for (int direction = 0; direction < 4; ++direction)
                    {
                        int output = solve(i, j, direction, true, 2, grid) + 1;
                        result = max(result, output);
                    }
                }
            }
        }

        return result;
    }

private:
    int solve(int curr_row, int curr_col, int direction, bool clockwise_rotate, int target, vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int next_row = curr_row + directions[direction][0];
        int next_col = curr_col + directions[direction][1];

        // If it goes beyond the boundary or the next node's value is not
        // the target value, then return
        if (next_row < 0 || next_col < 0 || next_row >= ROWS || next_col >= COLS || grid[next_row][next_col] != target)
            return 0;

        if (memo[next_row][next_col][direction][clockwise_rotate] != -1)
            return memo[next_row][next_col][direction][clockwise_rotate];

        // SKIP rotation
        int max_step = solve(next_row, next_col, direction, clockwise_rotate, 2 - target, grid);

        // TAKE rotation
        if (clockwise_rotate)
        {
            // Clockwise rotate 90 degrees
            int output = solve(next_row, next_col, (direction + 1) % 4, false, 2 - target, grid);
            max_step = max(max_step, output);
        }

        return memo[next_row][next_col][direction][clockwise_rotate] = max_step + 1;
    }
};
