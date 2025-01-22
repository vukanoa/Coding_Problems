/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    542) 01 Matrix
    ===========================

    ============
    Description:
    ============

    Given an m x n binary matrix mat, return the distance of the nearest 0 for
    each cell.

    The distance between two cells sharing a common edge is 1.

    =====
    Note: This question is, essentially, the same as: LeetCode 1765
    =====

    =====================================================================
    FUNCTION: vector<vector<int>> updateMatrix(vector<vector<int>>& mat);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
    Output: [[0,0,0],[0,1,0],[0,0,0]]

    --- Example 2 ---
    Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
    Output: [[0,0,0],[0,1,0],[1,2,1]]


    *** Constraints ***
    m == mat.length
    n == mat[i].length
    1 <= m, n <= 10^4
    1 <= m * n <= 10^4
    mat[i][j] is either 0 or 1.
    There is at least one 0 in mat.

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Multi-Source BFS.

    First, create "result" or ROWS * COLS cells. Then, go through mat matrix
    and at every "0-cell", i.e. at matrix[row][col] == 0, assign 0 as a
    ditance in "result" because every 0-cell's distance ought to be 0.

    However, once you do that, push it to the queue.

    After we're done traversing the mat matrix, we'll have all the 0-cells
    pushed into a queue(as a pair {row,col}).

    Those are our starting points, hence Multi-Source BFS.

    Starting from 0-cells we'll try to assign all the distances of 1 to the
    neighbor nodes of 0-cells, then we'll push all those 1 distances to the
    queue and perform a Multi-Source BFS on those to get distances of 2, etc.
    until we have visited all the cells in result.

    This is a well-known technique and its name is "Multi-Source BFS".

*/

/* Time  Beats: 25.69% */
/* Space Beats: 69.22% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat)
    {
        const int ROWS = mat.size();
        const int COLS = mat[0].size();
        const int DIRECTIONS = 4;

        vector<vector<int>> result(ROWS, vector<int>(COLS, -1));
        queue<pair<int,int>> queue;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (mat[row][col] == 0)
                {
                    result[row][col] = 0;
                    queue.push( {row, col} );
                }
            }
        }

        /* Signing Cross */
        std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        while ( ! queue.empty())
        {
            int size = queue.size();

            for (int x = 0; x < size; x++)
            {
                auto [row, col] = queue.front();
                queue.pop();

                int curr_distance = result[row][col];

                for (int dir = 0; dir < DIRECTIONS; dir++)
                {
                    int new_row = row + directions[dir].first;
                    int new_col = col + directions[dir].second;

                    if (out_of_bounds(new_row, new_col, ROWS, COLS))
                        continue;

                    if (result[new_row][new_col] != -1) // Already visited
                        continue;

                    result[new_row][new_col] = curr_distance + 1;
                    queue.push( {new_row, new_col} );
                }
            }
        }

        return result;
    }

private:
    bool out_of_bounds(int& new_row, int& new_col, const int& ROWS, const int& COLS)
    {
        return new_row < 0 || new_col < 0 || new_row == ROWS || new_col == COLS;
    }
};
