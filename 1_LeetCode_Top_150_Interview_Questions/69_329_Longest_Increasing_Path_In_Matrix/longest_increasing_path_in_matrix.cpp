#include <iostream>
#include <vector>
#include <functional> // For Lambda

/*
	============
	=== HARD ===
	============

	======================================
	329) Longest Incresaing Path in Matrix
	======================================

	============
	Description:
	============

	Given an m x n integers matrix, return the length of the longest increasing
	path in matrix.

	From each cell, you can either move in four directions: left, right, up, or
	down. You may not move diagonally or move outside the boundary (i.e.,
	wrap-around is not allowed).

	=================================================================
	FUNCTION: int longestIncreasingPath(vector<vector<int>>& matrix); 
	=================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
	Output: 4
	Explanation: The longest increasing path is [1, 2, 6, 9].


	--- Example 2 ---
	Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
	Output: 4
	Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally
	             is not allowed.


	--- Example 3 ---
	Input: matrix = [[1]]
	Output: 1

	*** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 200
    0 <= matrix[i][j] <= 231 - 1

*/

/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 93.50% */
/* Space Beats: 81.03% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution {
public:
    int longestIncreasingPath(std::vector<std::vector<int>>& matrix)
	{
		int rows = matrix.size();
		int cols = matrix.size();

		std::vector<std::vector<int>> dp(rows, std::vector(cols, -1));

		// DFS(as a lambda so that we don't have to pass other parameters)
		function<int(int, int, int)> dfs = [&](int r, int c, int prev_val)
		{
			if (r < 0 || r == rows ||
				c < 0 || c == cols ||
				matrix[r][c] <= prev_val)
				return 0;

			if (dp[r][c] != -1)
				return dp[r][c];
			
			int res = 1;
			// 1 + dfs(..) to take the current one into account as well
			res = std::max(res, 1 + dfs(r - 1, c    , matrix[r][c])); // Up
			res = std::max(res, 1 + dfs(r + 1, c    , matrix[r][c])); // Down
			res = std::max(res, 1 + dfs(r    , c - 1, matrix[r][c])); // Left
			res = std::max(res, 1 + dfs(r    , c + 1, matrix[r][c])); // Right

			dp[r][c] = res;

			return res;
		};

		int LIP = 0; // Longest increasing path
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				LIP = std::max(LIP, dfs(i, j, -1));
			}
		}

		return LIP;
    }
};




/* Time  Beats: 96.83% */
/* Space Beats: 61.07% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution {
public:
    int longestIncreasingPath(std::vector<std::vector<int>>& matrix)
	{
		int rows = matrix.size();
		int cols = matrix[0].size();

		std::vector<std::vector<int>> dp(rows, std::vector(cols, -1));

		int LIP = 0; // Longest increasing path
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				LIP = std::max(LIP, dfs(matrix, dp, i, j, -1));
			}
		}

		return LIP;
    }

private:
	// DFS(as a lambda so that we don't have to pass other parameters)
	int dfs(std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& dp, int r, int c, int prev_val)
	{
		if (r < 0 || r == matrix.size() || c < 0 || c == matrix[0].size() || matrix[r][c] <= prev_val)
			return 0;

		if (dp[r][c] != -1)
			return dp[r][c];
		
		int res = 1;
		// 1 + dfs(..) to take the current one into account as well
		res = std::max(res, 1 + dfs(matrix, dp, r - 1, c    , matrix[r][c])); // Up
		res = std::max(res, 1 + dfs(matrix, dp, r + 1, c    , matrix[r][c])); // Down
		res = std::max(res, 1 + dfs(matrix, dp, r    , c - 1, matrix[r][c])); // Left
		res = std::max(res, 1 + dfs(matrix, dp, r    , c + 1, matrix[r][c])); // Right

		dp[r][c] = res;

		return res;
	};
};
