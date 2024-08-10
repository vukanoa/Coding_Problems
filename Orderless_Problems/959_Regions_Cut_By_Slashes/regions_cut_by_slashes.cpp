#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    959) Regions Cut By Slashes
    ===========================

    ============
    Description:
    ============

    An n x n grid is composed of 1 x 1 squares where each 1 x 1 square consists
    of a '/', '\', or blank space ' '. These characters divide the square into
    contiguous regions.

    Given the grid grid represented as a string array, return the number of
    regions.

    Note that backslash characters are escaped, so a '\' is represented as
    '\\'.

    =====================================================
    FUNCTION: int regionsBySlashes(vector<string>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [" /","/ "]
    Output: 2

    --- Example 2 ---
    Input: grid = [" /","  "]
    Output: 1

    --- Example 3 ---
    Input: grid = ["/\\","\\/"]
    Output: 5
    Explanation: Recall that because \ characters are escaped, "\\/" refers to
                 \/, and "/\\" refers to /\.


    *** Constraints ***
    n == grid.length == grid[i].length
    1 <= n <= 30
    grid[i][j] is either '/', '\', or ' '.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 32.52% */
/* Space Beats: 28.73% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    /* Signing Cross */
    std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    int regionsBySlashes(vector<string>& grid)
    {
        const int n = grid.size();
        vector<vector<int>> mat(n*3, vector<int>(n*3, 0));

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                int row = i*3;
                int col = j*3;

                if(grid[i][j] != ' ' && grid[i][j] == '\\')
                {
                    mat[row  ][col  ] = 1;
                    mat[row+1][col+1] = 1;
                    mat[row+2][col+2] = 1;
                }
                else if (grid[i][j] != ' ' && grid[i][j] == '/')
                {
                    mat[row  ][col+2] = 1;
                    mat[row+1][col+1] = 1;
                    mat[row+2][col  ] = 1;
                }
            }
        }

        int result = 0;

        for (int i = 0; i < n*3; i++)
        {
            for (int j = 0; j < n*3; j++)
            {
                if (mat[i][j] == 0)
                {
                    dfs(mat, i, j, n*3);
                    result++;
                }
            }
        }

        return result;
    }

private:
    void dfs(vector<vector<int>>& mat, int row, int col, int n)
    {
        mat[row][col] = 1;

        for (const auto& dir : directions)
        {
            int new_row = row + dir.first;
            int new_col = col + dir.second;

            if (new_row >= 0 && new_row < n && new_col >= 0 && new_col < n && mat[new_row][new_col] == 0)
                dfs(mat, new_row, new_col, n);
        }
    }
};
