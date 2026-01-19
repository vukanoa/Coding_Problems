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




/*
    ------------
    --- IDEA ---
    ------------

    Instead of manually checking every square of side: 1, then 2, then 3, ...

    We know that if we find a VALID square(whose sum is <= threshold) of side
    length equal, say, 4 then why would we want to even check side lengths of:
    1, 2 and 3?

    Those will CERTAINLY not be a Solution, therefore we're wasting time.

    Since we have a RANGE of possible answers and we know the bounds, i.e.
    smallest possible result(besides 0) is square of size 1 and biggest
    possible result is a square of side length equal to min(ROWS, COLS).

    Since we know our result is WITHIN SOME BOUNDARY, why not just perform a
    Binary Search? (specifically I've implemeneted lower_bound).

    That's exactly what we're doing here.

*/

/* Time  Beats: 95.00% */
/* Space Beats: 82.73% */

/* Time  Complexity: O(ROWS * COLS * log(min(ROWS,COLS))) */
/* Space Complexity: O(ROWS * COLS)                       */
class Solution_Binary_Search {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold)
    {
        const int ROWS = mat.size();
        const int COLS = mat[0].size();

        long long prefix_sum[301][301] = {{0}}; // O(ROWS * COLS)

        // O(ROWS * COLS) (entire block)
        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                prefix_sum[row][col] = mat[row][col] + prefix_sum[row + 1][col    ] +
                                                       prefix_sum[row    ][col + 1] -
                                                       prefix_sum[row + 1][col + 1];
            }
        }

        int max_possible_side_length = min(ROWS, COLS);
        return my_lower_bound(1, max_possible_side_length + 1, prefix_sum, ROWS, COLS, threshold);
    }

private:
    // O(ROWS * COLS) (entire block(i.e. function))
    bool is_valid(long long (& prefix_sum)[301][301], int ROWS, int COLS, int side, int threshold)
    {
        for (int row = 0; row + side <= ROWS; row++)
        {
            for (int col = 0; col + side <= COLS; col++)
            {
                long long sum = prefix_sum[row       ][col       ] -
                                prefix_sum[row + side][col       ] -
                                prefix_sum[row       ][col + side] +
                                prefix_sum[row + side][col + side];

                if (sum <= threshold)
                    return true;
            }
        }

        return false;
    }

    // O(ROWS * COLS * log(min(ROWS, COLS))) (entire block(i.e. function))
    int my_lower_bound(int low, int high, long long (& prefix_sum)[301][301], int ROWS, int COLS, int threshold)
    {
        /* Binary Search(lower_bound) on Square SIDE LENGTH */
        while (low < high) // O(log(min(ROWS, COLS)))
        {
            // mid <==> square_side_len
            int mid = low + (high - low) / 2; // LEFT-leaning

            if (is_valid(prefix_sum, ROWS, COLS, mid, threshold)) // O(ROWS * COLS)
                low = mid + 1;
            else
                high = mid;
        }

        return high - 1;
    }
};
