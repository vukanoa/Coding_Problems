#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	130) Surrounded Regions
	===========================

	============
	Description:
	============

	Given an m x n matrix board containing 'X' and 'O', capture all regions
	that are 4-directionally surrounded by 'X'.

	A region is captured by flipping all 'O's into 'X's in that surrounded
	region.

	==================================================
	FUNCTION: void solve(vector<vector<char>>& board);
	==================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	+---+---+---+---+             +---+---+---+---+
	| X | X | X | X |             | X | X | X | X |
	+---+---+---+---+             +---+---+---+---+
	| X | O | O | X |             | X | X | X | X |
	+---+---+---+---+    ====>    +---+---+---+---+
	| X | X | O | X |             | X | X | X | X |
	+---+---+---+---+             +---+---+---+---+
	| X | O | X | X |             | X | O | X | X |
	+---+---+---+---+             +---+---+---+---+

	Input: board = [["X","X","X","X"],
	                ["X","O","O","X"],
	                ["X","X","O","X"],
	                ["X","O","X","X"]]
	
	Output: [["X","X","X","X"],
	         ["X","X","X","X"],
	         ["X","X","X","X"],
	         ["X","O","X","X"]]

	Explanation: Notice that an 'O' should not be flipped if:
	- It is on the border, or
	- It is adjacent to an 'O' that should not be flipped.
	The bottom 'O' is on the border, so it is not flipped.
	The other three 'O' form a surrounded region, so they are flipped.
	

	--- Example 2 ---
	Input: board = [["X"]]
	Output: [["X"]]


	*** Constraints ***
	m == board.length
	n == board[i].length
	1 <= m, n <= 200
	board[i][j] is 'X' or 'O'.

*/




/*
	------------
	--- IDEA ---
	------------

	We will use boundary DFS to solve this problem
	
	Let's analyze when an 'O' cannot be flipped,
	if it has atleast one 'O' in it's adjacent, AND ultimately this chain
	of adjacent 'O's is connected to some 'O' which lies on boundary of
	board
	
	Consider these two cases for clarity :

	O's won't be flipped          O's will be flipped
	   X O X X X                     X X X X X     
	   X O O O X                     X O O O X
	   X O X X X                     X O X X X 
	   X X X X X                     X X X X X
	
	we can conclude if a chain of adjacent O's is connected some O on
	undary then they cannot be flipped
	
	Steps to Solve :
	1. Move over the boundary of board, and find O's 

	2. Every time we find an O, perform DFS from it's position

	3. In DFS convert all 'O' to '#'
	   (why?? so that we can differentiate which 'O' can be flipped and which
	    cannot be)   

	4. After all DFSs have been performed, board contains three elements:
	   '#', 'O' and 'X'

	5. 'O' are left over elements which are not connected to any boundary O,
	   so flip them to 'X'

	6. '#' are elements which cannot be flipped to 'X', so flip them
	   back to 'O'
*/

/* Time  Beats: 89.51% */
/* Space Beats: 93.25% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */ // Due to recursion
class Solution {
public:
    void solve(vector<vector<char>>& board)
    {
		int m = board.size();
		int n = board[0].size();

		/* Moving over first and last column */
        for (int i = 0; i < m; i++)
        {
			// Check First(0-th) column
            if (board[i][0] == 'O')
				dfs(board, i, 0, m, n);
            
			// Check Last(n-1th) column
            if (board[i][n-1]== 'O')
				dfs(board, i, n-1, m, n);
        }

		/* Moving over first and last row */
        for (int j = 1; j < board[0].size() - 1; j++)
        {
			// Check First(0-th) row
            if (board[0][j] == 'O')
				dfs(board, 0, j, m, n);

			// Check Last(m-1th) row
            if (board[m-1][j] == 'O')
				dfs(board, m-1, j, m, n);
        }

        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == '#')
                    board[i][j] = 'O';
            }
        }
    }

private:
    void dfs(vector<vector<char>>& board, int i, int j, int m, int n)
    {
        if (i < 0 || j < 0 || i >= m || j >= n || board[i][j] != 'O')
            return;
        
		board[i][j] = '#';

        dfs(board, i - 1, j    , m, n); // Down
        dfs(board, i + 1, j    , m, n); // Up
        dfs(board, i    , j - 1, m, n); // Left
        dfs(board, i    , j + 1, m, n); // Right
    }
};
