#include <iostream>
#include <vector>
#include <functional>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    74) Search a 2D Matrix
    ===========================

    ============
    Description:
    ============

    Write an efficient algorithm that searches for a value "target" in an
    "m x n" integer matrix "matrix". This matrix has the following properties.

    - Integers in each row are sorted from left to right.

    - The first integer of each row is greater than the last integer of the
      previous row.

    =====================================================================
    FUNCTION: bool searchMatrix(vector<vector<int>>& matrix, int target);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  matrix = [[1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 60]], target = 3
    Output: true

    --- Example 2 ---
    Input:  matrix = [[1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 60]], target = 13
    Output: false

    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 100
    -10^4 <= matrix[i][j], target <= 10^4

*/


/*
    ------------
    --- IDEA ---
    ------------

    First check if target is within the last row since we're doing a Vertical
    Binary Search on 0-th column, thus elements of the last row aren't checked.

    If it is within the last row:
        Binary Search Horizontally.

    Otherwise:
        Binary Search Vertically.
        Binary Search Horizontally.

    Theoricatically this Solution should be more efficient in Time than the one
    below but, somehow, LeetCode doesn't account that. They are both beating
    100% of accepted Solutions.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

    There aren't any "tricks" for this problem. Just think logically and you'll
    notice that 2 Binary Searches are the most optimal Solution.

*/

/* Time  Beats: 100% */
/* Space Beats: 8.63% */

/* Time  Complexity: O(log(m * n)) */
/* Space Complexity: O(1) */
class Solution_Bin_Search_1 {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target)
    {
        int m = matrix.size();
        int n = matrix[0].size();

        if (target < matrix[0][0] || target > matrix[m - 1][n - 1])
            return false;

        /* Lambda for Binary Search through Columns in a correct Row */
        std::function<bool(int)> binary_search;
        binary_search = [&](int row) -> bool
        {
            int left  = 0;
            int right = n-1;

            while (left <= right)
            {
                int mid = left + (right - left) / 2;

                if (matrix[row][mid] == target)
                    return true;

                if (matrix[row][mid] < target)
                    left  = mid + 1;
                else
                    right = mid - 1;
            }

            return false;
        };

        int top = 0;
        int bot = m-1;

        /* Binary Search through Rows */
        while (top <= bot)
        {
            int mid = top + (bot - top) / 2;

            if (matrix[mid][n-1] < target)
                top = mid + 1;
            else if(target < matrix[mid][0])
                bot = mid - 1;
            else
                return binary_search(mid);
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Equivalent to the above one, but I think this one is much more easier to
    read.

*/

/* Time  Beats: 73.05% */
/* Space Beats: 19.75% */

/* Time  Complexity: O(log(m * n)) */
/* Space Complexity: O(1)          */
class Solution_Bin_Search_2 {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target)
    {
        int ROWS = matrix.size();
        int COLS = matrix[0].size();

        int up   = 0;
        int down = ROWS-1;

        while (up <= down)
        {
            int mid = up + (down - up) / 2;

            if (matrix[mid][0] <= target && target <= matrix[mid][COLS-1])
                return bin_search_row(matrix[mid], target);

            if (target < matrix[mid][0])
                down = mid - 1;
            else
                up = mid + 1;
        }

        return false;
    }

private:
    bool bin_search_row(std::vector<int>& row, int& target)
    {
        int COLS = row.size();

        int left  = 0;
        int right = COLS-1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (row[mid] == target)
                return true;

            if (row[mid] < target)
                left  = mid + 1;
            else
                right = mid - 1;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Since integers are sorted from left to right and since the first integer of
    each row is greater than the last integer of the previous row, we don't
    have to search through an entire matrix.

    We iterater through 'm' rows and we're checking if our target is within the
    range of current row.
    How do we do that?

    Well, since it is sorted from left to right, just check if target is
    greater than or equal to matrix[current_row][0] and if target is less than
    or equal to matrix[current_row][n - 1].
    (where n is the number of column in entire matrix)

    If we find a row that fulfills these statements then iterate through that
    entire row.
    If you find it, return true, if not return false.

    Also, at the very beginning we can check if the target is less than our
    matrix[0][0] element or if it is greater than our matrix[m][n] element.

    In either case, return false since the target is certainly not inside of
    matrix.

*/

/* Time  Beats:   100% */ // I have no idea how is this one faster
/* Space Beats: 96.94% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(1) */
class Solution_Somehow_Most_Efficient {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target)
    {
        int m = matrix.size();
        int n = matrix[0].size();

        if (target < matrix[0][0] || target > matrix[m - 1][n - 1])
            return false;

        for (int i = 0; i < m; i++)
        {
            if (matrix[i][0] <= target && target <= matrix[i][n - 1])
            {
                for (int j = 0; j < n; j++)
                {
                    if (matrix[i][j] == target)
                        return true;
                }

                return false;
            }
        }

        return false;
    }
};


void
print_matrix(std::vector<std::vector<int>>& matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        std::cout << "\n\n\t\t";

        for (int j = 0; j < matrix[0].size(); j++)
            printf("%2d ", matrix[i][j]);
    }
    std::cout << "\n\n";
}


int
main()
{
    Solution_Bin_Search_1           sol_bin_search_1;
    Solution_Bin_Search_2           sol_bin_search_2;
    Solution_Somehow_Most_Efficient sol_most_efficient;

    /* Example 1 */
    std::vector<std::vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target = 3;

    /* Example 2 */
    // std::vector<std::vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    // int target = 13;

    /* Example 3 */
    // std::vector<std::vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    // int target = 87;

    /* Example 4 */
    // std::vector<std::vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    // int target = -2;

    /* Example 5 */
    // std::vector<std::vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    // int target = 16;

    std::cout << "\n\t==========================";
    std::cout << "\n\t=== SEARCH A 2D MATRIX ===";
    std::cout << "\n\t==========================\n\n";


    /* Write Input */
    std::cout << "\n\tMatrix:";
    print_matrix(matrix);
    std::cout << "\n\tTarget: " << target << "\n";


    /* Solution */
    // bool found = sol_bin_search_1.searchMatrix(matrix, target);
    bool found = sol_bin_search_2.searchMatrix(matrix, target);
    // bool found = sol_most_efficient.searchMatrix(matrix, target);


    /* Write Output */
    if (found)
        std::cout << "\n\n\tOutput: True\n\n";
    else
        std::cout << "\n\n\tOutput: False\n\n";

    return 0;
}
