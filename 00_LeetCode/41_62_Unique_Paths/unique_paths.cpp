#include <iostream>
#include <vector>


/*
	==============
	=== MEDIUM ===
	==============

	===========================
	62) Unique Paths
	===========================

	============
	Description:
	============

	There is a robot on an m x n grid. The robot is initially located at the
	top-left corner(i.e., grid[0][0]). The robot tries to move to the
	bottom-right corner(i.e., grid[m - 1][n - 1]). The robot can only move
	either down or right at any point in time.

	Given the two integers 'm' and 'n', return the number of possible unique
	paths that the robot can take to reach the bottom-right corner.

	The test cases are generated so that the answer will be less than or equal
	to 2 * 10^9

	========================================
	FUNCTION: int uniquePaths(int m, int n);
	========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  m = 3, n = 7
	Output: 28

	--- Example 2 ---
	Input:  m = 3, n = 2
	Output: 3

	*** Constraints ***
	1 <= m, n <= 100

*/


/*
	------------
	--- IDEA ---
	------------

	Since the robot can only move right and down, when it arrives at a point,
	it either arrives from left or above. If we use dp[i][j] for the number
	of unique paths to arrive at the point (i, j), then the state equation is
		dp[i][j] = do[i][j - 1] + dp[i - 1][j]

	Moreover, we have the base cases dp[0][j] = dp[i][0] = 1 for all valid
	i and j.

*/


/* Time  Beats: 23.53% */
/* Space Beats: 56.13% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution_1{
public:
	int uniquePaths(int m, int n)
	{
		std::vector<std::vector<int>> dp(m, std::vector<int>(n, 1));

		for (int i = 1; i < m; i++)
		{
			for (int j = 1; j < n; j++)
				dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
		}

		return dp[m - 1][n - 1];
	}
};




/*
	------------
	--- IDEA ---
	------------

	The above solutions runs in O(m * n) time and costs O(m * n) space.
	However, you may have noticed that each time when we update dp[i][j], we
	only need:
		dp[i - 1][j](previous row)    and
		dp[i][j - 1](previous column)

	So we can reduce memory usage to just two rows => O(n) space.
	
*/


/* Time  Beats: 100% */
/* Space Beats: 89.82% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(n) */
class Solution_2{
public:
	int uniquePaths(int m, int n)
	{
		std::vector<int> previous_row(n, 1);
		std::vector<int> current_row (n, 1);

		for (int i = 1; i < m; i++)
		{
			for (int j = 1; j < n; j++)
			{
				if (i % 2 == 0)
					previous_row[j] = current_row[j] + previous_row[j - 1];
				else
					current_row[j]  = previous_row[j] + current_row[j - 1];
			}
		}

		if (m % 2 == 0)
			return current_row[n - 1];

		return previous_row[n - 1];
	}
};




/*
	------------
	--- IDEA ---
	------------

	Further inspecting the above code:
		previous_row[j] is just the current_row[j] before the update.

	So we can further reduce the memory usage to one row.
	
	Note:
		Space Beats on LeetCode shows worse percentage than Solution 2, but
		that depends on LeetCode. Generally, Solution 3 is always preffered.
*/


/* Time  Beats: 100% */
/* Space Beats: 75.81% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(n) */
class Solution_3{
public:
	int uniquePaths(int m, int n)
	{
		std::vector<int> current_row (n, 1);

		for (int i = 1; i < m; i++)
		{
			for (int j = 1; j < n; j++)
				current_row[j] += current_row[j - 1];
		}

		return current_row[n - 1];
	}
};


void
print_grid(int m, int n)
{
	std::cout << "\n\t";

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == 0 && j == 0)
				std::cout << "R ";
			else if (i == m - 1 && j == n - 1)
				std::cout << "E ";
			else
				std::cout << "_ ";
		}
		std::cout << "\n\t";
	}

	std::cout << "\n";
}


int
main()
{
	Solution_1 sol_1;
	Solution_2 sol_2;
	Solution_3 sol_3;

	/* Example 1 */
	int m = 3;
	int n = 7;

	/* Example 2 */
	// int m = 3;
	// int n = 2;

	/* Example 3 */
	// int m = 23;
	// int n = 12;

	/* Example 4 */
	// int m = 59;
	// int n = 2;

	/* Example 5 */
	// int m = 3;
	// int n = 59;

	std::cout << "\n\t====================";
	std::cout << "\n\t=== UNIQUE PATHS ===";
	std::cout << "\n\t====================\n\n";
	std::cout << "\n\t\t\tLegend:";
	std::cout << "\n\t\t\t\tR - Robot(Start)\n\t\t\t\tS - End  (Finish)";


	/* Write Input */
	std::cout << "\n\tGrid:\n";
	print_grid(m, n);


	/* Solution */
	// int result = sol_1.uniquePaths(m, n);
	// int result = sol_2.uniquePaths(m, n);
	int result = sol_3.uniquePaths(m, n);


	/* Write Output */
	std::cout << "\n\tNumber of unique paths: " << result << "\n\n";

	return 0;
}
