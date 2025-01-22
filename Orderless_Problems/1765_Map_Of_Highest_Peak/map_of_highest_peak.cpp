/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1765) Map of Highest Peak
    ===========================

    ============
    Description:
    ============

    You are given an integer matrix isWater of size m x n that represents a map
    of land and water cells.

        + If isWater[i][j] == 0, cell (i, j) is a land cell.
        + If isWater[i][j] == 1, cell (i, j) is a water cell.

    You must assign each cell a height in a way that follows these rules:

        + The height of each cell must be non-negative.

        + If the cell is a water cell, its height must be 0.

        + Any two adjacent cells must have an absolute height difference of at
          most 1. A cell is adjacent to another cell if the former is directly
          north, east, south, or west of the latter (i.e., their sides are
          touching).

    Find an assignment of heights such that the maximum height in the matrix is
    maximized.

    Return an integer matrix height of size m x n where height[i][j] is
    cell (i, j)'s height. If there are multiple solutions, return any of them.

    =====
    Note: This question is the same as LeetCode: 542 "01 Matrix"
    =====

    ========================================================================
    FUNCTION: vector<vector<int>> highestPeak(vector<vector<int>>& isWater);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: isWater = [[0,1],[0,0]]
    Output: [[1,0],[2,1]]
    Explanation: The image shows the assigned heights of each cell.
    The blue cell is the water cell, and the green cells are the land cells.

    --- Example 2 ---
    Input: isWater = [[0,0,1],[1,0,0],[0,0,0]]
    Output: [[1,1,0],[0,1,1],[1,2,2]]
    Explanation: A height of 2 is the maximum possible height of any assignment
    Any height assignment that has a maximum height of 2 while still meeting
    the rules will also be accepted.


    *** Constraints ***
    m == isWater.length
    n == isWater[i].length
    1 <= m, n <= 1000
    isWater[i][j] is 0 or 1.
    There is at least one water cell.

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Multi-Source BFS.

    First, create "heights" or ROWS * COLS cells. Then, go through isWater
    matrix and at every "water cell", i.e. at isWater[row][col] == 1, assign 0
    as a height in "heights" because every water-cell's height ought to be 0.

    However once you do that, push it to the queue.

    After we're done traversing the isWater matrix, we'll have all the
    water-cells pushed into a queue(as a pair {row,col}).

    Those are our starting points, henceforth Multi-Source BFS.

    Starting from water-cells we'll try to assign all the heights 1 to the
    neighbor nodes of water-cells, then we'll push all those 1 heights to the
    queue and perform a Multi-Source BFS on those to get heights of 2, etc.
    until we have visited all the cells in heights.

    This is a well-known technique and its name is "Multi-Source BFS".

*/

/* Time  Beats: 84.22% */
/* Space Beats: 59.10% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater)
    {
        const int ROWS = isWater.size();
        const int COLS = isWater[0].size();
        const int DIRECTIONS = 4;

        vector<vector<int>> heights(ROWS, vector<int>(COLS, -1));

        queue<pair<int,int>> queue;
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (isWater[row][col] == 1) // If it's a water-cell
                {
                    queue.push( {row, col} );
                    heights[row][col] = 0;
                }
            }
        }

        /* Signing Cross */
        std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};


        /* Do a Multi-Source BFS */
        while ( ! queue.empty())
        {
            int size = queue.size();

            for (int x = 0; x < size; x++)
            {
                auto [row, col] = queue.front();
                queue.pop();

                int curr_height = heights[row][col];

                for (int dir = 0; dir < DIRECTIONS; dir++)
                {
                    int new_row = row + directions[dir].first;
                    int new_col = col + directions[dir].second;

                    if (out_of_bounds(new_row, new_col, ROWS, COLS))
                        continue;

                    if (heights[new_row][new_col] != -1) // Already visited
                        continue;

                    heights[new_row][new_col] = curr_height + 1;
                    queue.push( {new_row, new_col} );
                }
            }
        }

        return heights;
    }

private:
    bool out_of_bounds(int& new_row, int& new_col, const int& ROWS, const int& COLS)
    {
        return new_row < 0 || new_col < 0 || new_row == ROWS || new_col == COLS;
    }
};
