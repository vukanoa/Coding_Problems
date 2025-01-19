/*
    ============
    === HARD ===
    ============

    ===========================
    407) Trapping Water II
    ===========================

    ============
    Description:
    ============

    Given an m x n integer matrix heightMap representing the height of each
    unit cell in a 2D elevation map, return the volume of water it can trap
    after raining.

    ============================================================
    FUNCTION: int trapRainWater(vector<vector<int>>& heightMap);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
    Output: 4
    Explanation: After the rain, water is trapped between the blocks.
    We have two small ponds 1 and 3 units trapped.
    The total volume of water trapped is 4.

    --- Example 2 ---
    Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
    Output: 10


    *** Constraints ***
    m == heightMap.length
    n == heightMap[i].length
    1 <= m, n <= 200
    0 <= heightMap[i][j] <= 2 * 10^4

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 31.82% */
/* Space Beats: 24.79% */

/* Time  Complexity: O(ROWS * COLS * log(ROWS) * COLS) */
/* Space Complexity: O(ROWS * COLS)                    */
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap)
    {
        const int ROWS = heightMap.size();
        const int COLS = heightMap[0].size();
        int result = 0;


        /* Signing Cross */
        std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));

        auto comparator = [](const vector<int>& a, const vector<int>& b) {
            return a[0] > b[0]; // Min-heap based on the first element
        };

        std::priority_queue<vector<int>,
                            vector<vector<int>>,
                            decltype(comparator)> boundary(comparator);

        // Add the first and last column cells to the boundary and mark them as
        // visited
        for (int row = 0; row < ROWS; row++)
        {
            boundary.push( {heightMap[row][   0    ], row, 0       } );
            boundary.push( {heightMap[row][COLS - 1], row, COLS - 1} );


            // Mark left and right boundary cells as visited
            visited[row][0] = visited[row][COLS - 1] = true;
        }

        // Add the first and last row cells to the boundary and mark them as
        // visited
        for (int col = 0; col < COLS; col++)
        {
            boundary.push( {heightMap[   0    ][col], 0       , col} );
            boundary.push( {heightMap[ROWS - 1][col], ROWS - 1, col} );

            // Mark top and bottom boundary cells as visited
            visited[0][col] = visited[ROWS - 1][col] = true;
        }

        while ( ! boundary.empty())
        {
            vector<int> current_cell = boundary.top();
            boundary.pop();

            int curr_row = current_cell[1];
            int curr_col = current_cell[2];
            int min_boundary_height = current_cell[0];

            for (int dir = 0; dir < 4; dir++)
            {
                int neighbor_row = curr_row + directions[dir].first;
                int neighbor_col = curr_col + directions[dir].second;

                if (neighbor_row < 0 || neighbor_col < 0 || neighbor_row == ROWS || neighbor_col == COLS)
                    continue;

                if (visited[neighbor_row][neighbor_col])
                    continue;

                int neighbor_height = heightMap[neighbor_row][neighbor_col];

                // If the neighbor's height is less than the current
                // boundary height, only then can water be trapped
                if (neighbor_height < min_boundary_height)
                    result += min_boundary_height - neighbor_height;

                // Push the neighbor into the boundary with updated height
                // (to prevent water leakage)
                boundary.push( {max(neighbor_height, min_boundary_height), neighbor_row, neighbor_col} );
                visited[neighbor_row][neighbor_col] = true;
            }
        }

        return result;
    }
};
