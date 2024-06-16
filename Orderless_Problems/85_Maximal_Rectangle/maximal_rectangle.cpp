#include <iostream>

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
    int maximalRectangle(std::vector<std::vector<char>>& matrix)
    {
        if (matrix.empty() || matrix[0].empty())
            return 0;

        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        // Include an extra element for easier calculation
        std::vector<int> heights(COLS + 1, 0);
        int max_area = 0;

        for (const auto& row : matrix)
        {
            for (int i = 0; i < COLS; i++)
                heights[i] = (row[i] == '1') ? heights[i] + 1 : 0;

            // Calculate max area using histogram method
            int n = heights.size(); // Number of bars in the histogram

            for (int i = 0; i < n; i++)
            {
                int min_height = INT_MAX;

                for (int j = i; j < n; j++)
                {
                    min_height = std::min(min_height, heights[j]);

                    int area = min_height * (j - i + 1);
                    max_area = std::max(max_area, area);
                }
            }
        }

        return max_area;
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

/* Time  Beats: 84.87% */
/* Space Beats: 81.27% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(M)     */
class Solution_Optimization {
public:
    int maximalRectangle(std::vector<std::vector<char>>& matrix)
    {
        if (matrix.empty() || matrix[0].empty())
            return 0;

        int ROWS = matrix.size();
        int COLS = matrix[0].size();
        std::vector<int> heights(COLS + 1, 0); // Include an extra element for easier calculation
        int max_area = 0;

        for (const auto& row : matrix)
        {
            for (int i = 0; i < COLS; i++)
            {
                heights[i] = (row[i] == '1') ? heights[i] + 1 : 0;
            }

            // Calculate max area using stack-based method
            stack<int> stack;
            for (int i = 0; i < heights.size(); i++)
            {
                while (!stack.empty() && heights[i] < heights[stack.top()])
                {
                    int h = heights[stack.top()];
                    stack.pop();
                    int w = stack.empty() ? i : i - stack.top() - 1;
                    max_area = max(max_area, h * w);
                }

                stack.push(i);
            }
        }

        return max_area;
    }
};
