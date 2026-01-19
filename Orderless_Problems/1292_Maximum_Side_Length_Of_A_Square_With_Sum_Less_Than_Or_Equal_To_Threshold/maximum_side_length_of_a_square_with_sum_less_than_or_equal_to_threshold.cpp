/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================================================
    1292) Maximum Side Length of a Square with Sum Less than or Equal to Threshold 
    ==============================================================================

    ============
    Description:
    ============

    Given a m x n matrix mat and an integer threshold, return the maximum
    side-length of a square with a sum less than or equal to threshold or
    return 0 if there is no such square.

    =====================================================================
    FUNCTION: int maxSideLength(vector<vector<int>>& mat, int threshold);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
    Output: 2
    Explanation: The maximum side length of square with sum less than 4 is 2 as shown.

    --- Example 2 ---
    Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
    Output: 0


    *** Constraints ***
    m == mat.length
    n == mat[i].length
    1 <= m, n <= 300
    0 <= mat[i][j] <= 10^4
    0 <= threshold <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If you knew about "Prefix Sum" of a MATRIX, then this was a breeze.
    If you didn't, then first learn about it and then come back to this problem

*/

/* Time  Beats: 33.64% */
/* Space Beats: 81.36% */

/* Time  Complexity: O(ROWS * COLS * min(ROWS, COLS)) */
/* Space Complexity: O(ROWS * COLS)                   */
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold)
    {
        const int ROWS = mat.size();
        const int COLS = mat[0].size();
        int result = 0;

        long long prefix_sum[301][301] = {{0}};

        /* Compute Prefix Sum for MATRIX */
        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                prefix_sum[row][col] = mat[row][col] + prefix_sum[row+1][col  ]
                                                     + prefix_sum[row  ][col+1]
                                                     - prefix_sum[row+1][col+1];
            }
        }


        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (mat[row][col] > threshold)
                    continue;

                result = max(result, 1);

                int side = 2;
                while (row + side <= ROWS && col + side <= COLS)
                {
                    long long sum = prefix_sum[row       ][col       ] -
                                    prefix_sum[row + side][col       ] -
                                    prefix_sum[row       ][col + side] +
                                    prefix_sum[row + side][col + side];
                                    

                    if (sum > threshold)
                        break;

                    result = max(result, side);
                    side++;
                }
            }
        }

        return result;
    }
};
