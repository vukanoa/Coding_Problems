#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    1091) Shortest Path in Binary Matrix
    ====================================

    ============
    Description:
    ============

    Given an n x n binary matrix grid, return the length of the shortest clear
    path in the matrix. If there is no clear path, return -1.

    A clear path in a binary matrix is a path from the top-left cell (i.e., (0,
    0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

        All the visited cells of the path are 0.
        All the adjacent cells of the path are 8-directionally connected (i.e.,
        they are different and they share an edge or a corner).

    The length of a clear path is the number of visited cells of this path.

    ==================================================================
    FUNCTION: int shortestPathBinaryMatrix(vector<vector<int>>& grid);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+   +-----+-----+
    |  0  |  1  |   |  0 \|  1  |
    +-----+-----+   +-----\-----+
    |  1  |  0  |   |  1  |\ 0  |
    +-----+-----+   +-----+-----+

    Input: grid = [[0,1],[1,0]]
    Output: 2


    --- Example 2 ---
    +-----+-----+-----+     +-----+-----+-----+
    |  0  |  0  |  0  |     |  0 -|- 0 \|  0  |
    +-----+-----+-----+     +-----+-----\-----+
    |  1  |  1  |  0  |     |  1  |  1  |\ 0  |
    +-----+-----+-----+     +-----+-----+-|---+
    |  1  |  1  |  0  |     |  1  |  1  |  0  |
    +-----+-----+-----+     +-----+-----+-----+
    Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
    Output: 4


    --- Example 3 ---
    +-----+-----+-----+
    |  1  |  0  |  0  |
    +-----+-----+-----+
    |  1  |  1  |  0  |
    +-----+-----+-----+
    |  1  |  1  |  0  |
    +-----+-----+-----+
    Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
    Output: -1


    *** Constraints ***
    n == grid.length
    n == grid[i].length
    1 <= n <= 100
    grid[i][j] is 0 or 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    You CANNOT solve it using DFS!

    LeetCode will give you a TLE(Time Limit Exceeded).

*/

class Solution_TLE {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid)
    {
        if (grid[0][0] != 0)
            return -1;

        int result = INT_MAX;
        dfs(grid, 0, 0, 0, result);

        return result == INT_MAX ? -1 : result;
    }

private:
    void dfs(vector<vector<int>>& grid, int i, int j, int path, int& result)
    {
        const int n = grid.size();

        if (i < 0 || j < 0 || i == n || j == n || grid[i][j] != 0)
            return;

        path++;

        if (i == n-1 && j == n-1)
        {
            result = std::min(result, path);
            return;
        }

        grid[i][j] = 2;

        /* Clockwise */
        dfs(grid, i-1, j  , path, result); // Up
        dfs(grid, i-1, j+1, path, result); // Up-Right
        dfs(grid, i  , j+1, path, result); // Right
        dfs(grid, i+1, j+1, path, result); // Down-Right
        dfs(grid, i+1, j  , path, result); // Down
        dfs(grid, i+1, j-1, path, result); // Down-Left
        dfs(grid, i  , j-1, path, result); // Left
        dfs(grid, i-1, j-1, path, result); // Up-Left

        grid[i][j] = 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    You MUST do it using BFS!
    That's usually the way you find "minimum path" to the destination in these
    kind of Graph problems.

*/

/* Time  Beats: 97.32% */
/* Space Beats: 86.77% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution_BFS {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid)
    {
        const int n = grid.size();

        if (grid[0][0] != 0 || grid[n-1][n-1] != 0)
            return -1;
        else if (n == 1)
            return grid[0][0] == 0; // Or grid[n-1][n-1], it's the same thing

        int result = INT_MAX;

        std::queue<std::pair<int, int>> queue;
        queue.push( {0, 0} );
        grid[0][0] = 2;

        std::vector<std::pair<int, int>> directions = {{-1,  0},   // Up
                                                       {-1, +1},   // Up-Right
                                                       { 0, +1},   // Right
                                                       {+1, +1},   // Down-Right
                                                       {+1,  0},   // Down
                                                       {+1, -1},   // Down-Left
                                                       { 0, -1},   // Left
                                                       {-1, -1}};  // Up-Left
        int path = 0;
        while (!queue.empty())
        {
            path++;
            int size = queue.size();

            while (size--)
            {
                int i = queue.front().first;
                int j = queue.front().second;
                queue.pop();

                for (auto& dir : directions)
                {
                    int row = i + dir.first;
                    int col = j + dir.second;

                    if (row < 0 || col < 0 || row == n || col == n)
                        continue;

                    if (row == n-1 && col == n-1 && grid[row][col] == 0)
                        return path+1;

                    if (grid[row][col] == 0)
                    {
                        grid[row][col] = 2;
                        queue.push( {row, col} );
                    }
                }
            }
        }

        return -1;
    }
};
