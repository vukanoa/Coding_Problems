/*
    ============
    === HARD ===
    ============

    =========================================
    2328) Number of Inreasing Paths in a Grid
    =========================================

    ============
    Description:
    ============

    You are given an m x n integer matrix grid, where you can move from a cell
    to any adjacent cell in all 4 directions.

    Return the number of strictly increasing paths in the grid such that you
    can start from any cell and end at any cell. Since the answer may be very
    large, return it modulo 109 + 7.

    Two paths are considered different if they do not have exactly the same
    sequence of visited cells.

    ====================================================
    FUNCTION: int countPaths(vector<vector<int>>& grid);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,1],[3,4]]
    Output: 8
    Explanation: The strictly increasing paths are:
    - Paths with length 1: [1], [1], [3], [4].
    - Paths with length 2: [1 -> 3], [1 -> 4], [3 -> 4].
    - Paths with length 3: [1 -> 3 -> 4].
    The total number of paths is 4 + 3 + 1 = 8.

    --- Example 2 ---
    Input: grid = [[1],[2]]
    Output: 3
    Explanation: The strictly increasing paths are:
    - Paths with length 1: [1], [2].
    - Paths with length 2: [1 -> 2].
    The total number of paths is 2 + 1 = 3.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 1000
    1 <= m * n <= 10^5
    1 <= grid[i][j] <= 10^5

*/

#include <cstring>
#include <utility>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Fairly easy Memoization for a HARD problem.

    If you've done Memoization before, this one shouldn't be much of a problem.

*/

/* Time  Beats: 46.70% */
/* Space Beats: 49.58% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
private:
    const int MOD = 1e9 + 7;

    static constexpr int MAX_ROWS = 1000;
    static constexpr int MAX_COLS = 1000;

    long long memo[MAX_ROWS + 1][MAX_COLS + 1];

    /* Signing Cross */
    vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

public:
    int countPaths(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        long result = 0;

        /* Allocate space on the Stack */
        memset(memo, -1, sizeof(memo));

        // For each cell as a starting point calculate the number of increasing
        // paths it can contribute.
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                result = (result + solve(row, col, grid)) % MOD;
            }
        }

        return result;
    }

private:
    long long solve(int row, int col, vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (memo[row][col] != -1) // Return the cached result if they exist.
            return memo[row][col];


        long long result = 1; // Contribution of curr cell as an increasing seq

        for (const auto& dir : directions)
        {
            int new_row = row + dir.first;
            int new_col = col + dir.second;

            // Out-of-Bounds?
            if (new_row < 0 || new_col < 0 || new_row == ROWS || new_col == COLS)
                continue;

            // Next cell isn't STRICTLY increasing?
            if (grid[new_row][new_col] <= grid[row][col])
                continue;

            result = (result + solve(new_row, new_col, grid)) % MOD;
        }

        return memo[row][col] = result;
    }
};
