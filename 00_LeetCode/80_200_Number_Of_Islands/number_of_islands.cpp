#include <iostream>
#include <vector>
#include<queue>

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

	There is also an elegant Find&Union Solution, but I won't implement it yet.

*/

/* Time  Beats: 98.84% */
/* Space Beats: 85.21% */

/* Time  Complexity:
	O(n) or O(row * columns) or O(V) 'V' for Vertices in Graph
*/
/* Space Complexity: O(n)
	Recursion can go up to N levels deep since we can have all 1's in "grid".
*/
class Solution_DFS {
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




/*
	------------
	--- IDEA ---
	------------

	It's a similar IDEA, just implemented using BFS.

	I wanted to implement it in as different way as possible, that's why I've
	used: lambda function, directions, pairs, etc.

	BFS does NOT use recursion. BFS uses a Queue, instead.

*/

/* Time  Beats: 91.73% */
/* Space Beats: 26.98% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_BFS{
public:
	int numIslands(std::vector<std::vector<char>>& grid)
	{
		if (grid.size() == 0 || grid[0].size() == 0)
			return 0;

		int m = grid.size();
		int n = grid[0].size();

		std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
		int islands = 0;

		/* Lambda */
		auto inside = [&](int i, int j)
		{
			return i >= 0 && j >= 0 && i < m && j < n;
		};

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (inside(i, j) && grid[i][j] == '1')
				{
					islands++;
					/* If we are not allowed to modify original given "grid",
					   then use vector<vector<bool>> visisted.
					*/
					grid[i][j] = 'x'; // Mark as processed

					/* BFS */
					std::queue<std::pair<int, int>> queue;
					queue.push({i, j});

					while (!queue.empty())
					{
						std::pair<int, int> curr = queue.front();
						queue.pop();

						for (const std::pair<int, int>& dir : directions)
						{
							int row = curr.first  + dir.first;
							int col = curr.second + dir.second; 

							if (inside(row, col) && grid[row][col] == '1')
							{
								grid[row][col] = 'x';
								queue.push({row, col}); // Mark as processed
							}
						}
					}
				}
			}
		}

		return islands;
	}
};


int
main()
{
	Solution_DFS sol_dfs;
	Solution_BFS sol_bfs;


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
	int islands = sol_dfs.numIslands(grid);
	// int islands = sol_bfs.numIslands(grid);


	/* Write Output */
	std::cout << "\n\tNumber of Islands: " << islands << "\n\n";


	return 0;
}
