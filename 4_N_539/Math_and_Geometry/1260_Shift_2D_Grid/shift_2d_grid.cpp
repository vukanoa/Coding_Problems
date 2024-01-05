#include <iostream>
#include <vector>
#include <algorithm> // For lambda functions

/*
    ============
    === EASY ===
    ============

    ===========================
    1260) Shift 2D Grid
    ===========================

    ============
    Description:
    ============

    Given a 2D grid of size m x n and an integer k. You need to shift the grid
    k times.

    In one shift operation:

        Element at grid[i][j] moves to grid[i][j + 1].
        Element at grid[i][n - 1] moves to grid[i + 1][0].
        Element at grid[m - 1][n - 1] moves to grid[0][0].

    Return the 2D grid after applying shift operation k times.

    ==========================================================================
    FUNCTION: vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+       +-----+-----+-----+
    |  1  |  2  |  3  |       |  9  |  1  |  2  |
    +-----+-----+-----+       +-----+-----+-----+
    |  4  |  5  |  6  |  -->  |  3  |  4  |  5  |
    +-----+-----+-----+       +-----+-----+-----+
    |  7  |  8  |  9  |       |  6  |  7  |  8  |
    +-----+-----+-----+       +-----+-----+-----+
    Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
    Output: [[9,1,2],[3,4,5],[6,7,8]]



    --- Example 2 ---
    +-----+-----+-----+-----+       +-----+-----+-----+-----+
    |  3  |  8  |  1  |  9  |       | 13  |  3  |  8  |  1  |
    +-----+-----+-----+-----+       +-----+-----+-----+-----+
    | 19  |  7  |  2  |  5  |       |  9  | 19  |  7  |  2  |
    +-----+-----+-----+-----+  -->  +-----+-----+-----+-----+  -->
    |  4  |  6  | 11  | 10  |       |  5  |  4  |  6  | 11  |
    +-----+-----+-----+-----+       +-----+-----+-----+-----+
    | 12  |  0  | 21  | 13  |       | 10  | 12  |  0  | 21  |
    +-----+-----+-----+-----+       +-----+-----+-----+-----+

    +-----+-----+-----+-----+       +-----+-----+-----+-----+
    | 21  | 13  |  3  |  8  |       |  0  | 21  | 13  |  3  |
    +-----+-----+-----+-----+       +-----+-----+-----+-----+
    |  1  |  9  | 19  |  7  |       |  8  |  1  |  9  | 19  |
    +-----+-----+-----+-----+  -->  +-----+-----+-----+-----+ -->
    |  2  |  5  |  4  |  6  |       |  7  |  2  |  5  |  4  |
    +-----+-----+-----+-----+       +-----+-----+-----+-----+
    | 11  | 10  | 12  |  0  |       |  6  | 11  | 10  | 12  |
    +-----+-----+-----+-----+       +-----+-----+-----+-----+

    +-----+-----+-----+-----+
    | 12  |  0  | 21  | 13  |
    +-----+-----+-----+-----+
    |  3  |  8  |  1  |  9  |
    +-----+-----+-----+-----+
    | 19  |  7  |  2  |  5  |
    +-----+-----+-----+-----+
    |  4  |  6  | 11  | 10  |
    +-----+-----+-----+-----+

    Input: grid = [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]], k = 4
    Output: [[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]


    --- Example 3 ---
    Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 9
    Output: [[1,2,3],[4,5,6],[7,8,9]]


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m <= 50
    1 <= n <= 50
    -1000 <= grid[i][j] <= 1000
    0 <= k <= 100

*/

/*
    ------------
    --- IDEA ---
    ------------

    All you have to do is to "figure out" how to shift the grid by one and then
    write that function and call it k times.

    I've implemented it by having an additional vector called "first_in_row"
    which would store the rightmost element which is "shifted out" at each
    row shifting.

    However, we can't put that "shifted out" element in the same i-th row,
    since once we get to the very last element, we'll realize that we have to
    put it all the way up, at the 0-th row, and not in the ROWS-1 row.

    Hence, this formula:
        first_in_row[(i + 1) % ROWS] = grid[i][COLS-1];

    (i + 1)  % ROWS will result in every i-th row, except the very last one, to
    be put in (i + 1)th position in "first_by_row". However, the very last one
    will be put in 0-th row, but since we don't want to write an if statement
    we can just use this formula that mods accordingly.

    Imagine that ROWS = 3;

    Last element in the 0-th row must go to the first element in (0 + 1)th row.
    Last element in the 1-st row must go to the first element in (1 + 1)th row.
    Last element in the 2-nd row must go to the first element in (2 + 1)th row,
    however since (2 + 1) = 3, that means we would get an "out of bounds" error
    and therefore we can realize that we need to mod it with the number of rows
    in order to get every index at the right place.

    (2 + 1) % ROWS ==> (3) % 3 = 0

    That's the only "tricky" part for this problem.

*/

/* Time  Beats: 23.65% */
/* Space Beats: 20.37% */

/* Time  Complexity: O(k * ROWS * COLS) */
/* Space Complexity: O(ROWS) */
class Solution {
public:
    std::vector<std::vector<int>> shiftGrid(std::vector<sd::vector<int>>& grid, int k)
    {
        for (int i = 0; i < k; i++)
            shift_grid_by_one(grid);

        return grid;
    }

private:
    void shift_grid_by_one(std::vector<std::vector<int>>& grid)
    {
        int ROWS = grid.size();
        int COLS = grid[0].size();

        std::vector<int> first_in_row(ROWS, 0);

        for (int i = 0; i < ROWS; i++)
        {
            first_in_row[(i + 1) % ROWS] = grid[i][COLS-1];

            for (int j = COLS-1; j > 0; j--)
                grid[i][j] = grid[i][j-1];
        }

        for (int i = 0; i < ROWS; i++)
            grid[i][0] = first_in_row[i];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 92.74% */
/* Space Beats: 51.99% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Neat {
public:
    std::vector<std::vector<int>> shiftGrid(std::vector<std::vector<int>>& grid, int k)
    {
        int ROWS = grid.size();
        int COLS = grid[0].size();

        std::function<int(int, int)> pos_2D_to_index_1D;
        pos_2D_to_index_1D = [&](int row, int col) -> int
                                {
                                    return row * COLS + col;
                                };

        std::function<std::pair<int, int>(int)> index_1D_to_pos_2D;
        index_1D_to_pos_2D = [&](int idx) -> std::pair<int, int>
                                {
                                    return {idx / COLS, idx % COLS};
                                };

        std::vector<std::vector<int>> result(ROWS, std::vector(COLS, 0));
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                int idx = (pos_2D_to_index_1D(row, col) + k) % (ROWS * COLS);

                std::pair<int, int> pair = index_1D_to_pos_2D(idx);
                int new_row = pair.first;
                int new_col = pair.second;

                result[new_row][new_col] = grid[row][col];
            }
        }

        return result;
    }
};
