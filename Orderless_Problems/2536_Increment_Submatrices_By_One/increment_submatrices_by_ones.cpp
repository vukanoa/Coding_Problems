/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    2536) Increment Submatrices by One
    ==================================

    ============
    Description:
    ============

    You are given a positive integer n, indicating that we initially have an n
    x n 0-indexed integer matrix mat filled with zeroes.

    You are also given a 2D integer array query. For each query[i] = [row1i,
    col1i, row2i, col2i], you should do the following operation:

        + Add 1 to every element in the submatrix with the top left corner
          (row1i, col1i) and the bottom right corner (row2i, col2i). That is,
          add 1 to mat[x][y] for all row1i <= x <= row2i and col1i <= y <=
          col2i.

    Return the matrix mat after performing every query.

    ===================================================================================
    FUNCTION: vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries);
    ===================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
    Output: [[1,1,0],[1,2,1],[0,1,1]]
    Explanation: The diagram above shows the initial matrix, the matrix after the first query, and the matrix after the second query.
    - In the first query, we add 1 to every element in the submatrix with the top left corner (1, 1) and bottom right corner (2, 2).
    - In the second query, we add 1 to every element in the submatrix with the top left corner (0, 0) and bottom right corner (1, 1).

    --- Example 2 ---
    Input: n = 2, queries = [[0,0,1,1]]
    Output: [[1,1],[1,1]]
    Explanation: The diagram above shows the initial matrix and the matrix after the first query.
    - In the first query we add 1 to every element in the matrix.

    *** Constraints ***
    1 <= n <= 500
    1 <= queries.length <= 10^4
    0 <= row1i <= row2i < n
    0 <= col1i <= col2i < n

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    According to Constraints, we are indeed allowed to literally "Simulate" the
    Description and Submit that as a Solution.

    It works, but it's not the most optimal way of solving this problem.


*/

/* Time  Beats: 21.63% */
/* Space Beats: 89.34% */

/* Time  Complexity: O(QUERIES_SIZE * n^2) */
/* Space Complexity: O(1)                  */ // "mat" is not "Extra space"
class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries)
    {
        const int QUERIES_SIZE = queries.size();
        vector<vector<int>> mat(n, vector<int>(n, 0));

        for (int i = 0; i < QUERIES_SIZE; i++)
        {
            const int TOP_ROW = queries[i][0];
            const int TOP_COL = queries[i][1];

            const int BOT_ROW = queries[i][2];
            const int BOT_COL = queries[i][3];

            for (int row = TOP_ROW; row <= BOT_ROW; row++)
            {
                for (int col = TOP_COL; col <= BOT_COL; col++)
                {
                    mat[row][col]++;
                }
            }
        }

        return mat;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    2D Line-Sweep technique.

*/

/* Time  Beats: 82.76% */
/* Space Beats: 75.24% */

/* Time  Complexity: O(N^2 + QUERIES_SIZE) */
/* Space Complexity: O(N)                  */ // For extra row and columns
class Solution_2D_Line_Sweep {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries)
    {
        const int QUERIES_SIZE = queries.size();

        vector<vector<int>> mat(n + 1, vector<int>(n + 1, 0));

        for (int i = 0; i < QUERIES_SIZE; i++)
        {
            int top_row = queries[i][0];
            int top_col = queries[i][1];

            int bot_row = queries[i][2];
            int bot_col = queries[i][3];

            mat[top_row    ][top_col    ]++;
            mat[top_row    ][bot_col + 1]--;
            mat[bot_row + 1][top_col    ]--;
            mat[bot_row + 1][bot_col + 1]++; // Diagonal correction
        }

        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                if (row-1 >= 0) mat[row][col] += mat[row-1][col  ];
                if (col-1 >= 0) mat[row][col] += mat[row  ][col-1];

                if (row-1 >= 0 && col-1 >= 0) // Diagonal(upper-left)
                    mat[row][col] -= mat[row-1][col-1];
            }

            // Remove extra column used for difference array
            mat[row].pop_back();
        }

        // Remove extra row used for difference array
        mat.pop_back();

        return mat;
    }
};
