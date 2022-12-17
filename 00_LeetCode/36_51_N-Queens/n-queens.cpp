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


class Solution{
public:
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
};


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
	std::cout << "\n\t================\n\n";

	std::cout << "\n\tBoard: " << n << " x " << n << "\n";

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
	std::cout << "]\n\n";

	return 0;
}
