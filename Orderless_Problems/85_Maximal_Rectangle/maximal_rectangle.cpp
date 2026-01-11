/*
    ============
    === HARD ===
    ============

    =====================
    85) Maximal Rectangle
    =====================

    ============
    Description:
    ============

    Given a rows x cols binary matrix filled with 0's and 1's, find the largest
    rectangle containing only 1's and return its area.

    =============================================================
    FUNCTION: int maximalRectangle(vector<vector<char>>& matrix);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+-----+-----+
    |  1  |  0  |  1  |  0  |  0  |
    +-----+-----+-----+-----+-----+
    |  1  |  0  |  1  |  1  |  1  |
    +-----+-----+-----+-----+-----+
    |  1  |  1  |  1  |  1  |  1  |
    +-----+-----+-----+-----+-----+
    |  1  |  0  |  0  |  1  |  0  |
    +-----+-----+-----+-----+-----+
    Input: matrix =
    [["1","0","1","0","0"],
     ["1","0","1","1","1"],
     ["1","1","1","1","1"],
     ["1","0","0","1","0"]]
    Output: 6
    Explanation: The maximal rectangle is shown in the above picture.


    --- Example 2 ---
    Input: matrix = [["0"]]
    Output: 0


    --- Example 3 ---
    Input: matrix = [["1"]]
    Output: 1


    *** Constraints ***
    rows == matrix.length
    cols == matrix[i].length
    1 <= row, cols <= 200
    matrix[i][j] is '0' or '1'.

*/

#include <climits>
#include <stack>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 19.25% */
/* Space Beats: 98.29% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n^2) */
class Solution_Brute_Force {
public:
    int maximalRectangle(vector<vector<char>>& matrix)
    {
        if (matrix.empty() || matrix[0].empty())
            return 0;

        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();
        int result = 0;

        vector<int> heights(COLS + 1, 0);
        for (int row = 0; row < ROWS; row++)
        {
            // Build histogram heights for current row
            for (int col = 0; col < COLS; col++)
            {
                if (matrix[row][col] == '1')
                    heights[col]++;
                else
                    heights[col] = 0;
            }

            // Brute-force largest rectangle in histogram
            for(int left_col = 0; left_col < COLS; left_col++)
            {
                int min_height_in_range = INT_MAX;

                for (int right_col = left_col; right_col < COLS; right_col++)
                {
                    min_height_in_range = min(min_height_in_range, heights[right_col]);

                    int width = right_col - left_col + 1;
                    int area  = min_height_in_range * width;

                    result = max(result, area);
                }
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    To optimize, identify and address inefficiencies in the brute-force method.
    This involves recognizing repetitive calculations, such as repeatedly
    finding the minimum height between pairs of bars. We can use techniques
    like dynamic programming (DP) or stack-based methods to streamline the
    process and reduce unnecessary recalculations, ultimately improving
    efficiency and scalability for larger datasets.

*/

/* Time  Beats: 93.51% */
/* Space Beats: 66.81% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(COLS)        */
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();
        int result = 0;

        vector<int>heights(COLS, 0);

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (matrix[row][col] == '1')
                    heights[col]++;
                else
                    heights[col] = 0;
            }

            result = max(result, area(heights));
        }

        return result;
    }

private:
    int area(vector<int>& heights)
    {
        const int COLS = heights.size();
        int result = 0;

        stack<int> stack;
        for (int col = 0; col <= COLS; col++)
        {
            while ( ! stack.empty() && (col == COLS || heights[stack.top()] >= heights[col]))
            {
                int curr_h = heights[stack.top()];
                stack.pop();

                int curr_w;
                if (stack.empty())
                    curr_w = col;
                else
                    curr_w = col - stack.top() - 1;

                result = max(result, curr_w * curr_h);
            }

            stack.push(col);
        }

        return result;
    }
};
