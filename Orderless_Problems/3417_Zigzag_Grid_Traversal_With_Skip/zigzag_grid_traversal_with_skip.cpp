/*
    ============
    === EASY ===
    ============

    =====================================
    3417) Zigzag Grid Traversal With Skip
    =====================================

    ============
    Description:
    ============

    You are given an m x n 2D array grid of positive integers.

    Your task is to traverse grid in a zigzag pattern while skipping every
    alternate cell.

    Zigzag pattern traversal is defined as following the below actions:

        + Start at the top-left cell (0, 0).

        + Move right within a row until the end of the row is reached.

        + Drop down to the next row, then traverse left until the beginning of
          the row is reached. Continue alternating between right and left
          traversal until every row has been traversed.

    Note that you must skip every alternate cell during the traversal.

    Return an array of integers result containing, in order, the value of the
    cells visited during the zigzag traversal with skips.

    =================================================================
    FUNCTION: vector<int> zigzagTraversal(vector<vector<int>>& grid);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,2],[3,4]]
    Output: [1,4]

    --- Example 2 ---
    Input: grid = [[2,1],[2,1],[2,1]]
    Output: [2,1,2]

    --- Example 3 ---
    Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
    Output: [1,3,5,7,9]


    *** Constraints ***
    2 <= n == grid.length <= 50
    2 <= m == grid[i].length <= 50
    1 <= grid[i][j] <= 2500

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Just code it up.

    THe only place where you should be careful is whether backward iteration
    should stard at COLS-1 or COLS-2.

    If it's an even row, then we're going FORWARD starting at 0.
    If it's an odd  row, then we're going BACKWRD starting at either COLS-1 or
                                                                     COLS-2.


    If COLS is an EVEN number, then going BACKWARD we should start at COLS-1.
    If COLS is an ODD  number, then going BACKWARD we should strat at COLS-2.

    We fixed this problem by doing this:

        int col = COLS-1 - (COLS & 1);

    If COLS is ODD, then (COLS & 1) will return 1(representing TRUE) and, thus
    we'll begin at COLS-2.

    Otherwise, if COLS is an EVEN number, then we'll begin at COLS-1 because
    (COLS & 1) will now give 0(representing FALSE).

*/

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */ // Result is not additional space
class Solution {
public:
    vector<int> zigzagTraversal(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<int> result;

        for (int row = 0; row < ROWS; row++)
        {
            if (row % 2 == 0) // Even Row, go from Left-To-Right
            {
                for (int col = 0; col < COLS; col += 2)
                    result.push_back(grid[row][col]);
            }
            else
            {
                for (int col = COLS-1 - (COLS & 1); col >= 0; col -= 2)
                    result.push_back(grid[row][col]);
            }
        }

        return result;
    }
};
