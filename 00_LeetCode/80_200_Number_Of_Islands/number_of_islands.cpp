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
	horizontally or vertically. You may asuem all four edges of the grid are
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

*/



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
		int count = 0;

		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[0].size(); j++)
			{
				if (grid[i][j] == '1')
				{
					DFS(grid, i, j);
					count++;
				}
			}
		}

		return count;
	}

	void DFS(std::vector<std::vector<char>>& grid, int i, int j)
	{
		if (i < 0 || j < 0 || i >= grid.size() || j>= grid[0].size())
			return;

		if (grid[i][j] != '1')
			return;

		grid[i][j] = 'v'; // 'v' for visited
		DFS(grid, i + 1, j    ); // Down
		DFS(grid, i - 1, j    ); // Up
		DFS(grid, i    , j + 1); // Right
		DFS(grid, i    , j - 1); // Left
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
	std::cout << "\n\tGrid: \n\t[\n\t";
	for (auto x: grid)
	{
		if (!first)
			std::cout << ", \n\t";

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
