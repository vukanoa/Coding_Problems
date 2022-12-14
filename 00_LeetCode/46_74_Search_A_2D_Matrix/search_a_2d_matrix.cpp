#include <iostream>
#include <vector>


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

	I
*/



/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
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
	Solution sol;

	std::cout << "\n\t==========================";
	std::cout << "\n\t=== SEARCH A 2D MATRIX ===";
	std::cout << "\n\t==========================\n\n";

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

	std::cout << "\n\tMatrix:";
	print_matrix(matrix);
	std::cout << "\n\tTarget: " << target << "\n";


	if (sol.searchMatrix(matrix, target))
		std::cout << "\n\n\tOutput: True\n\n";
	else
		std::cout << "\n\n\tOutput: False\n\n";

	return 0;
}
