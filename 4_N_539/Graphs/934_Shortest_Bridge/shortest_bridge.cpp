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




/*
    ------------
    --- IDEA ---
    ------------

    This is a combination of: DFS & BFS.

    This Solution has 3 steps.

    1. Iterate through the "grid" until you stumble upon a '1'(which represents
       one field of the first island) and then do a DFS starting from that very
       field.

       While doing a DFS, all of the 1's, of that first Island, will be changed
       to 2's.

       That way we're making a distinction between the First and the Second
       Island.

       Now the land of the First Island is represented with 2's, while the land
       of the Second Island is represented with 1's.

       (There are no actual "First" and "Second", you can choose which one of
       the two are you going to call "First" and which one are you going to
       call "Second". Maybe It's even better to call the one that is
       represented with 2's, "Second", and the other one "First". But it
       doesn't matter.)


    2. Push the positions(i.e. a pair of {i, j} ) of all of the 2's to the
       Queue.

       Now we have all of the "fields" that compose a "First Island"(or a
       "Second Island", however you choose to call it) in the Queue.

       Since and Island it composed of different "fields", i.e. positions in
       the grid, that means we had to push each and every position to the
       Queue.

       And that's exactly what we did.


    3. Now we perform a BFS, starting with an initial state of the Queue we've
       just filled.

       Essentially we start from the "First Island" and we expand it
       level-by-level until we find a '1' in the grid.

       Why 1?

       Because that's the OTHER Island.
       (Remember, they've said in the Description that there are exactly 2
       Islands in the grid, no more and no less. Therefore, if one Island is
       represented with 2's, the OTHER one, then, MUST be represented with 1's)

       While we're going through the layers one-by-one(meaning while we
       "construct" the bridge over the water "fields") we're going to mark
       those spots with 3's.

       Why 3's and not 2's?

       We can mark it with 2's as well, however, I wanted to mark it with 3's
       because if the interviewer said that we're NOT allowed to modify the
       "grid", then we'd have to return the "grid" to its initial state.

       If we were to mark the "bridge" with 2's as well, then once we tried to
       return the "grid" to its initial state, we wouldn't be able to do so.

       How would we differentiate between the "bridge field" and "First
       Island's field"?
       We wouldn't be able to.

       That's why I'm marking the "bridge" with 3's.

       For the Testcases of LeetCode, that's not needed, you can indeed mark it
       with 2, however I wanted to point out this possibillity.

       Every time we finish a new "layer", we increment "flips" by one.
       If at any point of processing the current "layer" we find out that there
       is a field with value '1' in any of the 4-directionally connected fields
       then we should immediatelly return the current value of "flips".

*/

/* Time  Beats: 90.16% */
/* Space Beats: 94.53% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution {
public:
    int shortestBridge(std::vector<std::vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        /* Mark First Island with 2's */
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid[i][j] == 1)
                {
                    dfs(grid, i, j);

                    i = ROWS; // Break the Outer loop
                    break;    // Break the Inner loop
                }
            }
        }

        std::queue<std::pair<int, int>> queue;

        /* Initialize a Queue with the first Island's positions(marked with 2's) */
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid[i][j] == 2)
                    queue.push({i, j});
            }
        }

        /* Signing Cross */
        std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        int flips = 0;

        /* BFS */
        while (!queue.empty())
        {
            int size = queue.size();

            for (int i = 0; i < size; i++)
            {
                std::pair<int, int> land = queue.front();
                queue.pop();

                for (const auto& dir : directions)
                {
                    int row = land.first  + dir.first;
                    int col = land.second + dir.second;

                    if (row < 0     || col < 0     ||
                        row == ROWS || col == COLS || grid[row][col] > 1)
                    {
                        continue;
                    }
                    else if (grid[row][col] == 1)
                        return flips;

                    grid[row][col] = 3;
                    queue.push({row, col});
                }
            }

            flips++;
        }

        return -1; // This will never be returned
    }

private:
    void dfs(std::vector<std::vector<int>>& grid, int i, int j)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (i < 0 || j < 0 || i == ROWS || j == COLS || grid[i][j] != 1)
            return;

        grid[i][j] = 2;

        dfs(grid, i-1, j  );
        dfs(grid, i+1, j  );
        dfs(grid, i  , j-1);
        dfs(grid, i  , j+1);
    }
};
