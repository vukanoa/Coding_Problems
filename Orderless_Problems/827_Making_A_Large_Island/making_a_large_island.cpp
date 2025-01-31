/*
    ============
    === HARD ===
    ============

    ===========================
    827) Making A Large Island
    ===========================

    ============
    Description:
    ============

    You are given an n x n binary matrix grid. You are allowed to change at most
    one 0 to be 1.

    Return the size of the largest island in grid after applying this operation

    An island is a 4-directionally connected group of 1s.

    =======================================================
    FUNCTION: int largestIsland(vector<vector<int>>& grid);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,0],[0,1]]
    Output: 3
    Explanation: Change one 0 to 1 and connect two 1s, then we get an island
                 with area = 3.

    --- Example 2 ---
    Input: grid = [[1,1],[1,0]]
    Output: 4
    Explanation: Change the 0 to 1 and make the island bigger, only one island
                 with area = 4.

    --- Example 3 ---
    Input: grid = [[1,1],[1,1]]
    Output: 4
    Explanation: Can't change any 0 to 1, only one island with area = 4.


    *** Constraints ***
    n == grid.length
    n == grid[i].length
    1 <= n <= 500
    grid[i][j] is either 0 or 1.

*/

#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 17.25% */
/* Space Beats:  8.14% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    int largestIsland(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int result = 0;

        vector<vector<int>> which_island(ROWS, vector<int>(COLS, 0));

        vector<vector<bool>> visited_1 = vector(ROWS, vector<bool>(COLS, false));
        vector<vector<bool>> visited_2 = vector(ROWS, vector<bool>(COLS, false));

        int island = 1;
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 1 && !visited_1[row][col])
                {
                    int size_of_island = dfs(grid, row, col, visited_1);
                    dfs_fill_islands(grid, row, col, visited_2, size_of_island, which_island, island);
                    island++;
                }
            }
        }

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 0)
                {
                    int size = 1;
                    unordered_set<int> uset;

                    if (row-1 >= 0)
                    {
                        size += grid[row-1][col];
                        uset.insert(which_island[row-1][col]);
                    }

                    if (row+1 < ROWS && !uset.count(which_island[row+1][col]))
                    {
                        size += grid[row+1][col];
                        uset.insert(which_island[row+1][col]);
                    }

                    if (col-1 >= 0 && !uset.count(which_island[row][col-1]))
                    {
                        size += grid[row][col-1];
                        uset.insert(which_island[row][col-1]);
                    }

                    if (col+1 < COLS && !uset.count(which_island[row][col+1]))
                    {
                        size += grid[row][col+1];
                        uset.insert(which_island[row][col+1]);
                    }

                    result = max(result, size);
                }
            }
        }

        return result == 0 ? ROWS * COLS : result;
    }

private:
    int dfs(vector<vector<int>>& grid, int row, int col, vector<vector<bool>>& visited)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row < 0 || col < 0 || row == ROWS || col == COLS)
            return 0;

        if (visited[row][col] || grid[row][col] == 0)
            return 0;

        visited[row][col] = true;

        int up    = dfs(grid, row-1, col  , visited);
        int down  = dfs(grid, row+1, col  , visited);
        int left  = dfs(grid, row  , col-1, visited);
        int right = dfs(grid, row  , col+1, visited);

        return 1 + up + down + left + right;
    }

    void dfs_fill_islands(vector<vector<int>>& grid, int row, int col, vector<vector<bool>>& visited, int size_of_island, vector<vector<int>>& which_island, int island)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row < 0 || col < 0 || row == ROWS || col == COLS)
            return;

        if (visited[row][col] || grid[row][col] == 0)
            return;

        visited[row][col] = true;
        which_island[row][col] = island;
        grid[row][col] = size_of_island;

        dfs_fill_islands(grid, row-1, col  , visited, size_of_island, which_island, island);
        dfs_fill_islands(grid, row+1, col  , visited, size_of_island, which_island, island);
        dfs_fill_islands(grid, row  , col-1, visited, size_of_island, which_island, island);
        dfs_fill_islands(grid, row  , col+1, visited, size_of_island, which_island, island);
    }
};
