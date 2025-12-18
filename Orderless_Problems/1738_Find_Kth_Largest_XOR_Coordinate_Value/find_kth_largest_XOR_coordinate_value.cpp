/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1738) Find Kth Largest XOR Coordinated Value
    ============================================

    ============
    Description:
    ============

    You are given a 2D matrix of size m x n, consisting of non-negative
    integers. You are also given an integer k.

    The value of coordinate (a, b) of the matrix is the XOR of all matrix[i][j]
    where 0 <= i <= a < m and 0 <= j <= b < n (0-indexed).

    Find the kth largest value (1-indexed) of all the coordinates of matrix.

    ==================================================================
    FUNCTION: int kthLargestValue(vector<vector<int>>& matrix, int k);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matrix = [[5,2],[1,6]], k = 1
    Output: 7
    Explanation: The value of coordinate (0,1) is 5 XOR 2 = 7, which is the
                 largest value.

    --- Example 2 ---
    Input: matrix = [[5,2],[1,6]], k = 2
    Output: 5
    Explanation: The value of coordinate (0,0) is 5 = 5, which is the 2nd
                 largest value.

    --- Example 3 ---
    Input: matrix = [[5,2],[1,6]], k = 3
    Output: 4
    Explanation: The value of coordinate (1,0) is 5 XOR 1 = 4, which is the 3rd
                 largest value.

    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 1000
    0 <= matrix[i][j] <= 10^6
    1 <= k <= m * n

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 46.67% */
/* Space Beats: 41.67% */

/* Time  Complexity: O(ROWS * COLS * log(ROWS * COLS)) */
/* Space Complexity: O(ROWS * COLS)                    */
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        priority_queue<int> max_heap;
        max_heap.push(matrix[0][0]);

        for (int col = 1; col < COLS; col++)
        {
            matrix[0][col] ^= matrix[0][col-1];
            max_heap.push(matrix[0][col]);
        }

        for (int row = 1; row < ROWS; row++)
        {
            matrix[row][0] ^= matrix[row-1][0];
            max_heap.push(matrix[row][0]);
        }

        for (int row = 1; row < ROWS; row++)
        {
            for (int col = 1; col < COLS; col++)
            {
                matrix[row][col] ^= matrix[row-1][col] ^ matrix[row][col-1] ^ matrix[row-1][col-1];
                max_heap.push(matrix[row][col]);
            }
        }

        while (--k > 0)
            max_heap.pop();

        return max_heap.top();
    }
};
