#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	73) Set Matrix Zeroes
	===========================

	============
	Description:
	============

	Given an "m x n" integer matrix "matrix", if an element is 0, set its
	entire row and column to 0's.

	=====
	Node: You must do it in place.
	=====

	======================================================
	FUNCTION: void setZeroes(vector<vector<int>>& matrix);
	======================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  matrix = [[1, 1, 1], [1, 0, 1], [1, 1, 1]]
	Output: [[1, 0, 1], [0, 0, 0], [1, 0, 1]]

	--- Example 2 ---
	Input:  matrix = [[0, 1, 2, 0], [3, 4, 5, 2], [1, 3, 1, 5]]
	Output: [[0, 0, 0, 0], [0, 4, 5, 0], [0, 3, 1, 0]]

	*** Constraints ***
	m == matrix.lenght
	n == matrix[0].length
	1 <= m, n <= 200
	-2^31 <= matrix[i][j] <= 2^31 - 1

*/


/*
	------------
	--- IDEA ---
	------------

	Since we should be doing it in place, another-matrix-solution is out.

	Idea is that if we find out that, for example, matrix[4][3] == 0, then that
	means we should be nullifying entire row[4] as well as entire column[3];

	So what we do is we just remember row index in 0th row and we remember
	column index in 0th column.
	Afterwards we're going to nullify entire rows and columns based on those
	indicators in 0th row and 0th column.

	First we iterate through 0th(first) row. If we find that there is a 0
	somewhere in it, we remember that in variable "zero_row".
	We only need to know if there is any zero in 0th row(without matrix[0][0]).

	Then we iterate through 0th(first) column. If we find that there is a 0
	somewhere in it, we remember that in variable "zero_col".
	We only need to know if there is any zero in 0th col(without matrix[0][0]).

	It's important to note that in both iterations we're iterating starting
	from index 1 and not 0.

	Why?

	Because at the very end we will just check if that element is 0, if it is
	we don't care about these 2 boolean values since we are going to nullify
	both first row and first column.

	After that we just set 0's in 0th row and column based on values in our
	submatrix matrix[1][1] - matrix[m][n].

	Then iterate through the 0th row (from index 1 again) and if we find a 0
	value, nullify that entire column.

	Then iterate through the 0th col (from index 1 again) and if we find a 0
	value, nullify that entire ow.

	After we finish that, now we check if matrix[0][0] == 0. If it is then
	nullify both 0th row and 0th column.

	If it is not, then our "zero_row" and "zero_col" boolean variables come in
	play.

	We nullify 0th row if "zero_row" is true.
	We nullify 0th col if "zero_col" is true.

*/


/* Time  Beats: 91.63% */
/* Space Beats: 99.74% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(1) */
class Solution {
public:
    void nullify_row(std::vector<std::vector<int>>&matrix, int n, int x)
    {
        for (int i = 0; i < n; i++)
            matrix[x][i] = 0;
    }

    void nullify_col(std::vector<std::vector<int>>& matrix, int m, int x)
    {
        for (int i = 0; i < m; i++)
            matrix[i][x] = 0;
    }

    void setZeroes(std::vector<std::vector<int>>& matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();

        if (m == 1 && n == 1)
            return;

        bool zero_row = false;
        bool zero_col = false;

        // We don't check matrix[0][0], we'll take care of that at the end

        // Check first row
        for (int i = 1; i < n; i++)
        {
            if (matrix[0][i] == 0)
            {
                zero_row = true;
                break;
            }
        }

        // Check first column
        for (int i = 1; i < m; i++)
        {
            if (matrix[i][0] == 0)
            {
                zero_col = true;
                break;
            }
        }


		// Check the rest of the matrix (Submatrix matrix[1][1] - matrix[m][n])
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }

        // Nullify certain rows
        for (int i = 1; i < m; i++)
        {
            if (matrix[i][0] == 0)
                nullify_row(matrix, n, i);
        }

        // Nullify certain columns
        for (int i = 1; i < n; i++)
        {
            if (matrix[0][i] == 0)
                nullify_col(matrix, m, i);
        }

		// We're taking care of it here
        if (matrix[0][0] == 0)
        {
            nullify_row(matrix, n, 0);
            nullify_col(matrix, m, 0);
        }
        else
        {
            if (zero_row)
                nullify_row(matrix, n, 0);

            if (zero_col)
                nullify_col(matrix, m, 0);
        }
    }
};


void
print_matrix(std::vector<std::vector<int>>& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		std::cout << "\n\n\t\t\t";

		for (int j = 0; j < matrix[0].size(); j++)
			printf("%2d ", matrix[i][j]);
	}
	std::cout << "\n\n";
}


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<std::vector<int>> matrix = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};

	/* Example 2 */
	// std::vector<std::vector<int>> matrix = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};

	/* Example 3 */
	// std::vector<std::vector<int>> matrix = {{7, 2, 3, 1}, {3, 0, 8, 4}, {0, 2, 0, 9}};

	/* Example 4 */
	std::vector<std::vector<int>> matrix = {{7, 2, 3, 1, 2}, {3, 1, 8, 4, 0}, {6, 3, 2, 7, 4}, {8, 0, 2, 2, 5}};

	std::cout << "\n\t=========================";
	std::cout << "\n\t=== SET MATRIX ZEROES ===";
	std::cout << "\n\t=========================\n\n";


	/* Write Input */
	std::cout << "\n\tOriginal Matrix:";
	print_matrix(matrix);


	/* Solution */
	sol.setZeroes(matrix);


	/* Write Output */
	std::cout << "\n\n\n\tZeroed Matrix:";
	print_matrix(matrix);


	return 0;
}
