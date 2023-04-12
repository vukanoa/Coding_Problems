#include <iostream>
#include <vector>


/*
	============
	=== HARD ===
	============

	===========================
	51) N-Queens
	===========================

	============
	Description:
	============

	The n-queens puzzle is the problem of placing 'n' queens on an n x n
	chessboard such that no two queens attack each other.

	Given an integer n, return all distinct solutions to the n-queens puzzle.
	You may return the answer in any order.

	Each solution contains a distinct board configuration of the n-queens
	placement, where 'Q' and '.' both indicate a queen and an empty space,
	respectively.

	=====================================================
	FUNCTION: vector<vector<string>> solveNQueens(int n);
	=====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  n = 4
	Output: [[".Q..","...Q","Q...","..Q."], ["..Q.","Q...","...Q",".Q.."]]

	--- Example 2 ---
	Input:  n = 1
	Output: [["Q"]]

	*** Constraints ***
	1 <= n <= 9

*/


/*
	------------
	--- IDEA ---
	------------

	We're trying to "fit" the Queen column by column, that's why we only need
	to check if the current Queen attacks any:
		1. Left upper    diagonal
		2. Left(meaning the same row, but left)
		3. Left downward diagonal
	
	If it doens't return false(false means it does indeed attack a Queen on
	the board) then return true and place a Queen on that spot and continue
	until we've placed all of the Queens on the board.

	If at any point we figure out that at a certain row we're attacking any
	Queen on the board - Backtrack and try some other "layout".
	
*/


/* Time  Beats:   100% */
/* Space Beats: 67.67% */

/* Time  Complexity: O(n!) */
/* Space Complexity: O(n^2) */
class Solution{
public:
	std::vector<std::vector<std::string>>
	solveNQueens(int n)
	{
		std::vector<std::vector<std::string>> results;
		std::vector<std::string> board(n);

		std::string str(n, '.');

		for (int i = 0; i < n; i++)
			board[i] = str;

		backtracking(0, board, results, n);

		return results;
	}

private:
	bool not_attacking(int row, int col, std::vector<std::string>& board, int n)
	{
		int tmp_row = row;
		int tmp_col = col;

		// Checking left upper diagonal for attack for any queen
		while (row >= 0 && col >= 0)
		{
			if (board[row][col] == 'Q')
				return false;

			row--;
			col--;
		}

		// Check left side of cols for attack from any queen
		row = tmp_row;
		col = tmp_col;

		while (col >= 0)
		{
			if (board[row][col] == 'Q')
				return false;

			col--;
		}

		// Check left downard diagonal for any attack
		row = tmp_row;
		col = tmp_col;

		while (row < n && col >= 0)
		{
			if (board[row][col] == 'Q')
				return false;

			row++;
			col--;
		}

		// If not under attack
		return true;
	}

	void backtracking(int col, std::vector<std::string>&board, std::vector<std::vector<std::string>>& results, int n)
	{
		// Base Case - if col reaches the end
		if (col == n)
		{
			results.push_back(board);
			return;
		}

		for (int row = 0; row < n; row++)
		{
			// Row is fixed and traversed in column
			if (not_attacking(row, col, board, n))
			{
				board[row][col] = 'Q';
				backtracking(col + 1, board, results, n);
				board[row][col] = '.';
			}
		}
	}
};


void
print_queens(std::vector<std::vector<std::string>>& results, int n)
{
	for (int i = 0; i < results.size(); i++)
	{
		std::cout << "\n\t" << i+1 << ")";
		for (int j = 0; j < n; j++)
		{
			std::cout << "\n\t\t";

			for (int k = 0; k < n; k++)
			{
				std::cout << results[i][j][k] << " ";
			}
		}

		std::cout << "\n\n\t";
	}

	std::cout << "\n";
}


int
main()
{
	Solution sol;

	/* Example 1 */
	int n = 4;

	/* Example 2 */
	// int n = 1;

	std::cout << "\n\t================";
	std::cout << "\n\t=== N-QUEENS ===";
	std::cout << "\n\t================\n";


	/* Write Input */
	std::cout << "\n\tBoard: " << n << " x " << n << "\n";

	
	/* Solution */
	std::vector<std::vector<std::string>> results = sol.solveNQueens(n);


	/* Write Output */
	bool first = true;
	std::cout << "\n\tResults: [";
	for (auto x: results)
	{
		if (!first)
			std::cout << ", ";

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
	std::cout << "]\n";

	/* Print Queens on Board in ASCII */
	print_queens(results, n);


	return 0;
}
