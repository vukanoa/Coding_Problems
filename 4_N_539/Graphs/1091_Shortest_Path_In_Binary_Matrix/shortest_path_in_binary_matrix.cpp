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

/* Time  Beats: 95.40% */
/* Space Beats: 91.54% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid)
    {
        if (grid[0][0] != 0)
            return -1;
        else if (grid.size() == 1)
            return 1;

        const int N = grid.size();

        std::queue<std::pair<int,int>> queue;
        grid[0][0] = 2;
        queue.push({0,0});

        /* Clockwise */
        std::vector<std::pair<int, int>> directions = {{-1, 0},  // Up
                                                       {-1, 1},  // Up-Right
                                                       { 0, 1},  // Right
                                                       { 1, 1},  // Down-Right
                                                       { 1, 0},  // Down
                                                       { 1,-1},  // Down-Left
                                                       { 0,-1},  // Left
                                                       {-1,-1}}; // Up-Left

        /* BFS */
        int path_len = 1;
        while (!queue.empty())
        {
            int size = queue.size();
            path_len++;

            for (int i = 0; i < size; i++)
            {
                std::pair<int, int> field = queue.front();
                queue.pop();

                for (const auto& dir : directions)
                {
                    int row = field.first  + dir.first;
                    int col = field.second + dir.second;

                    if (row < 0 || col < 0 || row == N || col == N || grid[row][col] != 0)
                        continue;
                    else if (row == N-1 && col == N-1)
                        return path_len;

                    grid[row][col] = 2;
                    queue.push({row, col});
                }
            }
        }

        return -1;
    }
};
