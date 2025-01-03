#include <iostream>
#include <vector>
#include <queue>

/*
    ============
    === HARD ===
    ============

    ==============================================
    2290) Minimum Obstacle Removal to Reach Corner
    ==============================================

    ============
    Description:
    ============

    You are given a 0-indexed 2D integer array grid of size m x n. Each cell
    has one of two values:

        + 0 represents an empty cell,
        + 1 represents an obstacle that may be removed.

    You can move up, down, left, or right from and to an empty cell.

    Return the minimum number of obstacles to remove so you can move from the
    upper left corner (0, 0) to the lower right corner (m - 1, n - 1).

    ==========================================================
    FUNCTION: int minimumObstacles(vector<vector<int>>& grid);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[0,1,1],[1,1,0],[1,1,0]]
    Output: 2
    Explanation: We can remove the obstacles at (0, 1) and (0, 2) to create a
                 path from (0, 0) to (2, 2). It can be shown that we need to
                 remove at least 2 obstacles, so we return 2. Note that there
                 may be other ways to remove 2 obstacles to create a path.


    --- Example 2 ---
    Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]]
    Output: 0
    Explanation: We can move from (0, 0) to (2, 4) without removing any
                 obstacles, so we return 0.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 10^5
    2 <= m * n <= 10^5
    grid[i][j] is either 0 or 1.
    grid[0][0] == grid[m - 1][n - 1] == 0

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (More or less standard Dijkstra Algorithm)

*/

/* Time  Beats: 30.45% */
/* Space Beats: 39.43% */

/* Time  Complexity: O(M * N * log(M * N)) */
/* Space Complexity: O(M * N)             */
class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        // Min Heap of vector<int>
        std::priority_queue<vector<int>,
                            std::vector<vector<int>>,
                            std::greater<vector<int>>> min_heap;

        min_heap.push({0, 0, 0}); // {obstacles, row, col}

        vector<vector<int>> visited(ROWS, vector<int>(COLS, false));

        /* Signing Cross */
        std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        while ( ! min_heap.empty())
        {
            int obstacles = min_heap.top()[0];
            int curr_row  = min_heap.top()[1];
            int curr_col  = min_heap.top()[2];
            min_heap.pop();

            if (curr_row == ROWS-1 && curr_col == COLS-1)
                return obstacles;

            for (const auto& dir : directions)
            {
                // Neighbor <==> nei
                int nei_row = curr_row + dir.first;
                int nei_col = curr_col + dir.second;

                if (nei_row < 0 || nei_col < 0 || nei_row == ROWS || nei_col == COLS)
                    continue;

                if (visited[nei_row][nei_col])
                    continue;

                min_heap.push({obstacles + grid[nei_row][nei_col], nei_row, nei_col});
                visited[nei_row][nei_col] = true;
            }
        }

        return -1; // We won't get to here
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Optimized approach. Instead of using a MinHeap, use a Deque and reduce
    Time Complexity by log(M * N).

*/

/* Time  Beats: 44.48% */
/* Space Beats: 20.43% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M * N) */
class Solution_Optimal {
public:
    int minimumObstacles(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        deque<vector<int>> deque;
        deque.push_front({0, 0, 0}); // {obstacles, row, col}

        vector<vector<int>> visited(ROWS, vector<int>(COLS, false));

        /* Signing Cross */
        std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        while ( ! deque.empty())
        {
            int obstacles = deque.front()[0];
            int curr_row  = deque.front()[1];
            int curr_col  = deque.front()[2];
            deque.pop_front();

            if (curr_row == ROWS-1 && curr_col == COLS-1)
                return obstacles;

            for (const auto& dir : directions)
            {
                // Neighbor <==> nei
                int nei_row = curr_row + dir.first;
                int nei_col = curr_col + dir.second;

                if (nei_row < 0 || nei_col < 0 || nei_row == ROWS || nei_col == COLS)
                    continue;

                if (visited[nei_row][nei_col])
                    continue;

                if (grid[nei_row][nei_col] == 1) // It's an obstacle
                    deque.push_back({obstacles  + 1, nei_row, nei_col}); // Push to the back
                else
                    deque.push_front({obstacles + 0, nei_row, nei_col}); // Push to the front

                visited[nei_row][nei_col] = true;
            }
        }

        return -1; // We won't get to here
    }
};
