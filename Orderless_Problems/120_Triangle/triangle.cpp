#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	120) Triangle
	===========================

	============
	Description:
	============

	Given a triangle array, return the minimum path sum from top to bottom.

	For each step, you may move to an adjacent number of the row below. More
	formally, if you are on index i on the current row, you may move to either
	index i or index i + 1 on the next row.

	==========================================================
	FUNCTION: int minimumTotal(vector<vector<int>>& triangle);
	==========================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
	Output: 11
	Explanation: The triangle looks like:
	   2
	  3 4
	 6 5 7
	4 1 8 3
	The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined
	above).


	--- Example 2 ---
	Input: triangle = [[-10]]
	Output: -10


	*** Constraints ***
	1 <= triangle.length <= 200
	triangle[0].length == 1
	triangle[i].length == triangle[i - 1].length + 1
	-104 <= triangle[i][j] <= 104

*/

/* Time  Beats: 100% */
/* Space Beats: 21.32% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution{
public:
	int minimumTotal(std::vector<std::vector<int>>& triangle)
	{
		if (triangle.size() == 1)
			return triangle[0][0];

		std::vector<int> dp;
		dp.push_back(triangle[0][0]);

		int min;
		for (int i = 1; i < triangle.size(); i++)
		{
			std::vector<int> tmp(triangle[i].size());

			min = dp[0] + triangle[i][0];
			for (int j = 0; j < triangle[i].size(); j++)
			{
				tmp[j] = triangle[i][j];

				if (j == 0)
					tmp[j] += dp[0];
				else if (j == triangle[i].size() - 1)
					tmp[j] += dp[triangle[i].size() - 2];
				else
					tmp[j] += std::min(dp[j - 1], dp[j]);

				min = std::min(min, tmp[j]);
			}

			dp = tmp;
		}

		return min;
	}
};
