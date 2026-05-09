/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    1914) Cyclically Rotating a Grid
    ================================

    ============
    Description:
    ============

    You are given an m x n integer matrix grid, where m and n are both even
    integers, and an integer k.

    The matrix is composed of several layers, which is shown in the below
    image, where each color is its own layer:

        <Look at the image on the LeetCode's website>

    A cyclic rotation of the matrix is done by cyclically rotating each layer
    in the matrix. To cyclically rotate a layer once, each element in the layer
    will take the place of the adjacent element in the counter-clockwise
    direction. An example rotation is shown below:

        <Look at the image on the LeetCode's website>

    Return the matrix after applying k cyclic rotations to it.

    ===========================================================================
    FUNCTION: vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[40,10],[30,20]], k = 1
    Output: [[10,20],[40,30]]
    Explanation: The figures above represent the grid at every state.

    --- Example 2 ---
    Input: grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]], k = 2
    Output: [[3,4,8,12],[2,11,10,16],[1,7,6,15],[5,9,13,14]]
    Explanation: The figures above represent the grid at every state.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    2 <= m, n <= 50
    Both m and n are even integers.
    1 <= grid[i][j] <= 5000
    1 <= k <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (This one is a pain to do. I advise you to skip it)

*/

/* Time  Beats: 19.12% */
/* Space Beats:  5.08% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k)
    {
        int ROWS = grid.size();
        int COLS = grid[0].size();

        int total_layers = min(ROWS / 2, COLS / 2);  // level count

        // counterclockwise starting from the top-left corner
        for (int layer = 0; layer < total_layers; layer++)
        {
            vector<int> curr_row;
            vector<int> curr_col;

            vector<int> val;  // each element's row index, column index, and value

            for (int row = layer; row < ROWS - layer - 1; row++) // Left
            {
                curr_row.push_back(row);
                curr_col.push_back(layer);

                val.push_back(grid[row][layer]);
            }


            for (int col = layer; col < COLS - layer - 1; col++) // Down
            {
                curr_row.push_back(ROWS - layer - 1);
                curr_col.push_back(col);

                val.push_back(grid[ROWS - layer - 1][col]);
            }


            for (int row = ROWS - layer - 1; row > layer; row--) // Right
            {
                curr_row.push_back(row);
                curr_col.push_back(COLS - layer - 1);

                val.push_back(grid[row][COLS - layer - 1]);
            }


            for (int col = COLS - layer - 1; col > layer; col--) // Up
            {
                curr_row.push_back(layer);
                curr_col.push_back(col);

                val.push_back(grid[layer][col]);
            }


            int element_in_curr_layer = val.size();
            int kk = k % element_in_curr_layer;

            // find the value at each index after rotation
            for (int i = 0; i < element_in_curr_layer; ++i)
            {
                int idx = (i + element_in_curr_layer - kk) % element_in_curr_layer;

                grid[curr_row[i]][curr_col[i]] = val[idx];
            }
        }

        return grid;
    }
};
