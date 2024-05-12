#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ======================================
    2373) Largest Local Values in a Matrix
    ======================================

    ============
    Description:
    ============

    You are given an n x n integer matrix grid.

    Generate an integer matrix maxLocal of size (n - 2) x (n - 2) such that:

        maxLocal[i][j] is equal to the largest value of the 3 x 3 matrix in
        grid centered around row i + 1 and column j + 1.

    In other words, we want to find the largest value in every contiguous 3 x 3
    matrix in grid.

    Return the generated matrix.

    ======================================================================
    FUNCTION: vector<vector<int>> largestLocal(vector<vector<int>>& grid);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+-----+              +-----+-----+
    |  9  |  9  |  8  |  1  |              |  9  |  9  |
    +-----+-----+-----+-----+              +-----+-----+
    |  5  |  6  |  2  |  6  |              |  8  |  6  |
    +-----+-----+-----+-----+              +-----+-----+
    |  8  |  2  |  6  |  4  |
    +-----+-----+-----+-----+
    |  6  |  2  |  2  |  2  |
    +-----+-----+-----+-----+

    Input: grid = [[9,9,8,1],[5,6,2,6],[8,2,6,4],[6,2,2,2]]
    Output: [[9,9],[8,6]]
    Explanation: The diagram above shows the original matrix and the generated
                  matrix.
    Notice that each value in the generated matrix corresponds to the largest
    value of a contiguous 3 x 3 matrix in grid.


    --- Example 2 ---
    +-----+-----+-----+-----+-----+
    |  1  |  1  |  1  |  1  |  1  |
    +-----+-----+-----+-----+-----+          +-----+-----+-----+
    |  1  |  1  |  1  |  1  |  1  |          |  2  |  2  |  2  |
    +-----+-----+-----+-----+-----+          +-----+-----+-----+
    |  1  |  1  |  2  |  1  |  1  |          |  2  |  2  |  2  |
    +-----+-----+-----+-----+-----+          +-----+-----+-----+
    |  1  |  1  |  1  |  1  |  1  |          |  2  |  2  |  2  |
    +-----+-----+-----+-----+-----+          +-----+-----+-----+
    |  1  |  1  |  1  |  1  |  1  |
    +-----+-----+-----+-----+-----+

    Input: grid = [[1,1,1,1,1],[1,1,1,1,1],[1,1,2,1,1],[1,1,1,1,1],[1,1,1,1,1]]
    Output: [[2,2,2],[2,2,2],[2,2,2]]
    Explanation: Notice that the 2 is contained within every contiguous 3 x 3
                 matrix in grid


    *** Constraints ***
    n == grid.length == grid[i].length
    3 <= n <= 100
    1 <= grid[i][j] <= 100

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 53.93% */
/* Space Beats: 81.97% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    std::vector<std::vector<int>> largestLocal(std::vector<std::vector<int>>& grid)
    {
        const int N = grid.size();
        std::vector<std::vector<int>> result(N - 2, std::vector<int>(N - 2));

        for(int i = 1; i < N-1; i++)
        {
            for(int j = 1; j < N-1; j++)
            {
                int tmp = 0;

                for(int k = i-1; k <= i+1; k++)
                {
                    for(int m = j-1; m<= j+1; m++)
                        tmp = std::max(tmp, grid[k][m]);
                }

                result[i-1][j-1] = tmp;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Use a sized 3 extra array maxC to compute the max for 3x1 submatrices. In
    each row, moving j & compute the next maxC[(j+1)%3], i.e. sliding window,
    computational amount is reduced.

*/

/* Time  Beats: 99.54% */
/* Space Beats: 53.31% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1) */
class Solution_Sliding_Window {
public:
    std::vector<std::vector<int>> largestLocal(std::vector<std::vector<int>>& grid)
    {
        const int N = grid.size();
        int max_columns[3] = {0};

        for(int i = 1; i < N-1; i++)
        {
            for(int j = 1; j < N-1; j++)
            {
                if (j == 1)
                {
                    max_columns[0] = std::max( {grid[i-1][0], grid[i][0], grid[i+1][0]} );
                    max_columns[1] = std::max( {grid[i-1][1], grid[i][1], grid[i+1][1]} );
                }

                max_columns[(j+1) % 3] = std::max( {grid[i-1][j+1], grid[i][j+1], grid[i+1][j+1]} );

                grid[i-1][j-1] = std::max( {max_columns[0], max_columns[1], max_columns[2]} );
            }
            grid[i-1].resize(N-2);

        }
        grid.resize(N-2);

        return grid;
    }
};
