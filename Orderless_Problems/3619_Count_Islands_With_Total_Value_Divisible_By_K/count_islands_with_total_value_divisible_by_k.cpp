/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    3619) Count Islands With Total Value Divisible by K
    ===================================================

    ============
    Description:
    ============

    You are given an m x n matrix grid and a positive integer k. An island is a
    group of positive integers (representing land) that are 4-directionally
    connected (horizontally or vertically).

    The total value of an island is the sum of the values of all cells in the
    island.

    Return the number of islands with a total value divisible by k.

    =============================================================
    FUNCTION: int countIslands(vector<vector<int>>& grid, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[0,2,1,0,0],[0,5,0,0,5],[0,0,1,0,0],[0,1,4,7,0],[0,2,0,0,8]], k = 5
    Output: 2
    Explanation: The grid contains four islands. The islands highlighted in
                 blue have a total value that is divisible by 5, while the
                 islands highlighted in red do not.

    --- Example 2 ---
    Input: grid = [[3,0,3,0], [0,3,0,3], [3,0,3,0]], k = 3
    Output: 6
    Explanation: The grid contains six islands, each with a total value that is
                 divisible by 3.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 1000
    1 <= m * n <= 10^5
    0 <= grid[i][j] <= 10^6
    1 <= k <= 10^6

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic "Count Islands" variation. Fundamental "DFS on a grid" problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int result = 0;

        vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if ( ! visited[row][col] && grid[row][col] > 0)
                {
                    unsigned long long sum = 0LL;
                    dfs(row, col, grid, visited, sum);

                    if (sum > 0LL && sum % k == 0)
                        result++;
                }
            }
        }

        return result;
    }

private:
    void dfs(int row, int col, vector<vector<int>>& grid, vector<vector<bool>>& visited, unsigned long long& sum)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row < 0 || col < 0 || row >= ROWS || col >= COLS || grid[row][col] == 0)
            return;

        if (visited[row][col])
            return;

        visited[row][col] = true; // Mark
        sum += grid[row][col];

        dfs(row - 1, col   , grid, visited, sum);
        dfs(row + 1, col   , grid, visited, sum);
        dfs(row    , col -1, grid, visited, sum);
        dfs(row    , col +1, grid, visited, sum);
    }
};
