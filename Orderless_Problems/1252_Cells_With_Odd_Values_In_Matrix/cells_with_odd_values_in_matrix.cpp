/*
    ============
    === EASY ===
    ============

    =======================================
    1252) Cells with Odd Values in a Matrix
    =======================================

    ============
    Description:
    ============

    There is an m x n matrix that is initialized to all 0's. There is also a 2D
    array indices where each indices[i] = [ri, ci] represents a 0-indexed
    location to perform some increment operations on the matrix.

    For each location indices[i], do both of the following:

        + Increment all the cells on row ri.
        + Increment all the cells on column ci.

    Given m, n, and indices, return the number of odd-valued cells in the
    matrix after applying the increment to all locations in indices.

    ===================================================================
    FUNCTION: int oddCells(int m, int n, vector<vector<int>>& indices);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: m = 2, n = 3, indices = [[0,1],[1,1]]
    Output: 6
    Explanation: Initial matrix = [[0,0,0],[0,0,0]].
    After applying first increment it becomes [[1,2,1],[0,1,0]].
    The final matrix is [[1,3,1],[1,3,1]], which contains 6 odd numbers.

    --- Example 2 ---
    Input: m = 2, n = 2, indices = [[1,1],[0,0]]
    Output: 0
    Explanation: Final matrix = [[2,2],[2,2]]. There are no odd numbers in the
                 final matrix.


    *** Constraints ***
    1 <= m, n <= 50
    1 <= indices.length <= 100
    0 <= ri < m
    0 <= ci < n

*/

#include <bitset>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  69.76% */

/* Time  Complexity: O(indices.size() + m * n) */
/* Space Complexity: O(m + n)                  */
class Solution {
public:
    int oddCells(int m, int n, vector<vector<int>>& indices)
    {
        int odd_count = 0;

        vector<int> row_increments(m, 0);
        vector<int> col_increments(n, 0);

        for (const auto& entry : indices)
        {
            row_increments[entry[0]]++;
            col_increments[entry[1]]++;
        }

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if ((row_increments[i] + col_increments[j]) & 1)
                    odd_count++;
            }
        }

        return odd_count;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  95.25% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int oddCells(int m, int n, vector<vector<int>>& indices)
    {
        bitset<50> rows;
        bitset<50> cols;

        for (const auto& entry : indices)
        {
            rows.flip(entry[0]);
            cols.flip(entry[1]);
        }

        const auto odd_rows = rows.count();
        const auto odd_cols = cols.count();

        return (m - odd_rows) * odd_cols + (n - odd_cols) * odd_rows;
    }
};
