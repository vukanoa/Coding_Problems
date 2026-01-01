#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    221) Maximal Square
    ===========================

    ============
    Description:
    ============

    Given an m x n binary matrix filled with 0's and 1's, find the largest
    square containing only 1's and return its area.

    ==========================================================
    FUNCTION: int maximalSquare(vector<vector<char>>& matrix);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+-----+-----+
    |  1  |  0  |  1  |  0  |  0  |
    +-----+-----+-----+-----+-----+
    |  1  |  0  |  1  |  1  |  1  |
    +-----+-----+-----+-----+-----+
    |  1  |  1  |  1  |  1  |  1  |
    +-----+-----+-----+-----+-----+
    |  1  |  0  |  0  |  1  |  0  |
    +-----+-----+-----+-----+-----+

    Input: matrix =
    [["1","0","1","0","0"],
     ["1","0","1","1","1"],
     ["1","1","1","1","1"],
     ["1","0","0","1","0"]]
    Output: 4


    --- Example 2 ---
    +-----+-----+
    |  0  |  1  |
    +-----+-----+
    |  1  |  0  |
    +-----+-----+
    Input: matrix = [["0","1"],["1","0"]]
    Output: 1


    --- Example 3 ---
    Input: matrix = [["0"]]
    Output: 0


    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 300
    matrix[i][j] is '0' or '1'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 29.28% */
/* Space Beats: 11.12% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    int maximalSquare(std::vector<std::vector<char>> matrix)
    {
        int ROWS = matrix.size();
        int COLS = matrix[0].size();

        std::vector<std::vector<int>> cache_square_len(ROWS, std::vector(COLS, -1));

        std::function<int(int, int)> helper;

        /* LAMBDA */
        helper = [&](int r, int c) -> int
        {
            if (r >= ROWS || c >= COLS)
                return 0;

            if (cache_square_len[r][c] == -1)
            {
                int down     = helper(r+1, c  );
                int right    = helper(r  , c+1);
                int diagonal = helper(r+1, c+1);

                cache_square_len[r][c] = 0;

                if (matrix[r][c] == '1')
                    cache_square_len[r][c] = 1 + std::min( {down, right, diagonal} );
            }

            return cache_square_len[r][c];
        };

        helper(0, 0);

        int max = INT_MIN;
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
                max = std::max(max, cache_square_len[i][j]);
        }

        return max * max;
    }
};
