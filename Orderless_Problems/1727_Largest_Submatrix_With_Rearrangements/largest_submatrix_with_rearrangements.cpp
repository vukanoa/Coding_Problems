#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    1727) Largest Submatrix With Rearrangements
    ===========================================

    ============
    Description:
    ============

    You are given a binary matrix matrix of size m x n, and you are allowed to
    rearrange the columns of the matrix in any order.

    Return the area of the largest submatrix within matrix where every element
    of the submatrix is 1 after reordering the columns optimally.

    ============================================================
    FUNCTION: int largestSubmatrix(vector<vector<int>>& matrix);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
    Output: 4
    Explanation: You can rearrange the columns as shown above.
    The largest submatrix of 1s, in bold, has an area of 4.


    --- Example 2 ---
    Input: matrix = [[1,0,1,0,1]]
    Output: 3
    Explanation: You can rearrange the columns as shown above.
    The largest submatrix of 1s, in bold, has an area of 3.


    --- Example 3 ---
    Input: matrix = [[1,1,0],[1,0,1]]
    Output: 2
    Explanation: Notice that you must rearrange entire columns, and there is no
                 way to make a submatrix of 1s larger than an area of 2.


    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m * n <= 10^5
    matrix[i][j] is either 0 or 1.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 92.52% */
/* Space Beats: 66.44% */

/* Time  Complexity: O(M * N * logN) */
/* Space Complexity: O(M * N)        */
class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& mat)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int ROWS = mat.size();
        const int COLS = mat[0].size();

        int result = 0;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (mat[i][j] != 0 and i != 0)
                    mat[i][j] += mat[i-1][j];
            }

            vector<int>tmp = mat[i];

            // Sort in DESCENDING order
            sort(tmp.begin(), tmp.end(), greater());

            for (int j = 0; j < COLS; j++)
            {
                result = max(result, tmp[j] * (j+1));
            }
        }

        return result;
    }
};
