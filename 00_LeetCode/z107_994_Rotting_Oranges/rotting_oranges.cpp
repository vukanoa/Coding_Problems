#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <map>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	994) Rotting Oranges
	===========================

	============
	Description:
	============

	You are given an m x n grid where each cell can have one of three values:
		# 0 representing an empty cell
		# 1 representing a fresh orange, or
		# 2 representing a rotten orange

	Every minutes, any fresh orange that is 4-directionally adjacent to a
	rotten orange becomes rotten.

	Return the minimum number of minutes that must elapse until no cell has a
	fresh orange. If this is impossible, return -1.

	=======================================================
	FUNCTION: int orangesRotting(vector<vector<int>>& grid);
	=======================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	   Minute 0          Minute 1           Minute 2          Minute 3
	+---+---+---+     +---+---+---+      +---+---+---+     +---+---+---+
	| 2 | 1 | 1 |     | 2 | 2 | 1 |      | 2 | 2 | 2 |     | 2 | 2 | 2 |
	+---+---+---+     +---+---+---+      +---+---+---+     +---+---+---+
	| 1 | 1 | 0 |     | 2 | 1 | 0 |      | 2 | 2 | 0 |     | 2 | 2 | 0 |
	+---+---+---+     +---+---+---+      +---+---+---+     +---+---+---+
	| 0 | 1 | 1 |     | 0 | 1 | 1 |      | 0 | 1 | 1 |     | 0 | 2 | 1 |
	+---+---+---+     +---+---+---+      +---+---+---+     +---+---+---+


	   Minute 4
	+---+---+---+
	| 2 | 2 | 2 |
	+---+---+---+
	| 2 | 2 | 0 |
	+---+---+---+
	| 0 | 2 | 2 |
	+---+---+---+



	--- Example 1 ---
	Input:  grid = [[2, 1, 1], [1, 1, 0], [0, 1, 1]]
	Output: 4

	--- Example 2 ---
	Input:  grid = [[2, 1, 1], [0, 1, 1], [1, 0, 1]]
	Output: -1
	Explanation: THe orange in the bottom left corner (row 2, column 0) is
	never rotten, because rotting only happens 4-directionally.

	--- Example 3 ---
	Input:  grid = [[0, 2]]
	Output: 0
	Explanation: Since there are already no fresh oranges at minut 0, the
	answer is just 0.

	*** Constraints ***
	m == grid.length
	n = grid[i].length
	1 <= m, n <= 10
	grid[i][j] is 0, 1, or 2.

*/


/*
	------------
	--- IDEA ---
	------------

	First, go through an entire grid and:
		1) Count how many fresh oranges are there. Save in variable "fresh".
		2) Put indexes of rotten oranges in vec_1

	After that check if there are any fresh oranges. If there are not,
	immediately return 0 that indicates that all oranges have been rotten in
	minute 0.

	If there are any fresh oranges left in the grid then:
		if (It's an even minute)
			go through vec_1 and check every vec_1 element's:
			 UP
		LEFT    RIGHT
			DOWN

			If any orange that is UP, DOWN, LEFT or RIGHT to our current rotten
			orange is 1(fresh one) assign 2 to it(make it rotten) and PUSH
			indexes of it in vec_2.


			Why in vec_2 and not in vec_1?
				If we were to push it in vec_1, we would process every fresh
				orange at once. It would be as if we have done it in minute 0.

				So we're changing grid in real time, but pushing newly rotten
				orange indexes in vec_2.

				Once we're in an odd minute, then it the opposite.
				We're iterating throgh vec_2 and we're pushing newly rotten
				orange indexes in vec_1.

			And ERASE current rotten orange from vec_1(int this case).
			Why?
			Because we have already processed that orange. That orange have
			already "infected" the fresh ones and put them into vec_2(or vec_1
			depending on the minute).

	At the end we check if there are any fresh oranges left.

	If there are not:
		return the number of minutes needed to rotten the entire grid.
	else
		return -1 to indicate it's impossible to rotten all the fresh oranges.

*/



