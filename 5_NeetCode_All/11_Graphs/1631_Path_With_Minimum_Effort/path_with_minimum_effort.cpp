/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    1631) Path With Minimum Effort
    ==============================

    ============
    Description:
    ============

    You are a hiker preparing for an upcoming hike. You are given heights, a 2D
    array of size rows x columns, where heights[row][col] represents the height
    of cell (row, col). You are situated in the top-left cell, (0, 0), and you
    hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e.,
    0-indexed). You can move up, down, left, or right, and you wish to find a
    route that requires the minimum effort.

    A route's effort is the maximum absolute difference in heights between two
    consecutive cells of the route.

    Return the minimum effort required to travel from the top-left cell to the
    bottom-right cell.

    ==============================================================
    FUNCTION: int minimumEffortPath(vector<vector<int>>& heights);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

        +-----+-----+-----+
        |  1  |  2  |  2  |
        +-----+-----+-----+
        |  3  |  8  |  2  |
        +-----+-----+-----+
        |  5  |  3  |  5  |
        +-----+-----+-----+

    Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
    Output: 2
    Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of
    2 in consecutive cells.  This is better than the route of [1,2,2,2,5],
    where the maximum absolute difference is 3.



    --- Example 2 ---

        +-----+-----+-----+
        |  1  |  2  |  3  |
        +-----+-----+-----+
        |  3  |  8  |  4  |
        +-----+-----+-----+
        |  5  |  3  |  5  |
        +-----+-----+-----+

    Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
    Output: 1
    Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of
    1 in consecutive cells, which is better than route [1,3,5,3,5].


    --- Example 3 ---

        +-----+-----+-----+-----+-----+
        |  1  |  2  |  1  |  1  |  1  |
        +-----+-----+-----+-----+-----+
        |  1  |  2  |  1  |  2  |  1  |
        +-----+-----+-----+-----+-----+
        |  1  |  2  |  1  |  2  |  1  |
        +-----+-----+-----+-----+-----+
        |  1  |  2  |  1  |  2  |  1  |
        +-----+-----+-----+-----+-----+
        |  1  |  1  |  1  |  3  |  1  |
        +-----+-----+-----+-----+-----+

    Input: heights =
    [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
    Output: 0
    Explanation: This route does not require any effort.




    *** Constraints ***
    rows == heights.length
    columns == heights[i].length
    1 <= rows, columns <= 100
    1 <= heights[i][j] <= 10^6

*/

#include <vector>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (DIjkstra on a 2D Grid)

*/

/* Time  Beats:  8.52% */
/* Space Beats: 11.42% */

/* Time  Complexity: O((ROWS * COLS) * log(ROWS * COLS)) */
/* Space Complexity: O((ROWS * COLS)                   ) */
class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights)
    {
        const int ROWS = heights.size();
        const int COLS = heights[0].size();

        // min-Heap: {abs_diff, row, col}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;
        min_heap.push( {0, 0, 0} );

        // 1D flattening technique
        bool visited[10001] = {false};

        /* Signing Cross */
        vector<pair<int,int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        /* Dijkstra's Algorithm */
        while ( ! min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop();

            int min_effort_to_here = top[0];
            int row                = top[1];
            int col                = top[2];

            if (visited[row * COLS + col])
                continue; // We've already been here with some SMALLER effort

            visited[row * COLS + col] = true;

            // If we've reached the bottom-right cell
            if (row == ROWS-1 && col == COLS-1)
                return min_effort_to_here;

            /* Signign Cross directions: Up, Down, Left, Right */
            for (const auto& dir : directions)
            {
                int new_row = row + dir.first;
                int new_col = col + dir.second;

                /* Out-of-Bounds */
                if (new_row < 0 || new_col < 0 || new_row >= ROWS || new_col >= COLS)
                    continue;

                /* Already processed */
                if (visited[new_row * COLS + new_col])
                    continue;

                int next_abs_diff  = abs(heights[row][col] - heights[new_row][new_col]);
                int new_min_effort = max(min_effort_to_here, next_abs_diff);

                min_heap.push( {new_min_effort, new_row, new_col} );
            }
        }

        return 0;
    }
};
