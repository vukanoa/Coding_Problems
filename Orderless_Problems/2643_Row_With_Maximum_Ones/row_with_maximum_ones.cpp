/*
    ============
    === EASY ===
    ============

    ===========================
    2643) Row With Maximum Ones
    ===========================

    ============
    Description:
    ============

    Given a m x n binary matrix mat, find the 0-indexed position of the row
    that contains the maximum count of ones, and the number of ones in that
    row.

    In case there are multiple rows that have the maximum count of ones, the
    row with the smallest row number should be selected.

    Return an array containing the index of the row, and the number of ones in
    it.

    ==================================================================
    FUNCTION: vector<int> rowAndMaximumOnes(vector<vector<int>>& mat);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: mat = [[0,1],[1,0]]
    Output: [0,1]
    Explanation: Both rows have the same number of 1's. So we return the index
                 of the smaller row, 0, and the maximum count of ones (1). So,
                 the answer is [0,1]. 

    --- Example 2 ---
    Input: mat = [[0,0,0],[0,1,1]]
    Output: [1,2]
    Explanation: The row indexed 1 has the maximum count of ones (2). So we
                 return its index, 1, and the count. So, the answer is [1,2].

    --- Example 3 ---
    Input: mat = [[0,0],[1,1],[0,0]]
    Output: [1,2]
    Explanation: The row indexed 1 has the maximum count of ones (2). So the
                 answer is [1,2].


    *** Constraints ***
    m == mat.length 
    n == mat[i].length 
    1 <= m, n <= 100 
    mat[i][j] is either 0 or 1.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats:  8.96% */
/* Space Beats: 35.25% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution {
public:
    vector<int> rowAndMaximumOnes(vector<vector<int>>& mat)
    {
        const int ROWS = mat.size();
        const int COLS = mat[0].size();

        vector<int> result = {-1, -1};

        for (int row = 0; row < ROWS; row++)
        {
            int count = 0;
            for (int col = 0; col < COLS; col++)
            {
                if (mat[row][col] == 1)
                    count++;
            }

            if (count > result[1])
            {
                result = {row, count};
            }
        }

        return result;
    }
};
