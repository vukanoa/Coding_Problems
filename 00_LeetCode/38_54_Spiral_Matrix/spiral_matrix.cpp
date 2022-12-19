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



/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n * m) */
class Solution{
public:
	std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix)
	{
		int m = matrix.size();
		int n = matrix[0].size();

		// Base case
		if (matrix.size() == 1)
			return {matrix[0]};

		/*
			0 - to the right
			1 - downwards
			2 - to the left
			3 - upwards
		*/
		unsigned direction = 0;
		std::vector<int> starts = {0,  1, n - 2, m - 2};
		std::vector<int> ends   = {n,  m,   0  ,   1  };

		std::vector<int> order;
		int traversed = 0;
		int i;

		while (traversed < matrix.size() * matrix[0].size())
		{
			switch (direction)
			{
				case 0:
					i = starts[direction];
					while (i < ends[direction])
					{
						order.push_back(matrix[starts[direction]][i++]);
						traversed++;
					}

					starts[direction]++;
					ends[direction]--;
					break;

				case 1:
					i = starts[direction];
					while (i < ends[direction])
					{
						order.push_back(matrix[i++][ends[0]]);
						traversed++;
					}

					starts[direction]++;
					ends[direction]--;
					break;

				case 2:
					i = starts[direction];
					while (i >= ends[direction])
					{
						order.push_back(matrix[ends[1]][i--]);
						traversed++;
					}

					starts[direction]--;
					ends[direction]++;
					break;

				case 3:
					i = starts[direction];
					while (i >= ends[direction])
					{
						order.push_back(matrix[i--][ends[2] - 1]);
						traversed++;
					}

					starts[direction]--;
					ends[direction]++;
					break;
			}

			direction = (direction + 1) % 4;
		}

		return order;
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


	print_matrix(matrix);
	std::vector<int> order = sol.spiralOrder(matrix);

	std::cout << "\n\tSpiral order:\n\t\t ";
	for(const auto& x : order)
		std::cout << x << " ";

	std::cout << "\n\n\n";

	return 0;
}