/* Time  Beats: 75.26% */
/* Space Beats: 85.29% */
/* Time  Complexity: O(n^2) */
/* Space Complexity: O(num of (fresh + rotten) oranges) */
class Solution{
public:
	int orangesRotting(std::vector<std::vector<int>>& grid)
	{
		std::vector<std::pair<int, int>> vec_1;
		std::vector<std::pair<int, int>> vec_2;
		int fresh  = 0;
		int minute = 0;

		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[0].size(); j++)
			{
				if (grid[i][j] == 0)
					continue;
				else if (grid[i][j] == 1)
					fresh++;
				else
					vec_1.push_back({i, j});
			}
		}

		if (fresh == 0)
			return 0;

		while (!vec_1.empty() || !vec_2.empty())
		{

			if (minute % 2 == 0) // Use vec_1
			{
				for(auto it = vec_1.begin(); it != vec_1.end();)
				{

					/* UP */
					if ((it->first - 1) >= 0) // Not out of bounds
					{
						// If it's a fresh orange
						if (grid[it->first - 1][it->second] == 1)
						{
							grid[it->first - 1][it->second] = 2;

							fresh--;
							vec_2.push_back({it->first - 1, it->second});
						}
					}

					/* DOWN */
					if ((it->first + 1) < grid.size()) // Not out of bounds
					{
						if (grid[it->first + 1][it->second] == 1)
						{
							grid[it->first + 1][it->second] = 2;

							fresh--;
							vec_2.push_back({it->first + 1, it->second});
						}
					}

					/* LEFT */
					if ((it->second - 1) >= 0) // Not out of bounds
					{
						if (grid[it->first][it->second - 1] == 1)
						{
							grid[it->first][it->second - 1] = 2;

							fresh--;
							vec_2.push_back({it->first, it->second - 1});
						}
					}

					/* RIGHT */
					if ((it->second + 1) < grid[0].size()) // Not out of bounds
					{
						// If it's a fresh orange
						if (grid[it->first][it->second + 1] == 1)
						{
							grid[it->first][it->second + 1] = 2;

							fresh--;
							vec_2.push_back({it->first, it->second + 1});
						}
					}

					vec_1.erase(it);
				}

				minute++;
			}
			else // Use vec_2
			{
				for(auto it = vec_2.begin(); it != vec_2.end();)
				{
					/* UP */
					if ((it->first - 1) >= 0) // Not out of bounds
					{
						// If it's a fresh orange
						if (grid[it->first - 1][it->second] == 1)
						{
							grid[it->first - 1][it->second] = 2;

							fresh--;
							vec_1.push_back({it->first - 1, it->second});
						}
					}

					/* DOWN */
					if ((it->first + 1) < grid.size()) // Not out of bounds
					{
						if (grid[it->first + 1][it->second] == 1)
						{
							grid[it->first + 1][it->second] = 2;

							fresh--;
							vec_1.push_back({it->first + 1, it->second});
						}
					}

					/* LEFT */
					if ((it->second - 1) >= 0) // Not out of bounds
					{
						if (grid[it->first][it->second - 1] == 1)
						{
							grid[it->first][it->second - 1] = 2;

							fresh--;
							vec_1.push_back({it->first, it->second - 1});
						}
					}

					/* RIGHT */
					if ((it->second + 1) < grid[0].size()) // Not out of bounds
					{
						// If it's a fresh orange
						if (grid[it->first][it->second + 1] == 1)
						{
							grid[it->first][it->second + 1] = 2;

							fresh--;
							vec_1.push_back({it->first, it->second + 1});
						}
					}

					vec_2.erase(it);
				}

				minute++;
			}


			if (fresh == 0)
				break;
		}

		if (fresh == 0)
			return minute;

		return -1;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<std::vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};

	/* Example 2 */
	// std::vector<std::vector<int>> grid = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};

	/* Example 3 */
	// std::vector<std::vector<int>> grid = {{0, 2}};

	/* Example 4 */
	// std::vector<std::vector<int>> grid =
	// {
	//  {2,0,1,1,1},
	//  {1,0,1,0,1},
	//  {1,0,1,0,1},
	//  {1,0,0,0,1},
	//  {1,1,1,1,1}
	// };

	/* Example 5 */
	std::vector<std::vector<int>> grid =
	{
	 {2,0,1,1,1,1,1,1,1,1},
	 {1,0,1,0,0,0,0,0,0,1},
	 {1,0,1,0,1,1,1,1,0,1},
	 {1,0,1,0,1,0,0,1,0,1},
	 {1,0,1,0,1,0,0,1,0,1},
	 {1,0,1,0,1,1,0,1,0,1},
	 {1,0,1,0,0,0,0,1,0,1},
	 {1,0,1,1,1,1,1,1,0,1},
	 {1,0,0,0,0,0,0,0,0,1},
	 {1,1,1,1,1,1,1,1,1,1}
	};

	/* Example 6 */
	// std::vector<std::vector<int>> grid = {{2,2,2,1,1}};


	std::cout << "\n\t=======================";
	std::cout << "\n\t=== ROTTING ORANGES ===";
	std::cout << "\n\t=======================\n\n";

	/* Write Output */

	/* Write Output */
	bool first = true;
	std::cout << "\n\tGrid:\n\t\t";
	for (auto x: grid)
	{
		for (const auto& xx : x)
		{
			printf("%2d ", xx);
		}
		std::cout << "\n\t\t";
	}
	std::cout << "\n";


	/* Solution */
	int output = sol.orangesRotting(grid);

	/* Write Output */
	std::cout << "\n\tOutput: " << output << "\n\n";

	return 0;
}
