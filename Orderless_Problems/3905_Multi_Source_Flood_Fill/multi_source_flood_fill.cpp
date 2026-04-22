/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    3905) Multi Source Flood Fill
    =============================

    ============
    Description:
    ============

    You are given two integers n and m representing the number of rows and columns of a grid, respectively.

    You are also given a 2D integer array sources, where:

        sources[i] = [ri, ci, colori] indicates that the cell

    (ri, ci) is initially colored with colori. All other cells are initially
    uncolored and represented as 0.

    At each time step, every currently colored cell spreads its color to all
    adjacent uncolored cells in the four directions: up, down, left, and right.
    All spreads happen simultaneously.

    If multiple colors reach the same uncolored cell at the same time step, the
    cell takes the color with the maximum value.

    The process continues until no more cells can be colored.

    Return a 2D integer array representing the final state of the grid, where
    each cell contains its final color.

    ====================================================================================
    FUNCTION: vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& sources);
    ====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, m = 3, sources = [[0,0,1],[2,2,2]]
    Output: [[1,1,2],[1,2,2],[2,2,2]]

    --- Example 2 ---
    Input: n = 3, m = 3, sources = [[0,1,3],[1,1,5]]
    Output: [[3,3,3],[5,5,5],[5,5,5]]

    --- Example 3 ---
    Input: n = 2, m = 2, sources = [[1,1,5]]
    Output: [[5,5],[5,5]]


    *** Constraints ***
    1 <= n, m <= 10^5
    1 <= n * m <= 10^5
    1 <= sources.length <= n * m
    sources[i] = [ri, ci, colori]
    0 <= ri <= n - 1
    0 <= ci <= m - 1
    1 <= colori <= 10^6
    All (ri, ci) in sources are distinct.

*/

#include <climits>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Basic Multi-Source BFS. The only remotely difficult part was to make sure
    NOT to let change propagate after the initial coloring at time 't' is done.

*/

/* Time  Beats: 83.84% */
/* Space Beats: 83.33% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& sources)
    {
        const int ROWS = n;
        const int COLS = m;
        const int INITIALLY_COLORED = sources.size();

        vector<vector<int>> result      (ROWS, vector<int>(COLS, 0      ));
        vector<vector<int>> colored_time(ROWS, vector<int>(COLS, INT_MAX));

        /* Directions */
        vector<pair<int,int>> directions = { {-1,0}, {1,0}, {0,-1}, {0,1} };

        /* Fill initial sources */
        queue<pair<int,int>> queue;
        for (const auto& source : sources)
        {
            const int& row   = source[0];
            const int& col   = source[1];
            const int& color = source[2];

            result[row][col]       = color;
            colored_time[row][col] = 0; // At minute 0

            queue.push( {row, col} );
        }

        int uncolored = ROWS * COLS - INITIALLY_COLORED;

        /* Multi-Source BFS */
        int time = 0;
        while (uncolored > 0)
        {
            int size = queue.size();

            while (size > 0)
            {
                auto [row, col] = queue.front();
                queue.pop();

                for (const auto& dir : directions)
                {
                    int new_row = row + dir.first;
                    int new_col = col + dir.second;

                    if (new_row < 0 || new_col < 0 || new_row >= ROWS || new_col >= COLS)
                        continue;

                    if (result[new_row][new_col] == 0)
                    {
                        queue.push( {new_row, new_col} );
                        colored_time[new_row][new_col] = time+1;
                        uncolored--;
                    }

                    if (colored_time[new_row][new_col] == time+1)
                        result[new_row][new_col] = max(result[new_row][new_col], result[row][col]);
                }

                // Decrement
                size--;
            }

            // Increment Time
            time++;
        }

        return result;
    }
};
