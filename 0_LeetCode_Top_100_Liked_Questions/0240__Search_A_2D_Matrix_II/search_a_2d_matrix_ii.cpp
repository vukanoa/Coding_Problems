#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    240) Search a 2D Matrix II
    ===========================

    ============
    Description:
    ============

    Write an efficient algorithm that searches for a values "target" in an
    m x n integer matrix "matrix".
    This matrix has the following properties:
        - Integers in each row are sorted in ascending from left to right
        - Integers in each column are sorted in ascending from top to bottom

    =====================================================================
    FUNCTION: bool searchMatrix(vector<vector<int>>& matrix, int target);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  matrix =
    [[1, 4, 7, 11, 15], [2, 5, 8, 12, 19], [3, 6, 9, 16, 22],
    [10, 13, 14, 17, 24], [18, 21, 23, 26, 30]], target = 5
    Output: true

    --- Example 2 ---
    Input:  matrix =
    [[1, 4, 7, 11, 15], [2, 5, 8, 12, 19], [3, 6, 9, 16, 22],
    [10, 13, 14, 17, 24], [18, 21, 23, 26, 30]], target = 20
    Output: false

    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= n, m <= 300
    -10^9 <= matrix[i][j] <= 10^9
    All the integers in each row are sorted in ascending order
    All the integers in each column are sorted in ascending order
    -10^9 <= target <= 10^9

*/


/*

    Yes, you can solve it using two Binary Searches, but that's the idea of the
    first part of this problem. This second, II), part have two different
    important properties:

        - The first integer of each row is NOT necessarily greater than the
          last integer of the previous row.

        - Integers in each column are NOT necessarily in ascending from top to
          bottom.

    So, while you can solve it in Time: O(logM * logN) and Space: O(1), there
    is an infinitely more elegant and superior Solution to that one given these
    two new properties of this problem.

*/


/*
    ------------
    --- IDEA ---
    ------------

    Since elements are sorted in each row and each column, start from the
    top-right element.

    if current element is target:
        return true
    else if current element is less than our target:
        col--; // Move to the previous column
    else if current element is greater than our target:
        row++; // Move "down", to next row

    That's it. That's the whole algorithm.

*/

/* Time  Beats: 20.54% */
/* Space Beats: 88.18% */

/* Time  Complexity: O(m + n) */
/* Space Complexity: O(1) */
class Solution_Readable{
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target)
    {
        if (matrix.empty() || matrix[0].empty())
            return false;

        int m = matrix.size();
        int n = matrix[0].size();

        int row = 0;
        int col = n - 1;

        while (row < m && col >= 0)
        {
            if (target == matrix[row][col])
                return true;
            else if (target < matrix[row][col])
                col--;
            else if (target > matrix[row][col])
                row++;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's the same solution, but with neat little optimizations.

*/

/* Time  Beats: 99.69% */
/* Space Beats: 98.74% */

/* Time  Complexity: O(m + n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target)
    {
        std::ios::sync_with_stdio(0);
        int m = matrix.size();
        int n = matrix[0].size();

        int row = 0;
        int col = n - 1;

        while (row < m && col >= 0)
        {
            if (matrix[row][col] == target)
            {
                matrix.clear();
                return true;
            }
            else if (matrix[row][col] > target)
                col--;
            else
                row++;
        }
        matrix.clear();

        return false;
    }
};


int
main()
{
    Solution_Readable sol_readable;
    Solution          sol;


    /* Example 1 */
    // int target = 5;
    // std::vector<std::vector<int>> matrix =
    // {{ 1,  4,  7, 11, 15},
    //  { 2,  5,  8, 12, 19},
    //  { 3,  6,  9, 16, 22},
    //  {10, 13, 14, 17, 24},
    //  {18, 21, 23, 26, 30}};


    /* Example 2 */
    int target = 20;
    std::vector<std::vector<int>> matrix =
    {{ 1,  4,  7, 11, 15},
     { 2,  5,  8, 12, 19},
     { 3,  6,  9, 16, 22},
     {10, 13, 14, 17, 24},
     {18, 21, 23, 26, 30}};


    std::cout << "\n\t=============================";
    std::cout << "\n\t=== SEARCH A 2D MATRIX II ===";
    std::cout << "\n\t=============================\n";


    /* Write Input */
    std::cout << "\n\tTarget: " << target << "\n";

    bool first = true;
    std::cout << "\n\tMatrix: \n\t\t";
    for (auto x: matrix)
    {
        if (!first)
            std::cout << "\t\t";

        bool first_first = true;
        // std::cout << "[";
        for (const auto& xx : x)
        {
            if (!first_first)
                std::cout << "  ";

            // std::cout << xx;
            printf("%2d", xx);
            first_first = false;
        }
        std::cout << "\n";

        first = false;
    }
    std::cout << "\n";


    /* Solution */
    // bool exist = sol_readable.searchMatrix(matrix, target);
    bool exist = sol.searchMatrix(matrix, target);


    /* Write Output */
    if (exist)
        std::cout << "\n\tOutput: True\n\n";
    else
        std::cout << "\n\tOutput: False\n\n";


    return 0;
}
