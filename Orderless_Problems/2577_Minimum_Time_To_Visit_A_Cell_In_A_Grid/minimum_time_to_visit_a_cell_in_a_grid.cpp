#include <iostream>
#include <vector>
#include <queue>

/*
    ============
    === HARD ===
    ============

    ============================================
    2577) Minimum Time To Visit a Cell In a Grid
    ============================================

    ============
    Description:
    ============

    You are given a m x n matrix grid consisting of non-negative integers where
    grid[row][col] represents the minimum time required to be able to visit the
    cell (row, col), which means you can visit the cell (row, col) only when
    the time you visit it is greater than or equal to grid[row][col].

    You are standing in the top-left cell of the matrix in the 0th second, and
    you must move to any adjacent cell in the four directions: up, down, left,
    and right. Each move you make takes 1 second.

    Return the minimum time required in which you can visit the bottom-right
    cell of the matrix. If you cannot visit the bottom-right cell, then return
    -1.

    =====================================================
    FUNCTION: int minimumTime(vector<vector<int>>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
    Output: 7
    Explanation: One of the paths that we can take is the following:
    - at t = 0, we are on the cell (0,0).
    - at t = 1, we move to the cell (0,1). It is possible because grid[0][1] <= 1.
    - at t = 2, we move to the cell (1,1). It is possible because grid[1][1] <= 2.
    - at t = 3, we move to the cell (1,2). It is possible because grid[1][2] <= 3.
    - at t = 4, we move to the cell (1,1). It is possible because grid[1][1] <= 4.
    - at t = 5, we move to the cell (1,2). It is possible because grid[1][2] <= 5.
    - at t = 6, we move to the cell (1,3). It is possible because grid[1][3] <= 6.
    - at t = 7, we move to the cell (2,3). It is possible because grid[2][3] <= 7.
    The final time is 7. It can be shown that it is the minimum time possible.


    --- Example 2 ---
    Input: grid = [[0,2,4],[3,2,1],[1,0,4]]
    Output: -1
    Explanation: There is no path from the top left to the bottom-right cell.



    *** Constraints ***
    m == grid.length
    n == grid[i].length
    2 <= m, n <= 1000
    4 <= m * n <= 10^5
    0 <= grid[i][j] <= 10^5
    grid[0][0] == 0

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 48.53% */
/* Space Beats: 43.40% */

/* Time  Complexity: O(M * N * log(M * N)) */
/* Space Complexity: O(M * N)              */
class Solution {
public:
    int minimumTime(vector<vector<int>>& grid)
    {
        if (grid[0][1] > 1 && grid[1][0] > 1)
            return -1;

        const int ROWS = grid.size();
        const int COLS = grid[0].size();


        // Min Heap of VECTOR<INT>
        std::priority_queue<vector<int>,
                            std::vector<vector<int>>,
                            std::greater<vector<int>>> min_heap; // {time, row, col}

        // Add the starting position
        min_heap.push({0, 0, 0}); // {time, row, col}

        /* Signing Cross */
        std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));

        while ( ! min_heap.empty())
        {
            int curr_time = min_heap.top()[0];
            int curr_row  = min_heap.top()[1];
            int curr_col  = min_heap.top()[2];
            min_heap.pop();

            if (curr_row == ROWS-1 && curr_col == COLS-1)
                return curr_time;

            for (const auto& dir : directions)
            {
                // Neighbor <==> nei
                int nei_row = curr_row + dir.first;
                int nei_col = curr_col + dir.second;

                if (nei_row < 0 || nei_col < 0 || nei_row == ROWS || nei_col == COLS)
                    continue;

                if (visited[nei_row][nei_col])
                    continue;

                /* Crux of this Solution */
                int wait = 0;
                if (abs(grid[nei_row][nei_col] - curr_time) % 2 == 0)
                    wait = 1;

                int next_time = max(grid[nei_row][nei_col] + wait, curr_time + 1);
                min_heap.push({next_time, nei_row, nei_col});
                visited[nei_row][nei_col] = true;
            }
        }

        return -1; // We won't ever get to here
    }
};
