#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	============================================
	378) Kth Smallest Element In A Sorted Matrix
	============================================

	============
	Description:
	============

	Given an n x n matrix where each of the rows and columns is sorted in
	ascending order, return the kth smallest element in the matrix.

	Note that it is the kth smallest element in the sorted order, not the kth
	distinct element.

	You must find a solution with a memory complexity better than O(n^2).


	Follow up:
		Could you solve the problem with a constant memory
		(i.e., O(1) memory complexity)?

		Could you solve the problem in O(n) time complexity? The solution may
		be too advanced for an interview but you may find reading this paper
		fun.

	==============================================================
	FUNCTION: int kthSmallest(vector<vector<int>>& matrix, int k);
	==============================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
	Output: 13
	Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15],
	             and the 8th smallest number is 13


	--- Example 2 ---
	Input: matrix = [[-5]], k = 1
	Output: -5



	*** Constraints ***
    n == matrix.length == matrix[i].length

    1 <= n <= 300

    -10^9 <= matrix[i][j] <= 10^9

    All the rows and columns of matrix are guaranteed to be sorted in
	non-decreasing order.

    1 <= k <= n^2

*/

/* Time  Beats: 95.37% */
/* Space Beats: 85.59% */

/* Time  Complexity: O(n * log(max_val - min_val)) */
/* Space Complexity: O(1) */
class Solution{
public:
	int kthSmallest(std::vector<std::vector<int>>& matrix, int k)
	{
		int rows = matrix.size();
		int cols = matrix[0].size();

		int low  = matrix[0][0];
		int high = matrix[rows - 1][cols - 1];

		while (low < high)
		{
			int mid = std::floor((high - low) / 2 + low);
			int cnt = count(matrix, k , mid);

			if (cnt >= k)
				high = mid;
			else
				low = mid + 1;
		}

		return low;
	}

private:
	// O(n), but we could improve it to be O(log n)
	int count(std::vector<std::vector<int>>& matrix, int k, int mid)
	{
		int cnt = 0;
		int rows = matrix.size();
		int cols = matrix[0].size();
		
		for (int i = 0; i < rows; i++)
		{
			for (int j = cols - 1; j >= 0; j--)
			{
				if (matrix[i][j] <= mid)
				{
					cnt += j + 1;
					break;
				}
			}
		}

		return cnt;
	}
};
