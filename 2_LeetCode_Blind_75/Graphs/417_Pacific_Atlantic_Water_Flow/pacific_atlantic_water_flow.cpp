#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	================================
	417) Pacific Atlantic Water Flow
	================================

	============
	Description:
	============

	There is an m x n rectangular island that borders both the Pacific Ocean
	and Atlantic Ocean. The Pacific Ocean touches the island's left and top
	edges, and the Atlantic Ocean touches the island's right and bottom edges.

	The island is partitioned into a grid of square cells. You are given an m x
	n integer matrix heights where heights[r][c] represents the height above
	sea level of the cell at coordinate (r, c).

	The island receives a lot of rain, and the rain water can flow to
	neighboring cells directly north, south, east, and west if the neighboring
	cell's height is less than or equal to the current cell's height. Water can
	flow from any cell adjacent to an ocean into the ocean.

	Return a 2D list of grid coordinates result where result[i] = [ri, ci]
	denotes that rain water can flow from cell (ri, ci) to both the Pacific and
	Atlantic oceans.

	===========================================================================
	FUNCTION: vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights)
	===========================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---

	                                                           
	                  Pacific ocean
	                                                           
	         +-----+-----+-----+-----+-----+ ~~~~~
	         |  1  |  2  |  2  |  3  |  5  |        
	         +-----+-----+-----+-----+-----+        
	         |  3  |  2  |  3  |  4  |  4  |        
	 Pacific +-----+-----+-----+-----+-----+ Atlantic
	  Ocean  |  2  |  4  |  5  |  3  |  1  |  Ocean 
	         +-----+-----+-----+-----+-----+        
	         |  6  |  7  |  1  |  4  |  5  |        
	         +-----+-----+-----+-----+-----+        
	         |  5  |  1  |  1  |  2  |  4  |        
	   ~~~~~ +-----+-----+-----+-----+-----+        
	                                                           
	                  Atlantic Ocean

	Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
	Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]

	Explanation: The following cells can flow to the Pacific and Atlantic
	             oceans, as shown below:
	[0,4]: [0,4] -> Pacific Ocean 
	       [0,4] -> Atlantic Ocean
	[1,3]: [1,3] -> [0,3] -> Pacific Ocean 
	       [1,3] -> [1,4] -> Atlantic Ocean
	[1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean 
	       [1,4] -> Atlantic Ocean
	[2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean 
	       [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
	[3,0]: [3,0] -> Pacific Ocean 
	       [3,0] -> [4,0] -> Atlantic Ocean
	[3,1]: [3,1] -> [3,0] -> Pacific Ocean 
	       [3,1] -> [4,1] -> Atlantic Ocean
	[4,0]: [4,0] -> Pacific Ocean 
	       [4,0] -> Atlantic Ocean

	Note that there are other possible paths for these cells to flow to the
	Pacific and Atlantic oceans.








	--- Example 2 ---
	Input: heights = [[1]]
	Output: [[0,0]]
	Explanation: The water can flow from the only cell to the Pacific and
	             Atlantic oceans.








	*** Constraints ***
	m == heights.length
	n == heights[r].length
	1 <= m, n <= 200
	0 <= heights[r][c] <= 10^5

*/

/*
	------------
	--- IDEA ---
	------------

	If you try to do it in a naive way, you would do a simple DFS for each
	height in the matrix. However that is very inefficient. The Time Complexity
	of that approach would be O((n * m)^2), which is unacceptable.

	Then you'd maybe think: I can **memoize** paths that I've tried and I can
	use some other matrix, say "indicators" which will have the calculated
	values in it indicating if it's possible to reach either of oceans, both or
	none.

	However that approach is almost impossible to code up. Try it yourself, I
	haven't managed to do it.

	The right way to solve this problem is - First Start from the Pacific ocean
	and do a DFS from 0th row and then do the same for 0th Column and do a DFS
	from each of those heights and mark all the heights that you can reach.

	Second, start from the Atlantic ocean and do a DFS from last row and then
	from last column and, again, do a DFS from each of those heights and mark
	all the heights that you can reach.

	At the end Iterate through all the positions of heights and check if from
	that point both oceans can be reach. If it can - push in vector "results'.

	*******************************
	*** Important thing to note ***
	*******************************

	We're told that if we are on some height, we can't go "up", meaning that
	the water can only flow from that point to height that is either of equal
	height or height that is lower than current height.

	However, that's if you are starting from the height and then going to the
	ocean/s.

	But in this approach, we're doing the exact opposite. We're starting from
	the Ocean/s and then doing a DFS from it, therefore we can continue in a
	certain direction if current heights is LESS than or EQUAL to the one we're
	trying to go on.

	Consider te very first example:

	      0     1     2     3     4
	   +-----+-----+-----+-----+-----+
	0  |  1  |  2  |  2  |  3  |  5  |
	   +-----+-----+-----+-----+-----+
	1  |  3  |  2  |  3  |  4  |  4  |
	   +-----+-----+-----+-----+-----+
	2  |  2  |  4  |  5  |  3  |  1  |
	   +-----+-----+-----+-----+-----+
	3  |  6  |  7  |  1  |  4  |  5  |
	   +-----+-----+-----+-----+-----+
	4  |  3  |  1  |  1  |  2  |  4  |
	   +-----+-----+-----+-----+-----+
	
	Consider heights[2][2], which is 5. From it, we can go to the right. To:
	3, then from 3 we can go to 1 and then from 1 to the Atlantic Ocean.

	We can go from 5 to 3 because 5 is GREATER THAN OR EQUAL TO 3. Similarly, 
	we can go from 3 to 1 because 3 is GREATER THAN OR EQUAL TO 1. And from 1
	we can reach the Atlantic Ocean.


	However, since we're going in the opposite direction, from the last column
	and 2nd row, which is value 1, we can go to the left because now we have to
	do an OPPOSITE check up.

	We can go from 1 to 3 because 1 is LESS THAN OR EQUAL TO 3. Etc.
	
	It's important to notice this.

*/

/* Time  Beats: 95.60% */
/* Space Beats: 89.06% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution {
public:
	// Trick for this problem: Go from outside towards the inside
	std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& heights)
	{
		int m = heights.size();
		int n = heights[0].size();

		std::vector<std::vector<bool>> pacific (m, std::vector<bool>(n, false));
		std::vector<std::vector<bool>> atlantic(m, std::vector<bool>(n, false));

		// First and last Row
		for (int i = 0; i < m; i++)
		{
			dfs(heights, pacific,  i, 0  , heights[i][ 0 ]);
			dfs(heights, atlantic, i, n-1, heights[i][n-1]);
		}
		
		// First and last Column
		for (int j = 0; j < n; j++)
		{
			dfs(heights, pacific,  0,   j, heights[ 0 ][j]);
			dfs(heights, atlantic, m-1, j, heights[m-1][j]);
		}

		// Results
		std::vector<std::vector<int>> results;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (pacific[i][j] && atlantic[i][j]) // If both oceans can be reached from that particular point
					results.push_back({i, j});       // Store it in results
			}
		}

		return results;
	}

private:
	void dfs(std::vector<std::vector<int>>& heights, std::vector<std::vector<bool>>& visited, int i, int j, int prev_height)
	{
		int m = heights.size();
		int n = heights[0].size();

		if (i < 0 || j < 0 || i == m || j == n || visited[i][j] || heights[i][j] < prev_height)
			return;

		visited[i][j] = true;

		dfs(heights, visited, i-1, j  , heights[i][j]); // Up
		dfs(heights, visited, i+1, j  , heights[i][j]); // Down
		dfs(heights, visited, i  , j-1, heights[i][j]); // Left
		dfs(heights, visited, i  , j+1, heights[i][j]); // Right
	}
};
