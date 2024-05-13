#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    861) Score After Flipping Matrix
    ================================

    ============
    Description:
    ============

    You are given an m x n binary matrix grid.

    A move consists of choosing any row or column and toggling each value in
    that row or column (i.e., changing all 0's to 1's, and all 1's to 0's).

    Every row of the matrix is interpreted as a binary number, and the score of
    the matrix is the sum of these numbers.

    Return the highest possible score after making any number of moves
    (including zero moves).

    =====================================================
    FUNCTION: int matrixScore(vector<vector<int>>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+-----+        +-----+-----+-----+-----+
    |  0  |  0  |  1  |  1  |        |  1  |  1  |  0  |  0  |
    +-----+-----+-----+-----+        +-----+-----+-----+-----+
    |  1  |  0  |  1  |  0  |  ===>  |  1  |  0  |  1  |  0  |
    +-----+-----+-----+-----+        +-----+-----+-----+-----+
    |  1  |  1  |  0  |  0  |        |  1  |  1  |  0  |  0  |
    +-----+-----+-----+-----+        +-----+-----+-----+-----+


                +-----+-----+-----+-----+        +-----+-----+-----+-----+
                |  1  |  1  |  1  |  0  |        |  1  |  1  |  1  |  1  |
                +-----+-----+-----+-----+        +-----+-----+-----+-----+
                |  1  |  0  |  0  |  0  |  ===>  |  1  |  0  |  0  |  1  |
                +-----+-----+-----+-----+        +-----+-----+-----+-----+
                |  1  |  1  |  1  |  0  |        |  1  |  1  |  1  |  1  |
                +-----+-----+-----+-----+        +-----+-----+-----+-----+

    Input: grid = [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
    Output: 39
    Explanation: 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39

    --- Example 2 ---
    Input: grid = [[0]]
    Output: 1

    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 20
    grid[i][j] is either 0 or 1.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Intuition

    By maximizing the number of set bits in the most significant bit positions,
    we can achieve maxximum possoble score.

    Approach: Greedy + Toggling

    Here's how the approach works:

        1. INITIAL SCORE INITIALIZATION: We initially assume that all the bits
           in the most significant position are set bits, meaning first column
           contains all 1s, which can be done by multiplying the number of
           rowws n with the value represented by the most significant bit
           (1 << (m - 1)).

        2. COLUMN TOGGLING: We then iterate over the remaining columns (from
           the second column to the last column) to determine whether toggling
           (flipping) the entire column would increase the score or not.

        3. VALUE OF THE CURRENT COLUMN: We then calculate a value val for each
           column j represented by that column's bit position (1 << (m-1-j)).

        4. COUNTING MATCHING ROWS: We then count the number of rows represented
           by set , where the value in the current column j matches the value
           in the first column (0 or 1) by iterating over all rows and
           comparing grid[i][j] with grid[i][0].

        5. TO TOGGLE OR NOT: If the number of rows set is greater than or equal
           to n/2 (half the number of rows), its beneficial for us to not
           toggle (flip) the column. Otherwise, its better to toggle (flip) the
           entire column to increase the score.

        6. UPDATING THE SCORE: We then update the result score by adding the
           maximum value between set * val (if the column is kept unchanged)
           and (n - set) * val (if the column is toggled), ensuring that the
           score is maximized by either keeping the current column unchanged or
           toggling it

        7. RESULTING SCORE: After iterating through all columns, we return the
           maximum score res.

    This approach works because toggling a row or a column affects all the bits
    in that row or column simultaneously. By ensuring that the most significant
    bits are set to 1 in as many rows as possible, and then adjusting the
    remaining columns based on the majority values, we can maximize the score
    of the matrix.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   9.21% */

/* Time  Complexity: O(m x n) */
/* Space Complexity: O(m x n) */
class Solution {
public:
    int matrixScore(std::vector<std::vector<int>>& grid)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        /*
            ROWS * the_number_with_a_first_bit_set_and_else 0's: 100..0

            In Example-1: COLS is 4, therefore 1000 is a number: 8
            Therefore, 2^(COLS-1), i.e. 2^3 = 8

            However, since we have ROWS=3, then we need to multiply previously
            calculated number by ROWS=3.
        */
        int result = ROWS * (1 << (COLS - 1)); // ROWS * 2^(COLS-1)

        for(int j = 1; j < COLS; j++)
        {
            int val = 1 << (COLS - 1 - j);
            int set = 0;

            for (int i = 0; i < ROWS; i++)
            {
                if (grid[i][j] == grid[i][0])
                    set++;
            }

            result += std::max(set, ROWS - set) * val;
        }

        return result;
    }
};
