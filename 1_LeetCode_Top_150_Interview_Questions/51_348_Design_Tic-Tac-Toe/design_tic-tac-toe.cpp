#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	348) Design Tic-Tac-Toe
	===========================

	============
	Description:
	============

	Design a Tic-tac-toe game that is played between two players on a  n  x  n  grid.

	You may assume the following rules:

		1. A move is guaranteed to be valid and is placed on an empty block.
		2. Once a winning condition is reached, no more moves is allowed.
		3. A player who succeeds in placing  n  of their marks in a horizontal,
		   vertical, or diagonal row wins the game.


	Follow up:
	Could you do better than O(n^2) per move()

	Hint:
	Could you trade extra space such that move() operation can be done in O(1)?
	You need two arrays: int rows[n], int cols[n], plus two variables: diagonal,
	anti_diagonal. 


	=================================================
	FUNCTION: class TicTacToe{
	public:
		TicTacToe(){}

		int move(int row, int col, int player);
	private:
		std::vector<std::vector<int> board;
	}
	=================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Given n = 3, assume that player 1 is "X" and player 2 is "O" in the board.

	TicTacToe toe = new TicTacToe(3);

	toe.move(0, 0, 1); - > Returns 0 (no one wins)
	|X| | |
	| | | |    // Player 1 makes a move at (0, 0).
	| | | |

	toe.move(0, 2, 2); -> Returns 0 (no one wins)
	|X| |O|
	| | | |    // Player 2 makes a move at (0, 2).
	| | | |

	toe.move(2, 2, 1); -> Returns 0 (no one wins)
	|X| |O|
	| | | |    // Player 1 makes a move at (2, 2).
	| | |X|

	toe.move(1, 1, 2); -> Returns 0 (no one wins)
	|X| |O|
	| |O| |    // Player 2 makes a move at (1, 1).
	| | |X|

	toe.move(2, 0, 1); -> Returns 0 (no one wins)
	|X| |O|
	| |O| |    // Player 1 makes a move at (2, 0).
	|X| |X|

	toe.move(1, 0, 2); -> Returns 0 (no one wins)
	|X| |O|
	|O|O| |    // Player 2 makes a move at (1, 0).
	|X| |X|

	toe.move(2, 1, 1); -> Returns 1 (player 1 wins)
	|X| |O|
	|O|O| |    // Player 1 makes a move at (2, 1).
	|X|X|X|







	*** Constraints ***
	Unknown

*/


/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(n^2) */
class TicTacToe {
public:
	/** Initialize your data structure here. */
	TicTacToe(int n) : n(n)
	{
		board = vector<vector<int>>(n, std::vector<int>(n, 0));
	}

	/*
		Player {player} makes a move at ({row}, {col}).
		@param row The row of the board.
		@param col The column of the board.
		@param player The player, can be either 1 or 2.
			@return The current winning condition, can be either:
				0: No one wins.
				1: Player 1 wins.
				2: Player 2 wins.
	*/
	int move(int row, int col, int player)
	{
		board[row][col] = player;
		bool win = true;

		for (int i = 0; i < n; i++)
		{
			if (board[i][col] != player)
			{
				win = false;
				break;
			}
		}

		if (win)
			return player;

		win = true;
		for (int j = 0; j < n; j++)
		{
			if (board[row][j] != player)
			{
				win = false;
				break;
			}
		}

		if (win)
			return player;

		if (row == col)
		{
			win = true;
			for (int i = 0; i < n; i++)
			{
				if (board[i][i] != player)
				{
					win = false;
					break;
				}
			}

			if (win)
				return player;
		}

		// anti-diagonal
		if (row == n - col - 1)
		{
			win = true;
			for (int i = 0; i < n; i++)
			{
				if (board[i][n - i - 1] != player)
				{
					win = false;
					break;
				}
			}

			if (win)
				return player;
		}

		return 0;
	}

private:
    int n;
    std::vector<std::vector<int>> board;
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe obj = new TicTacToe(n);
 * int param_1 = obj.move(row,col,player);
 */




/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

// ==================
// === SOLUTION 2 ===
// ==================

/* Time  Complexity: O(1) */
/* Space Complexity: O(n) */
class TicTacToe {
public:
	/** Initialize your data structure here. */
	TicTacToe(int n)
		: n(n), diagonal(0), anti_diagonal(0), rows(n,0), cols(n,0)
	{}

	/*
		Player {player} makes a move at ({row}, {col}).
		@param row The row of the board.
		@param col The column of the board.
		@param player The player, can be either 1 or 2.
			@return The current winning condition, can be either:
				0: No one wins.
				1: Player 1 wins.
				2: Player 2 wins.
		*/

	int move(int row, int col, int player)
	{
		int add = (player == 1) ? 1 : -1;

		rows[row] += add;
		cols[col] += add;

		if (row == col)
			diagonal += add;

		if (row == n - col - 1)
			anti_diagonal += add;

		return (abs(rows[row]) == n || abs(cols[col]) == n || abs(diagonal) == n || abs(anti_diagonal) == n) ? player : 0;

	}

private:
	int n, diagonal, anti_diagonal;
	vector<int> rows, cols;
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe obj = new TicTacToe(n);
 * int param_1 = obj.move(row,col,player);
 */
