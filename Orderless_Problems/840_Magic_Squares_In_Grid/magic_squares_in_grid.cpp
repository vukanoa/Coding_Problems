#include <iostream>
#include <vector>
#include <bitset>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    840) Magic Squares In Grid
    ===========================

    ============
    Description:
    ============

    A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to
    9 such that each row, column, and both diagonals all have the same sum.

    Given a row x col grid of integers, how many 3 x 3 contiguous magic square
    subgrids are there?

    =====
    Note: while a magic square can only contain numbers from 1 to 9, grid may
          contain numbers up to 15.
    =====

    ===============================================================
    FUNCTION: int numMagicSquaresInside(vector<vector<int>>& grid);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[4,3,8,4],[9,5,1,9],[2,7,6,2]]
    Output: 1
    Explanation:
    The following subgrid is a 3 x 3 magic square:
        GO ON LEETCODE AND SEE THE PICTURE

    while this one is not:
        GO ON LEETCODE AND SEE THE PICTURE

    In total, there is only one magic square inside the given grid.



    --- Example 2 ---
    Input: grid = [[8]]
    Output: 0


    *** Constraints ***
    row == grid.length
    col == grid[i].length
    1 <= row, col <= 10
    0 <= grid[i][j] <= 15

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 38.66% */
/* Space Beats: 71.43% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (ROWS < 3 || COLS < 3)
            return 0;

        int cnt = 0;
        for (int i = 1; i < ROWS-1; i++)
        {
            for(int j=1; j < COLS-1; j++)
            {
                // Center is not 5
                if (grid[i][j] != 5)
                    continue;

                int a = grid[i-1][j-1];
                int b = grid[i-1][j+1];
                int c = grid[i+1][j-1];
                int d = grid[i+1][j+1];

                bitset<10> once = (1 << a) + (1 << b) + (1 << c) + (1 << d) + (1 << 5);

                // Check diagonals & center, numbers in corner are even
                if (once.count() == 5 && (a&1) == 0 && a+d == 10 && (b&1) == 0 && b+c == 10 )
                    cnt += isMagic(grid, i, j, a, b, c, d);
            }
        }

        return cnt;
    }

private:
    bool isMagic(vector<vector<int>>& grid,
                 int i,
                 int j,
                 int a,
                 int b,
                 int c,
                 int d
                )
    {
        // Check sums without through center, In fact like solving linear system
        return (a + grid[i - 1][j    ] + b == 15) &&
               (a + grid[i    ][j - 1] + c == 15) &&
               (b + grid[i    ][j + 1] + d == 15) &&
               (c + grid[i + 1][j    ] + d == 15);
    }

};
