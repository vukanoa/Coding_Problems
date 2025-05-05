/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3537) Fill a Special Grid
    ===========================

    ============
    Description:
    ============

    You are given a non-negative integer n representing a 2n x 2n grid. You
    must fill the grid with integers from 0 to 22n - 1 to make it special.
    A grid is special if it satisfies all the following conditions:

        + All numbers in the top-right quadrant are smaller than those in the
          bottom-right quadrant.

        + All numbers in the bottom-right quadrant are smaller than those in
          the bottom-left quadrant.

        + All numbers in the bottom-left quadrant are smaller than those in the
          top-left quadrant.

        Each of its quadrants is also a special grid.

    Return the special 2n x 2n grid.

    =====
    Note: Any 1x1 grid is special.
    =====

    =================================================
    FUNCTION: vector<vector<int>> specialGrid(int N);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 0
    Output: [[0]]
    Explanation: The only number that can be placed is 0, and there is only one
                 possible position in the grid.


    --- Example 2 ---
    Input: n = 1
    Output: [[3,0],[2,1]]
    Explanation:
    The numbers in each quadrant are:
        Top-right: 0
        Bottom-right: 1
        Bottom-left: 2
        Top-left: 3
    Since 0 < 1 < 2 < 3, this satisfies the given constraints.


    --- Example 3 ---
    Input: n = 2
    Output: [[15,12,3,0],[14,13,2,1],[11,8,7,4],[10,9,6,5]]
    Explanation:
    The numbers in each quadrant are:

        Top-right: 3, 0, 2, 1
        Bottom-right: 7, 4, 6, 5
        Bottom-left: 11, 8, 10, 9
        Top-left: 15, 12, 14, 13
        max(3, 0, 2, 1) < min(7, 4, 6, 5)
        max(7, 4, 6, 5) < min(11, 8, 10, 9)
        max(11, 8, 10, 9) < min(15, 12, 14, 13)

    This satisfies the first three requirements. Additionally, each quadrant is
    also a special grid. Thus, this is a special grid.


    *** Constraints ***
    0 <= n <= 10

*/

#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Basic recursion. You just need to be very careful when implementing.

*/

/* Time  Beats: 38.46% */
/* Space Beats: 23.08% */

/* Time  Complexity: O(4^N) */
/* Space Complexity: O(4^N) */
class Solution {
public:
    vector<vector<int>> specialGrid(int N)
    {
        int ROWS = 1 << N;
        int COLS = 1 << N;

        vector<vector<int>> grid(ROWS, vector<int>(COLS, 0));

        int num = 0;
        solve(grid, 0, 0, ROWS-1, COLS-1, num);

        return grid;
    }

private:
    void solve(vector<vector<int>>& grid, int row_top_left, int col_top_left, int row_bot_right, int col_bot_right, int& num)
    {
        if (row_top_left == row_bot_right && col_top_left == col_bot_right)
        {
            grid[row_top_left][col_top_left] = num;
            num++;
            return;
        }

        int width  = col_bot_right - col_top_left;
        int height = row_bot_right - row_top_left;

        int row_TOP;
        int col_TOP;

        int row_BOT;
        int col_BOT;

        // ===== I =====
        row_TOP = row_top_left;
        col_TOP = static_cast<int>(col_top_left + ceil(1.0 * width / 2));

        row_BOT = static_cast<int>(row_top_left + floor(1.0 * height / 2));
        col_BOT = col_bot_right;

        solve(grid, row_TOP, col_TOP, row_BOT, col_BOT, num);


        // ===== II =====
        row_TOP = static_cast<int>(row_top_left + ceil(1.0 * height / 2));
        col_TOP = static_cast<int>(col_top_left + ceil(1.0 * width / 2));

        row_BOT = row_bot_right;
        col_BOT = col_bot_right;

        solve(grid, row_TOP, col_TOP, row_BOT, col_BOT, num);

        // ===== III =====
        row_TOP = static_cast<int>(row_top_left + ceil(1.0 * height / 2));
        col_TOP = col_top_left;

        row_BOT = row_bot_right;
        col_BOT = static_cast<int>(col_top_left + floor(1.0 * width / 2));

        solve(grid, row_TOP, col_TOP, row_BOT, col_BOT, num);


        // ===== IV =====
        row_TOP = row_top_left;
        col_TOP = col_top_left;

        row_BOT = static_cast<int>(row_top_left + floor(1.0 * height / 2));
        col_BOT = static_cast<int>(col_top_left + floor(1.0 * width / 2));

        solve(grid, row_TOP, col_TOP, row_BOT, col_BOT, num);
    }
};
