/*
    ============
    === HARD ===
    ============

    ======================================
    329) Longest Increasing Path In Matrix
    ======================================

    ============
    Description:
    ============

    Given an m x n integers matrix, return the length of the longest increasing
    path in matrix.

    From each cell, you can either move in four directions: left, right, up, or
    down. You may not move diagonally or move outside the boundary (i.e.,
    wrap-around is not allowed).

    ===============================
    FUNCTION:
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matrix = [[9,9,4],
                     [6,6,8],
                     [2,1,1]]
    Output: 4
    Explanation: The longest increasing path is [1, 2, 6, 9].


    --- Example 2 ---
    Input: matrix = [[3,4,5],
                     [3,2,6],
                     [2,2,1]]
    Output: 4
    Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally
                 is not allowed.


    --- Example 3 ---
    Input: matrix = [[1]]
    Output: 1


    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 200
    0 <= matrix[i][j] <= 2^31 - 1

*/

#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Same as above, the only difference is that the above Solution is written
    more explicitly.

    For example it has both visited and dp, whereas here we only has dp, but if
    dp[i][j] = -1, it measn that it's NOT visited.

    It's easier to read the above Solution.

*/

/* Time  Beats: 26.73% */
/* Space Beats: 31.87% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Concise {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix)
    {
        int ROWS = matrix.size();
        int COLS = matrix[0].size();

        vector<vector<int>> dp(ROWS, vector<int>(COLS, -1));

        function<int(int, int, int)> dfs = [&](int r, int c, int prev)
        {
            if (r < 0 || r == ROWS || c < 0 || c == COLS || matrix[r][c] <= prev)
                return 0;

            if (dp[r][c] != -1)
                return dp[r][c];

            int result = 1;
            result = max(result, 1 + dfs(r+1, c  , matrix[r][c]));
            result = max(result, 1 + dfs(r-1, c  , matrix[r][c]));
            result = max(result, 1 + dfs(r  , c+1, matrix[r][c]));
            result = max(result, 1 + dfs(r  , c-1, matrix[r][c]));

            dp[r][c] = result;

            return result;
        };

        int longest_path = 0;
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLS; c++)
            {
                longest_path = max(longest_path, dfs(r, c, -1));
            }
        }

        return longest_path;
    }
};
