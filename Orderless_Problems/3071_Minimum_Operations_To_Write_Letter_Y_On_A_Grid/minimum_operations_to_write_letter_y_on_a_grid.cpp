/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    3071) Minimum Operations to Write the Letter Y on a Grid
    ========================================================

    ============
    Description:
    ============

    You are given a 0-indexed n x n grid where n is odd, and grid[r][c] is
    0, 1, or 2.

    We say that a cell belongs to the Letter Y if it belongs to one of the
    following:

        + The diagonal starting at the top-left cell and ending at the center
          cell of the grid.

        + The diagonal starting at the top-right cell and ending at the center
          cell of the grid.

        = The vertical line starting at the center cell and ending at the
          bottom border of the grid.

    The Letter Y is written on the grid if and only if:

        + All values at cells belonging to the Y are equal.

        + All values at cells not belonging to the Y are equal.

        + The values at cells belonging to the Y are different from the values
          at cells not belonging to the Y.

    Return the minimum number of operations needed to write the letter Y on the
    grid given that in one operation you can change the value at any cell to
    0, 1, or 2.

    ===================================================================
    FUNCTION: int minimumOperationsToWriteY(vector<vector<int>>& grid);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,2,2],[1,1,0],[0,1,0]]
    Output: 3
    Explanation: We can write Y on the grid by applying the changes highlighted
                 in blue in the image above. After the operations, all cells
                 that belong to Y, denoted in bold, have the same value of 1
                 while those that do not belong to Y are equal to 0.
                 It can be shown that 3 is the minimum number of operations
                 needed to write Y on the grid.


    --- Example 2 ---
    Input: grid = [[0,1,0,1,0],[2,1,0,1,2],[2,2,2,0,1],[2,2,2,2,2],[2,1,2,2,2]]
    Output: 12
    Explanation: We can write Y on the grid by applying the changes highlighted
                 in blue in the image above. After the operations, all cells
                 that belong to Y, denoted in bold, have the same value of 0
                 while those that do not belong to Y are equal to 2.
                 It can be shown that 12 is the minimum number of operations
                 needed to write Y on the grid.


    *** Constraints ***
    3 <= n <= 49
    n == grid.length == grid[i].length
    0 <= grid[i][j] <= 2
    n is odd.

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 74.74% */
/* Space Beats: 27.72% */

/* Time  Complexity: O(N * N) */
/* Space Complexity: O(1)     */
class Solution {
public:
    int minimumOperationsToWriteY(vector<vector<int>>& grid)
    {
        const int N = grid.size();
        const int MID = N / 2;

        int result = 0;

        vector<pair<int,int>> y_counter = {{0,0}, {0,1}, {0,2}};
        vector<pair<int,int>> x_counter = {{0,0}, {0,1}, {0,2}};

        int y = 0;
        int x = 0;
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
            {
                if ((row <= MID && (col == row || col == N-1 - row)) ||
                    (row >= MID && (col == MID)))
                {
                    y_counter[grid[row][col]].first++;
                    y++;
                }
                else
                {
                    x_counter[grid[row][col]].first++;
                    x++;
                }
            }
        }

        int total = N * N;

        sort(y_counter.begin(), y_counter.end(), greater<pair<int,int>>());
        sort(x_counter.begin(), x_counter.end(), greater<pair<int,int>>());

        int y_operations = y - y_counter[0].first;
        int x_operations = x - x_counter[0].first;

        if (y_counter[0].second == x_counter[0].second)
        {
            int y_first = y_operations + (x - x_counter[1].first);
            int x_first = x_operations + (y - y_counter[1].first);

            if (y_first < x_first)
            {
                result += y_operations;
                result += x - x_counter[1].first;
            }
            else
            {
                result += x_operations;
                result += y - y_counter[1].first;
            }
        }
        else
        {
            result += y_operations + x_operations;
        }


        return result;
    }
};
