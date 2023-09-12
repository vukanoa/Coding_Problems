#include <iostream>
#include <vector>


/*
	==============
	=== MEDIUM ===
	==============

	===========================
	54) Spiral Matrix
	===========================

	============
	Description:
	============

	Given an m x n matrix, return all elements of the matrix in spiral order.

	===============================================================
	FUNCTION: vector<int> spiralOrder(vector<vector<int>>& matrix);
	===============================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
	Output: [1, 2, 3, 6, 9, 8, 7, 4, 5]

	--- Example 2 ---
	Input:  matrix = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]]
	Output: [1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7]

	*** Constraints ***
	m == matrix.length
	n == matrix[i].length
	1 <= m, n <= 10
	-100 <= matrix[i][j] <= 100

*/

/*
	------------
	--- IDEA ---
	------------

	Idea is self-explanatory. Thought it is hard to get the implementation
	right.

	Essentially we are solving rectangle by rectangle.

*/

/* Time  Beats:   100% */
/* Space Beats: 28.09% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(1) */
class Solution {
public:
	std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix)
	{
		int m = matrix.size();
		int n = matrix[0].size();

		std::vector<int> results;

		int left  = 0;
		int right = n;

		int top    = 0;
		int bottom = m;

		while (left < right && top < bottom)
		{
			// Top Row: Left to Right
			for (int i = left; i < right; i++)
				results.push_back(matrix[top][i]);
			top++;

			// Right Side: Top to Bottom
			for (int i = top; i < bottom; i++)
				results.push_back(matrix[i][right-1]);
			right--;

			/* Consider one-row matrix or one-column matrix */
			// if (left >= right || top >= bottom)
			if (!(left < right && top < bottom))
				break;

			// Bottom Row: Right to Left
			for (int i = right-1; i >= left; i--)
				results.push_back(matrix[bottom-1][i]);
			bottom--;

			// Left Side: Bottom to Top
			for (int i = bottom-1; i >= top; i--)
				results.push_back(matrix[i][left]);
			left++;
		}

		return results;
	}
};


void
print_matrix(std::vector<std::vector<int>>& matrix)
{
	printf("\tMatrix:\n\t\t");
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
			printf("%2d ", matrix[i][j]);

		printf("\n\t\t");
	}
	printf("\n");
}


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<std::vector<int>> matrix = {
	                                        { 1,  2,  3},
	                                        { 4,  5,  6},
	                                        { 7,  8,  9},
	                                       };


	/* Example 2 */
	// std::vector<std::vector<int>> matrix = {
	//                                         { 1,  2,  3, 4},
	//                                         { 5,  6,  7, 8},
	//                                         { 9, 10, 11, 12},
	//                                        };


	/* Example 3 */
	// std::vector<std::vector<int>> matrix = {
	//                                         { 1,  2,  3,  4,  5},
	//                                         { 6,  7,  8,  9, 10},
	//                                         {11, 12, 13, 14, 15},
	//                                         {16, 17, 18, 19, 20}
	//                                        };


	std::cout << "\n\t=====================";
	std::cout << "\n\t=== SPIRAL MATRIX ===";
	std::cout << "\n\t=====================\n\n";


	/* Write Input */
	print_matrix(matrix);


	/* Solution */
	std::vector<int> order = sol.spiralOrder(matrix);


	/* Write Output */
	std::cout << "\n\tSpiral order:\n\t\t ";
	for(const auto& x : order)
		std::cout << x << " ";

	std::cout << "\n\n\n";

	return 0;
}
