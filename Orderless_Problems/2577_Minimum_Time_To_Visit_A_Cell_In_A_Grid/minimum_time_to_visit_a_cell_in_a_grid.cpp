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

#include <vector>
#include <queue>

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 14.63% */
/* Space Beats: 14.18% */

/* Time  Complexity: O(ROWS * COLS * log(ROWS * COLS)) */
/* Space Complexity: O(ROWS * COLS)                    */
class Solution {
public:
    int minimumTime(vector<vector<int>>& grid)
    {
        /* Edge Case */
        if (grid[0][1] > 1 && grid[1][0] > 1)
            return -1;

        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        auto comparator = [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0])
            {
                if (a[1] == b[1])
                    return a[2] < b[2];

                return a[1] < b[1]; // Decreasing by the second
            }

            return a[0] > b[0]; // Increasing by the first
        };

        priority_queue<vector<int>,
                       vector<vector<int>>,
                       decltype(comparator)> min_heap(comparator);

        min_heap.push( {0, 0, 0} );

        /* Signing Cross */
        vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));

        while ( ! min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop();

            int time = top[0];
            int row  = top[1];
            int col  = top[2];

            if (visited[row][col])
                continue;

            visited[row][col] = true;

            if (row == ROWS-1 && col == COLS-1)
                return time;

            for (const auto& dir : directions)
            {
                int new_row = row + dir.first;
                int new_col = col + dir.second;

                if (new_row < 0 || new_col < 0 || new_row >= ROWS || new_col >= COLS)
                    continue;

                if (visited[new_row][new_col])
                    continue;

                /* Crux of this Solution */
                int min_cell_time = grid[new_row][new_col];
                if ((min_cell_time - (time + 1)) % 2 != 0) 
                    min_cell_time++;

                int arrival_time = max(time + 1, min_cell_time);

                min_heap.push( {arrival_time, new_row, new_col} );
            }
        }

        return -1; // If we can't get to bottom-right cell, return -1
    }
};
