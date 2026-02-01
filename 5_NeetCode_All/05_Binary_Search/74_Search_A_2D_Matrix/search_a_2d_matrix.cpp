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

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since integers are sorted from left to right and since the first integer of
    each row is greater than the last integer of the previous row, we don't
    have to search through an entire matrix.

    We iterater through each row and we're checking if our target is within the
    range of current row.

    How do we do that?

    Well, since it is sorted from left to right, just check if target is
    greater than or equal to matrix[row][0] and if target is less than or equal
    to matrix[row][COLS - 1].

    If we find a row that fulfills these statements then iterate through that
    entire row.
    If you find it, return true, if not return false.

    Also, at the very beginning we can check if the target is less than our
    matrix[0][0] element or if it is greater than our matrix[ROWS-1][COLS-1]
    element.

    In either case, return false since the target is certainly not inside of
    matrix.

*/

/* Time  Beats:   100% */ // I have no idea how is this one faster
/* Space Beats: 96.94% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(1) */
class Solution_Brute_Force {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        if (target < matrix[0][0] || target > matrix[ROWS - 1][COLS - 1])
            return false;

        for (int row = 0; row < ROWS; row++)
        {
            if (matrix[row][0] <= target && target <= matrix[row][COLS - 1])
            {
                for (int col = 0; col < COLS; col++)
                {
                    if (matrix[row][col] == target)
                        return true;
                }

                return false;
            }
        }

        return false;
    }
};


/*
    ------------
    --- IDEA ---
    ------------

    This one uses "upper_bound" on the rows, and then once we've located a row
    in which it COULD exist, then we do a "lower_bound".

    It's important to note that:

        + upper_bound searches for the first element that is STIRCTLY GREATER
          than the target.

        + lower_bound searches for the first element that is EQUAL TO OR
          GREATER than the target.

    However, it's important to note that we can use "lower_bound" to do an
    "upper_bound". Yes, you read that right.

    How do we do that?

    We simply add 1 to the target and we perform a "lower_bound", that's it.


    This is important because both of our implementations, i.e. both:
        + find_row_upper_bound, and
        + my_lower_bound

    are actually custom implementations of "lower_bound". The only difference
    is that one returns an index, while the other returns true/false based on
    the presence or absence of the target, respectivelly.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  43.36% */

/* Time  Complexity: O(log(ROWS * COLS)) */
/* Space Complexity: O(1)                */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        int row = find_row_upper_bound(0, ROWS-1, matrix, target);

        /* This is VERY important because we performed an UPPER_BOUND  */
        if (row > 0 && target < matrix[row][0])
            row--;

        return my_lower_bound(row, 0, COLS-1, matrix, target);
    }

private:
    /* Upper Bound Function */
    int find_row_upper_bound(int low, int high, vector<vector<int>>& matrix, int& target)
    {
        int new_target = target + 1; // Using this new_target makes this entire
                                     // function "upper_bound"

        /* Lower Bound Implementation */
        while (low < high)
        {
            int mid = low + (high - low) / 2;

            if (new_target > matrix[mid][0])
                low = mid + 1;
            else
                high = mid;
        }

        return high; // Or "low" it does NOT matter
    }

    int my_lower_bound(int row, int low, int high, vector<vector<int>>& matrix, int& target)
    {
        while (low < high)
        {
            int mid = low + (high - low) / 2; // Left-leaning

            if (target > matrix[row][mid])
                low = mid + 1;
            else
                high = mid;
        }

        return matrix[row][high] == target;
    }
};
