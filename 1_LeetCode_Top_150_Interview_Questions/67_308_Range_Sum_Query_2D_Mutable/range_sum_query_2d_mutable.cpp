#include <iostream>

/*
	============
	=== HARD ===
	============

	===============================
	308) Range Sum Query 2D Mutable
	===============================

	============
	Description:
	============

	Given a 2D matrix, find the sum of the elements inside the rectangle
	defined by its upper left corner (row1, col1) and lower right corner (row2,
	col2). And the elements of the matrix could be changed.

	You have to implement three functions:

		- NumMatrix(matrix) The constructor.

		- sumRegion(row1, col1, row2, col2) Return the sum of the elements
		  inside the rectangle defined by its upper left corner (row1, col1)
		  and lower right corner (row2, col2).

		- update(row, col, val) Update the element at (row, col) to val.

	===============================
	CLASS: 
	class NumMatrix {
	public:
		NumMatrix(vector<vector<int>> matrix) {
			
		}
		
		void update(int row, int col, int val) {
			
		}
		
		int sumRegion(int row1, int col1, int row2, int col2) {
			
		}
	};
	===============================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:

		NumMatrix = [[3,0,1,4,2],
					[5,6,3,2,1],
					[1,2,0,1,5],
					[4,1,0,1,7],
					[1,0,3,0,5]]

		sumRegion(2,1,4,3)
		update(3,2,2)
		sumRegion(2,1,4,3)

	Output:
	8
	10




	--- Example 2 ---
	Input:
		NumMatrix = [[1]]

		sumRegion(0, 0, 0, 0)
		update(0, 0, -1)
		sumRegion(0, 0, 0, 0)

	Output:
	1
	-1

	*** Constraints ***
	<Unkown>

*/


// This Solution gives Time Limit Exceeded
class NumMatrix_TLE {
public:
    NumMatrix(std::vector<std::vector<int>> matrix) : matrix(matrix)
	{}
    
    void update(int row, int col, int val)
	{
        matrix[row][col] = val;
    }
    
    int sumRegion(int row1, int col1, int row2, int col2)
	{
		int sum = 0;

		for (int i = row1; i < row2 + 1; i++)
		{
			for (int j = col1; j < col2 + 1; j++)
			{
				sum += matrix[i][j];
			}
		}

		return sum;
    }

private:
	std::vector<std::vector<int>> matrix;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */




/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 96.43% */
/* Space Beats: 54.05% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class NumMatrix {
public:
	std::vector<std::vector<int>> sums;

	NumMatrix(std::vector<std::vector<int>>& matrix)
	{
		if (matrix.size() == 0)
			return;

		sums = std::vector<std::vector<int>>(matrix.size(), std::vector<int>(matrix[0].size(), 0));
		for (int i = 0; i < matrix.size(); ++i)
		{
			int sum = 0;

			for (int j = 0; j < matrix[0].size(); ++j)
			{
				sum += matrix[i][j];
				sums[i][j] = sum;
			}
		}

		for (int j = 0; j < matrix[0].size(); ++j)
		{
			for (int i = 1; i < matrix.size(); ++i)
			{
				sums[i][j] += sums[i-1][j];
			}
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2)
	{
		if (row1 == 0 && col1 == 0)
			return sums[row2][col2];
		else if (row1 == 0)
			return sums[row2][col2] - sums[row2][col1 - 1];
		else if (col1 == 0)
			return sums[row2][col2] - sums[row1 - 1][col2];
		else
			return sums[row2][col2] - sums[row2][col1 - 1] - sums[row1 - 1][col2] + sums[row1 - 1][col1 - 1];
	}
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */
