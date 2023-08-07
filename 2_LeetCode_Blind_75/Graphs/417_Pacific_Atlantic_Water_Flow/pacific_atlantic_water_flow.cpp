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

	TODO
	
*/

/* Time  Beats: 98.26% */
/* Space Beats: 88.42% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution {
public:
	std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& heights)
	{
		std::vector<std::vector<int>> res;

		int m = heights.size();
		int n = heights[0].size();

		std::vector<std::vector<bool>> pacific (m + 1, std::vector<bool>(n + 1, false));
		std::vector<std::vector<bool>> atlantic(m + 1, std::vector<bool>(n + 1, false));

		// Check Edges for Pacific ocean
		for(int i = 0; i < m; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(i == 0 || j == 0)
					dfs(i, j, heights, pacific);
			}
		}

		// Check Edges for Atlantic ocean
		for(int i = 0; i < m; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(i == m-1 || j == n-1)
					dfs(i, j, heights, atlantic);
			}
		}

		// If water can flow from a cell in both atlantic and pacific add that to our answer.
		for(int i = 0; i < m; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(atlantic[i][j] == true && pacific[i][j] == true)
					res.push_back({i, j});
			}
		}

		return res;
	}

private:
	void dfs(int i, int j, std::vector<std::vector<int>>& height, std::vector<std::vector<bool>>& ocean)
	{
		int m = height.size();
		int n = height[0].size();

		if (ocean[i][j] == false)
			ocean[i][j] = true;

		// Up
		if(i > 0 && height[i-1][j] >= height[i][j] && ocean[i-1][j] == false)
			dfs(i-1, j, height, ocean);

		// Left
		if(j > 0 && height[i][j-1] >= height[i][j] && ocean[i][j-1] == false)
			dfs(i, j-1, height, ocean);

		// Down
		if(i < m-1 && height[i+1][j] >= height[i][j] && ocean[i+1][j] == false)
			dfs(i+1, j, height, ocean);

		// Right
		if(j < n-1 && height[i][j+1] >= height[i][j] && ocean[i][j+1] == false)
			dfs(i, j+1, height, ocean);
	}
};




/********************************/
/********* Another DFS **********/
/********************************/
/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 99.05% */
/* Space Beats: 77.09% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution {
public:
	// Trick for this problem: Go from outside towards the inside
	std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& heights)
	{
		int m = heights.size();
		int n = heights[0].size();

		std::vector<std::vector<int>> results;

		std::vector<std::vector<bool>> pacific (m, std::vector<bool>(n));
		std::vector<std::vector<bool>> atlantic(m, std::vector<bool>(n));

		for (int i = 0; i < m; i++)
		{
			dfs(heights, pacific,  i, 0);
			dfs(heights, atlantic, i, n-1);
		}
		
		for (int j = 0; j < n; j++)
		{
			dfs(heights, pacific,  0,   j);
			dfs(heights, atlantic, m-1, j);
		}
		
		
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (pacific[i][j] && atlantic[i][j]) // If both occurrences can be reached from that particular point
					results.push_back({i, j});       // Store it in results
			}
		}

		return results;
	}

private:
	void dfs(std::vector<std::vector<int>>& heights, std::vector<std::vector<bool>>& visited, int i, int j)
	{
		int m = heights.size();
		int n = heights[0].size();

		visited[i][j] = true;

		// Up
		if (i-1 >= 0 && visited[i-1][j] != true && heights[i-1][j] >= heights[i][j])
			dfs(heights, visited, i-1, j);

		// Down
		if (i+1 < m && visited[i+1][j] != true && heights[i+1][j] >= heights[i][j])
			dfs(heights, visited, i+1, j);

		// Left
		if (j-1 >= 0 && visited[i][j-1] != true && heights[i][j-1] >= heights[i][j])
			dfs(heights, visited,  i,  j-1);

		// Righeightst
		if (j+1 < n && visited[i][j+1] != true && heights[i][j+1] >= heights[i][j])
			dfs(heights, visited,  i,  j+1);
	}
};
