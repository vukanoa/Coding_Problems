#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	289) Game Of Life
	===========================

	============
	Description:
	============

	According to Wikipedia's article: "The Game of Life, also known simply as
	Life, is a cellular automaton devised by the British mathematician John
	Horton Conway in 1970."

	The board is made up of an m x n grid of cells, where each cell has an
	initial state: live (represented by a 1) or dead (represented by a 0).
	Each cell interacts with its eight neighbors (horizontal, vertical,
	diagonal) using the following four rules (taken from the above Wikipedia
	article):

	1. Any live cell with fewer than two live neighbors dies as if caused by
	under-population.

	2. Any live cell with two or three live neighbors lives on to the next
	generation.

	3. Any live cell with more than three live neighbors dies, as if by
	over-population.

	4. Any dead cell with exactly three live neighbors becomes a live cell, as
	if by reproduction.

	The next state is created by applying the above rules simultaneously to
	every cell in the current state, where births and deaths occur
	simultaneously. Given the current state of the m x n grid board, return the
	next state.


	Follow up:

    - Could you solve it in-place? Remember that the board needs to be updated
	simultaneously: You cannot update some cells first and then use their
	updated values to update other cells.

    - In this question, we represent the board using a 2D array. In principle,
	the board is infinite, which would cause problems when the active area
	encroaches upon the border of the array (i.e., live cells reach the
	border). How would you address these problems?

	======================================================
	FUNCTION: void gameOfLife(vector<vector<int>>& board);
	======================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	+---+---+---+          +---+---+---+                    
	| 0 | 1 | 0 |          | 0 | 0 | 0 |                    
	+---+---+---+          +---+---+---+                    
	| 0 | 0 | 1 |          | 1 | 0 | 1 |                    
	+---+---+---+   --->   +---+---+---+                    
	| 1 | 1 | 1 |          | 0 | 1 | 1 |                    
	+---+---+---+          +---+---+---+                    
	| 0 | 0 | 0 |          | 0 | 1 | 0 |                    
	+---+---+---+          +---+---+---+                    

	Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
	Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]



	--- Example 2 ---
	+---+---+         +---+---+
	| 0 | 1 |         | 0 | 0 |
	+---+---+  ---->  +---+---+
	| 0 | 0 |         | 1 | 0 |
	+---+---+         +---+---+
	Input: board = [[1,1],[1,0]]
	Output: [[1,1],[1,1]]	


	*** Constraints ***
	m == board.length
	n == board[i].length
	1 <= m, n <= 25
	board[i][j] is 0 or 1.

*/

/* Time  Beats: 50.44% */
/* Space Beats: 71.95% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution{
public:
	const int ALL_NEIGHBORS = 8;

	void gameOfLife(std::vector<std::vector<int>>& board)
	{
		int m = board.size();
		int n = board[0].size();
		std::vector<std::vector<int>> result_table(m, std::vector<int>(n, 0));

		std::vector<int> dir_rows {-1, -1, -1,  0,  0, +1, +1, +1};
		std::vector<int> dir_cols {-1,  0, +1, -1, +1, -1,  0, +1};

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				int x = 0;
				int neighbors = 0;

				while (x < ALL_NEIGHBORS)
				{
					int row = i + dir_rows[x];
					int col = j + dir_cols[x];

					if (row >= 0 && row < m && col >= 0 && col < n)
					{
						if (board[row][col] == 1)
							neighbors++;
					}

					x++;
				}

				if (board[i][j] == 1) // Live Cell
				{
					if (neighbors == 2 || neighbors == 3)
						result_table[i][j] = 1;
					else
						result_table[i][j] = 0;
				}
				else // Dead Cell
				{
					if (neighbors == 3)
						result_table[i][j] = 1;
				}
			}
		}

		// Replace board with the next state
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				board[i][j] = result_table[i][j];
			}
		}
	}
};
