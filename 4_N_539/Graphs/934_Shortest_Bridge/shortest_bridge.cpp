#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    934) Shortest Bridge
    ===========================

    ============
    Description:
    ============

    You are given an n x n binary matrix grid where 1 represents land and 0
    represents water.

    An island is a 4-directionally connected group of 1's not connected to any
    other 1's. There are exactly two islands in grid.

    You may change 0's to 1's to connect the two islands to form one island.

    Return the smallest number of 0's you must flip to connect the two islands.

    =======================================================
    FUNCTION: int shortestBridge(vector<vector<int>& grid);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[0,1],
                   [1,0]]
    Output: 1

    --- Example 2 ---
    Input: grid = [[0,1,0],
                   [0,0,0],
                   [0,0,1]]
    Output: 2

    --- Example 3 ---
    Input: grid = [[1,1,1,1,1],
                   [1,0,0,0,1],
                   [1,0,1,0,1],
                   [1,0,0,0,1],
                   [1,1,1,1,1]]


    *** Constraints ***
    n == grid.length == grid[i].length
    2 <= n <= 100
    grid[i][j] is either 0 or 1.
    There are exactly two islands in grid.

*/

/*
    ------------
    --- IDEA ---
    ------------

    DFS * BFS.

*/

/* Time  Beats: 87.49% */
/* Space Beats: 56.49% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    int shortestBridge(std::vector<std::vector<int>>& grid)
    {
        const int N = grid.size();

        std::queue<std::pair<int, int>> queue;
        std::vector<std::vector<bool>> visited(N, std::vector(N, false));

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (grid[i][j] == 1)
                {
                    dfs(grid, i, j, queue, visited);

                    // Find only the first island
                    i = N; // This is done to break the outer loop as well
                    break;
                }
            }
        }

        std::vector<std::pair<int, int>> directions = {{-1,0}, {1, 0}, {0, -1}, {0, 1}};

        int bridge = -1;
        while (!queue.empty())
        {
            bridge++;
            int size = queue.size();

            for (int x = 0; x < size; x++)
            {
                std::pair<int, int> pair = queue.front();
                queue.pop();

                int row = pair.first;
                int col = pair.second;

                for (auto& dir : directions)
                {
                    int i = dir.first;
                    int j = dir.second;

                    if (row+i < 0 || col+j < 0 || row+i == N || col+j == N)
                        continue;

                    if (visited[row + i][col + j]) //  <---------------------------------------------------------------
                        continue;                                                                                //   |
                                                                                                                 //   |
                                                                                                                 //   |
                    if (grid[row + i][col + j] == 1) // && NOT visited[i][j], but it's implicit because of the upper if
                        return bridge;
                    else
                    {
                        visited[row + i][col + j] = true;
                        queue.push( {row + i, col + j} );
                    }
                }
            }
        }

        return bridge; // The execution will never come to this point
    }

private:
    void dfs(std::vector<std::vector<int>>& grid,
             int i,
             int j,
             std::queue<std::pair<int, int>>& queue,
             std::vector<std::vector<bool>>& visited)
    {
        const int N = grid.size();

        if (i < 0 || j < 0 || i == N || j == N || grid[i][j] == 0 || visited[i][j])
            return;
        queue.push( {i, j} ); // Push indices of the current land(one part of the first island)
        visited[i][j] = true; // Mark as visited

        dfs(grid, i-1, j  , queue, visited);
        dfs(grid, i+1, j  , queue, visited);
        dfs(grid, i  , j-1, queue, visited);
        dfs(grid, i  , j+1, queue, visited);
    }
};
