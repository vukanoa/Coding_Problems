#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2326) Spiral Matrix IV
    ===========================

    ============
    Description:
    ============

    You are given two integers m and n, which represent the dimensions of a matrix.

    You are also given the head of a linked list of integers.

    Generate an m x n matrix that contains the integers in the linked list
    presented in spiral order (clockwise), starting from the top-left of the
    matrix. If there are remaining empty spaces, fill them with -1.

    Return the generated matrix.

    =========================================================================
    FUNCTION: vector<vector<int>> spiralMatrix(int m, int n, ListNode* head);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
    Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
    Explanation: The diagram above shows how the values are printed in the matrix.
    Note that the remaining spaces in the matrix are filled with -1.

    --- Example 2 ---
    Input: m = 1, n = 4, head = [0,1,2]
    Output: [[0,1,2,-1]]
    Explanation: The diagram above shows how the values are printed from left
                 to right in the matrix.  The last space in the matrix is set
                 to -1.


    *** Constraints ***
    1 <= m, n <= 10^5
    1 <= m * n <= 10^5
    The number of nodes in the list is in the range [1, m * n].
    0 <= Node.val <= 1000

*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  5.53% */
/* Space Beats: 82.17% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M * N) */
class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head)
    {
        vector<vector<int>> matrix(m, vector<int>(n, -1));

        int top_row      = 0;
        int bottom_row   = m - 1;
        int left_column  = 0;
        int right_column = n - 1;

        while (head)
        {
            // Fill top row
            for (int col = left_column; col <= right_column && head; ++col)
            {
                matrix[top_row][col] = head->val;
                head = head->next;
            }
            top_row++;

            // Fill right column
            for (int row = top_row; row <= bottom_row && head; ++row)
            {
                matrix[row][right_column] = head->val;
                head = head->next;
            }
            right_column--;

            // Fill bottom row
            for (int col = right_column; col >= left_column && head; --col)
            {
                matrix[bottom_row][col] = head->val;
                head = head->next;
            }
            bottom_row--;

            // Fill left column
            for (int row = bottom_row; row >= top_row && head; --row)
            {
                matrix[row][left_column] = head->val;
                head = head->next;
            }
            left_column++;
        }

        return matrix;
    }
};
