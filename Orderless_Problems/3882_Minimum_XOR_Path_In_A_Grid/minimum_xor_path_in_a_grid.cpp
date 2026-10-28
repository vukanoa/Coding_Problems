/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    3882) Minimum XOR Path in a Grid
    ================================

    ============
    Description:
    ============

    You are given a 2D integer array grid of size m * n.

    You start at the top-left cell (0, 0) and want to reach the bottom-right
    cell (m - 1, n - 1).

    At each step, you may move either right or down.

    The cost of a path is defined as the bitwise XOR of all the values in the
    cells along that path, including the start and end cells.

    Return the minimum possible XOR value among all valid paths from (0, 0) to
    (m - 1, n - 1).

    =================================================
    FUNCTION: int minCost(vector<vector<int>>& grid);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,2],[3,4]]
    Output: 6
    Explanation:
    There are two valid paths:
        (0, 0) → (0, 1) → (1, 1) with XOR: 1 XOR 2 XOR 4 = 7
        (0, 0) → (1, 0) → (1, 1) with XOR: 1 XOR 3 XOR 4 = 6
    The minimum XOR value among all valid paths is 6.


    --- Example 2 ---
    Input: grid = [[6,7],[5,8]]
    Output: 9
    Explanation:
    There are two valid paths:
        (0, 0) → (0, 1) → (1, 1) with XOR: 6 XOR 7 XOR 8 = 9
        (0, 0) → (1, 0) → (1, 1) with XOR: 6 XOR 5 XOR 8 = 11
    The minimum XOR value among all valid paths is 9.


    --- Example 3 ---
    Input: grid = [[2,7,5]]
    Output: 0
    Explanation:
    There is only one valid path:
        (0, 0) → (0, 1) → (0, 2) with XOR: 2 XOR 7 XOR 5 = 0
    The XOR value of this path is 0, which is the minimum possible.


    *** Constraints ***
    1 <= m == grid.length <= 1000
    1 <= n == grid[i].length <= 1000
    m * n <= 1000
    0 <= grid[i][j] <= 1023

*/

#include <bitset>
#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 22.73% */
/* Space Beats: 38.84% */

/* Time  Complexity: O(ROWS * COLS * 1024) */
/* Space Complexity: O(ROWS * COLS * 1024) */
class Solution_Top_Down__Memoization_3D {
private:
    vector<vector<vector<int>>> memo;
public:

    int minCost(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        /* Memset */
        memo.assign(ROWS, vector<vector<int>>(COLS, vector<int>(1024, -1)));

        return solve(0, 0, 0, grid);
    }

private:
    int solve(int row, int col, int xor_value, vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row >= ROWS || col >= COLS)
            return INT_MAX;


        xor_value = xor_value ^ grid[row][col];

        if (row == ROWS-1 && col == COLS-1)
            return xor_value;

        if (memo[row][col][xor_value] != -1)
            return memo[row][col][xor_value];


        int right = solve(row  , col+1, xor_value, grid);
        int down  = solve(row+1, col  , xor_value, grid);

        return memo[row][col][xor_value] = min(right, down);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 97.93% */
/* Space Beats: 96.28% */

/* Time  Complexity: O(ROWS * COLS * 1024) */
/* Space Complexity: O(   1 * COLS * 1024) */
class Solution_Bottom_Up__Tabulation__Bitset {
public:
    int minCost(vector<vector<int>>& grid)
    {
        static constexpr int MAX_XOR = 1024;

        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<bitset<MAX_XOR>> reachable_xor_values(COLS);
        reachable_xor_values[0][0] = 1;   // Bit 0 in this column is reachable(i.e. 1)
        // reachable_xor_values[0] = 0x1; // bitset=0x1 means only bit 0 is reachable

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                /* Get XOR values reachable from ABOVE or from the LEFT */
                bitset<1024> previous_xor_values;

                auto& above_xor_values = reachable_xor_values[col];
              //auto& left_xor_values  = reachable_xor_values[col-1];

                if (col > 0)
                    previous_xor_values = above_xor_values | reachable_xor_values[col - 1];
                else
                    previous_xor_values = above_xor_values;

                /* Clear previous states before storing the new ones */
                reachable_xor_values[col].reset();

                /* Append the current grid value to every reachable XOR */
                for (int xor_value = 0; xor_value < MAX_XOR; xor_value++)
                {
                    if (previous_xor_values[xor_value])
                        reachable_xor_values[col][xor_value ^ grid[row][col]] = 1;
                }
            }
        }

        /* Find the minimum reachable XOR at the bottom-right cell */
        for (int xor_value = 0; xor_value < MAX_XOR; xor_value++)
        {
            if (reachable_xor_values[COLS - 1][xor_value])
                return xor_value;
        }

        return -1;
    }
};
