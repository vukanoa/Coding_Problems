/*
    ============
    === EASY ===
    ============

    ===============================================
    1351) Count Negative Numbers in a Sorted Matrix
    ===============================================

    ============
    Description:
    ============

    Given a m x n matrix grid which is sorted in non-increasing order both
    row-wise and column-wise, return the number of negative numbers in grid.

    ---------------
    -- Follow Up --
    ---------------
        Could you find an O(n + m) solution?


    ========================================================
    FUNCTION: int countNegatives(vector<vector<int>>& grid);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
    Output: 8
    Explanation: There are 8 negatives number in the matrix.

    --- Example 2 ---
    Input: grid = [[3,2],[1,0]]
    Output: 0

    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 100
    -100 <= grid[i][j] <= 100

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simple Binary Search.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  68.44% */

/* Time  Complexity: O(ROWS * log(COLS)) */
/* Space Complexity: O(1)                */
class Solution {
public:
    int countNegatives(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int total = 0; // Total Negatives

        for (int row = 0; row < ROWS; row++)
        {
            int low  = 0;
            int high = COLS;

            while (low < high)
            {
                int mid = low + (high - low) / 2;

                if (grid[row][mid] >= 0)
                    low = mid+1;
                else
                    high = mid;
            }

            total += COLS - high; // Or "COLS - low", it doesn't matter
        }

        return total;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Since we're told that the numbers are sorted in NON-increasing order
    both by rows and by columns, we can use that to our advantage in other
    way than simply applying "Binary Search".

    Once we "hit" a negative on a certain column, we know that  in this column
    in ALL the rows BELOW(including this one) we have negative numbers.

    How many are there?
    Example: ROWS - curr_row

    How do we know that?

    Because elements are sorted in NON-increasing order. If we've hit a
    negative number in THIS current column, then in all the other rows of 
    THIS COLUMN, we MUST also have a negative number.

    Therefore, there's no point in checking this column in subsequent ROWS.
    Thus, we decrement the curr_col and continue.

*/

/* Time  Complexity: O(ROWS + COLS) */
/* Space Complexity: O(1)           */
class Solution_Linear {
public:
    int countNegatives(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int curr_row = 0;
        int curr_col = COLS - 1;

        int total = 0; // Total Negatives

        while (curr_col >= 0 && curr_row < ROWS)
        {
            if (grid[curr_row][curr_col] < 0)
            {
                total += ROWS - curr_row;
                curr_col--;
            }
            else
            {
                curr_row++;
            }
        }

        return total;
    }
};
