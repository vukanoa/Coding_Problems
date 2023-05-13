#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	200) Number of Islands
	===========================

	============
	Description:
	============

	Given an m x n 2D binary grid "grid" which represents a map of '1's(land)
	and '0's(water), return the number of islands.

	An island is surrounded by water and is formed by connecting adjacent lands
	horizontally or vertically. You may assume all four edges of the grid are
	all surrounded by water.

	=====================================================
	FUNCTION: int numIslands(vector<vector<char>>& grid);
	=====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  grid = [
		["1", "1", "1", "1", "0"],
		["1", "1", "0", "1", "0"],
		["1", "1", "0", "0", "0"],
		["0", "0", "0", "0", "0"],
		]
	Output: 1

	--- Example 2 ---
	Input:  grid = [
		["1", "1", "0", "0", "0"],
		["1", "1", "0", "0", "0"],
		["0", "0", "1", "0", "0"],
		["0", "0", "0", "1", "1"],
		]
	Output: 3

	*** Constraints ***
	m == grid.length
	n == grid[i].length
	1 <= m, n <= 300
	grid[i][j] is '0' or '1'

*/


/*
	------------
	--- IDEA ---
	------------

	A simple self-explanatory DFS.

	The only important thing here is that we're somehow allowed to modify our
	"grid" matrix.

	If that wasn't the case then we would've had to use an unordered_set and/or
	we could implement a BFS Solution instead of DFS.

*/

/* Time  Beats: 98.84% */
/* Space Beats: 85.21% */

/* Time  Complexity:
	O(n) or O(row * columns) or O(V) 'V' for Vertices in Graph
*/
/* Space Complexity: O(n)
	Recursion can go up to N levels deep since we can have all 1's in "grid".
*/
class Solution{
public:
	int numIslands(std::vector<std::vector<char>>& grid)
	{
		int islands = 0;
		int m = grid.size();
		int n = grid[0].size();

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (grid[i][j] == '1')
				{
					dfs(grid, i, j);
					islands++;
				}
			}
		}

		return islands;
	}

private:
	void dfs(std::vector<std::vector<char>>& grid, int i, int j)
	{
		if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size())
			return;

		if (grid[i][j] != '1')
			return;

		grid[i][j] = 'x'; // visited

		/* Clockwise */
		dfs(grid, i - 1, j    ); // Up
		dfs(grid, i    , j + 1); // Right
		dfs(grid, i + 1, j    ); // Down
		dfs(grid, i    , j - 1); // Left
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<std::vector<char>> grid {
	// 	{'1', '1', '1', '1', '0'},
	// 	{'1', '1', '0', '1', '0'},
	// 	{'1', '1', '0', '0', '0'},
	// 	{'0', '0', '0', '0', '0'}
	// };

	/* Example 2 */
	std::vector<std::vector<char>> grid {
		{'1', '1', '0', '0', '0'},
		{'1', '1', '0', '0', '0'},
		{'0', '0', '1', '0', '0'},
		{'0', '0', '0', '1', '1'}
	};


	std::cout << "\n\t=========================";
	std::cout << "\n\t=== NUMBER OF ISLANDS ===";
	std::cout << "\n\t=========================\n";


	/* Write Input */
	bool first = true;
	std::cout << "\n\tGrid: \n\t[\n\t\t";
	for (auto x: grid)
	{
		if (!first)
			std::cout << ", \n\t\t";

		bool first_first = true;
		std::cout << "[";
		for (const auto& xx : x)
		{
			if (!first_first)
				std::cout << ", ";

			std::cout << "\"" << xx << "\"";
			first_first = false;
		}
		std::cout << "]";

		first = false;
	}
	std::cout << "\n\t]\n";


	/* Solution */
	int islands = sol.numIslands(grid);


	/* Write Output */
	std::cout << "\n\tNumber of Islands: " << islands << "\n\n";


	return 0;
}
