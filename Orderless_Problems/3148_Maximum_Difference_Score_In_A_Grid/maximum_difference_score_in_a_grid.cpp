/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    3148) Maximum Difference Score in a Grid
    ========================================

    ============
    Description:
    ============

    You are given an m x n matrix grid consisting of positive integers. You can
    move from a cell in the matrix to any other cell that is either to the
    bottom or to the right (not necessarily adjacent). The score of a move
    from a cell with the value c1 to a cell with the value c2 is c2 - c1.

    You can start at any cell, and you have to make at least one move.

    Return the maximum total score you can achieve.

    ==================================================
    FUNCTION: int maxScore(vector<vector<int>>& grid);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[9,5,7,3],[8,9,6,1],[6,7,14,3],[2,5,3,1]]
    Output: 9
    Explanation: We start at the cell (0, 1), and we perform the following moves:
    - Move from the cell (0, 1) to (2, 1) with a score of 7 - 5 = 2.
    - Move from the cell (2, 1) to (2, 2) with a score of 14 - 7 = 7.
    The total score is 2 + 7 = 9.

    --- Example 2 ---
    Input: grid = [[4,3,2],[3,2,1]]
    Output: -1
    Explanation: We start at the cell (0, 0), and we perform one move: (0, 0)
                 to (0, 1). The score is 3 - 4 = -1.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    2 <= m, n <= 1000
    4 <= m * n <= 10^5
    1 <= grid[i][j] <= 10^5

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This was done during the contest, so even if it's messy I wanted to keep
    this "logic" in.

    The second Solution down below is an Elegant way of writing this Solution.

    It was just easier to think about it this way.
    Here is the "picture" of this approach:


    Example:
    grid = [[6,1,4,6],[5,6,3,5],[5,3,10,3],[8,7,1,5],[1,6,6,2]]


    grid_pair: (up is "first", down is "second" from the pair)
        +-----+-----+-----+-----+
        |  6  |  1  |  4  |  6  |
        |  0  |  9  |  6  |  0  |
        +-----+-----+-----+-----+
        |  5  |  6  |  3  |  6  |
        |  5  |  4  |  7  | -1  |
        +-----+-----+-----+-----+
        |  5  |  3  | 10  |  3  |
        |  5  |  7  | -4  |  2  |
        +-----+-----+-----+-----+
        |  8  |  7  |  1  |  5  |
        | -2  | -2  |  5  | -3  |
        +-----+-----+-----+-----+
        |  1  |  6  |  6  |  2  |
        |  5  |  0  | -4  |  0  |
        +-----+-----+-----+-----+

*/

/* Time  Beats: 44.62% */
/* Space Beats:  9.56% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_2 { // Weekly 397 Q3
public:
    int maxScore(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<vector<pair<int,int>>> grid_pair(ROWS, vector<pair<int,int>>(COLS, pair<int,int>(0, INT_MIN)));
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                grid_pair[row][col].first = grid[row][col];
            }
        }

        grid_pair[ROWS-1][COLS-1].second = 0;



        vector<pair<int,int>> best_in_col(COLS, pair<int,int>());
        best_in_col[COLS-1] = grid_pair[ROWS-1][COLS-1];

        pair<int,int> best_to_the_right = grid_pair[ROWS-1][COLS-1];

        for (int col = COLS-2; col >= 0; col--)
        {
            int base   = best_to_the_right.first - grid[ROWS-1][col];
            int addend = best_to_the_right.second;

            grid_pair[ROWS-1][col].second = max(base, base + addend);

            int num = grid_pair[ROWS-1][col].first;
            int add = grid_pair[ROWS-1][col].second;

            if ((num + add) > (best_to_the_right.first + addend))
            {
                best_to_the_right = {num, add};
            }
            else if ((num + add) == (best_to_the_right.first + addend))
            {
                if (num > best_to_the_right.first)
                {
                    best_to_the_right = {num, add};
                }
            }

            best_in_col[col] = best_to_the_right;
        }

        for (int row = ROWS-2; row >= 0; row--)
        {
            int base   = best_in_col[COLS-1].first - grid[row][COLS-1];
            int addend = best_in_col[COLS-1].second;

            grid_pair[row][COLS-1].second = max(base, base + addend);

            int num = grid_pair[row][COLS-1].first;
            int add = grid_pair[row][COLS-1].second;

            if ((num + add) > (best_in_col[COLS-1].first + best_in_col[COLS-1].second))
            {
                best_in_col[COLS-1] = {num, add};
            }
            else if ((num + add) == (best_in_col[COLS-1].first + best_in_col[COLS-1].second))
            {
                if (num > best_in_col[COLS-1].first)
                {
                    best_in_col[COLS-1] = {num, add};
                }
            }
        }

        for (int row = ROWS-2; row >= 0; row--)
        {
            best_to_the_right = grid_pair[row][COLS-1];

            for (int col = COLS-2; col >= 0; col--)
            {
                int r_base   = best_to_the_right.first - grid[row][col];
                int r_addend = best_to_the_right.second;

                int d_base   = best_in_col[col].first - grid[row][col];
                int d_addend = best_in_col[col].second;

                grid_pair[row][col].second = max( max(r_base, r_base + r_addend),
                                                  max(d_base, d_base + d_addend) );

                int num = grid_pair[row][col].first;
                int add = grid_pair[row][col].second;

                // Try moving right
                if ((num + add) > (best_to_the_right.first + r_addend))
                {
                    best_to_the_right = {num, add};
                }
                else if ((num + add) == (best_to_the_right.first + r_addend))
                {
                    if (num > best_to_the_right.first)
                    {
                        best_to_the_right = {num, add};
                    }
                }

                // Try moving right
                if ((num + add) > (best_in_col[col].first + best_in_col[col].second))
                {
                    best_in_col[col] = {num, add};
                }
                else if ((num + add) == (best_in_col[col].first + best_in_col[col].second))
                {
                    if (num > best_in_col[col].first)
                    {
                        best_in_col[col] = {num, add};
                    }
                }
            }
        }

        // Find max value in dp table (excluding bottom-right)
        int result = INT_MIN;
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (row == ROWS-1 && col == COLS-1)
                    continue;

                result = max(result, grid_pair[row][col].second);
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, thought written in a much more concise way.

*/

/* Time  Beats: 44.62% */
/* Space Beats: 47.41% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    int maxScore(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<vector<int>> dp(ROWS, vector<int>(COLS, INT_MIN));

        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                // Try moving Right
                if (col + 1 < COLS)
                {
                    int base   = grid[row][col + 1] - grid[row][col];
                    int addend =  dp[row][col + 1];

                    int score = base;
                    if (addend != INT_MIN)
                        score = max(base, base + addend);

                    dp[row][col] = max(dp[row][col], score);
                }

                // Try moving Down
                if (row + 1 < ROWS)
                {
                    int base   = grid[row + 1][col] - grid[row][col];
                    int addend =  dp[row + 1][col];

                    int score = base;
                    if (addend != INT_MIN)
                        score = max(base, base + addend);

                    dp[row][col] = max(dp[row][col], score);
                }
            }
        }

        // Find max value in dp table (excluding bottom-right)
        int result = INT_MIN;
        for (int row = 0; row < ROWS; ++row)
        {
            for (int col = 0; col < COLS; ++col)
            {
                if (row == ROWS - 1 && col == COLS - 1)
                    continue;

                result = max(result, dp[row][col]);
            }
        }

        return result;
    }
};
