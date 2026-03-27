/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    200) Number of Islands
    ===========================

    ============
    Description:
    ============

    Given an m x n 2D binary grid "grid" which represents a map of '1's(land)
    and '0's(water), return the number of islands.

    An island is surrounded by water and is formed by connecting adjacent lands
    horizontally or vertically. You may assume all four edges of the grid are
    all surrounded by water.

    =====================================================
    FUNCTION: int numIslands(vector<vector<char>>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  grid = [
        ["1", "1", "1", "1", "0"],
        ["1", "1", "0", "1", "0"],
        ["1", "1", "0", "0", "0"],
        ["0", "0", "0", "0", "0"],
        ]
    Output: 1

    --- Example 2 ---
    Input:  grid = [
        ["1", "1", "0", "0", "0"],
        ["1", "1", "0", "0", "0"],
        ["0", "0", "1", "0", "0"],
        ["0", "0", "0", "1", "1"],
        ]
    Output: 3

    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    grid[i][j] is '0' or '1'

*/

#include <vector>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    A simple self-explanatory DFS.

*/

/* Time  Beats: 98.84% */
/* Space Beats: 85.21% */

/* Time  Complexity:
    O(n) or O(row * columns) or O(V) 'V' for Vertices in Graph
*/
/* Space Complexity: O(n)
    Recursion can go up to N levels deep since we can have all 1's in "grid".
*/
class Solution_DFS {
public:
    int numIslands(vector<vector<char>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int islands = 0;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == '1')
                {
                    dfs(row, col, grid);
                    islands++;
                }
            }
        }

        /* Restore original Grid */
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == '#')
                    grid[row][col] = '1';
            }
        }

        return islands;
    }

private:
    void dfs(int row, int col, vector<vector<char>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row < 0 || col < 0 || row >= ROWS || col >= COLS)
            return;

        if (grid[row][col] != '1')
            return;

        grid[row][col] = '#';

        /* Signing Cross */
        dfs(row-1, col  , grid); // Up
        dfs(row+1, col  , grid); // Down
        dfs(row  , col-1, grid); // Left
        dfs(row  , col+1, grid); // Right
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 91.73% */
/* Space Beats: 26.98% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_BFS{
public:
    int numIslands(vector<vector<char>>& grid)
    {
        int ROWS = grid.size();
        int COLS = grid[0].size();

        /* Signing Cross */
        // (Up, Down, Left, Right)
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int islands = 0;

        /* Lambda */
        auto inside = [&](int i, int j)
        {
            return i >= 0 && j >= 0 && i < ROWS && j < COLS;
        };

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (inside(i, j) && grid[i][j] == '1')
                {
                    islands++;
                    /* If we are not allowed to modify original given "grid",
                       then use vector<vector<bool>> visisted.
                    */
                    grid[i][j] = 'x'; // Mark as processed

                    /* BFS */
                    queue<pair<int, int>> queue;
                    queue.push({i, j});

                    while (!queue.empty())
                    {
                        pair<int, int> curr = queue.front();
                        queue.pop();

                        for (const pair<int, int>& dir : directions)
                        {
                            int row = curr.first  + dir.first;
                            int col = curr.second + dir.second;

                            if (inside(row, col) && grid[row][col] == '1')
                            {
                                grid[row][col] = 'x'; // Mark as processed
                                queue.push({row, col});
                            }
                        }
                    }
                }
            }
        }

        return islands;
    }
};
