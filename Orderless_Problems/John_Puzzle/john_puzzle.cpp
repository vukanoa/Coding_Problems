#include <iostream>
#include <vector>
#include <sstream>
#include <string>

/*
    x 1 d 2
    1 a 1 d
    c 2 r 1
    1 y 3 i

    Y = 4
    3 <= Y <= 10

    W = "carry"

    Solution:
    c - A[2][0] => 1 - A[1][0] => a - A[1][1] => 1 - A[1][2] => r - A[2][2] =>
    2 - A[2][1] => y - A[3][1] => 1 - A[3][0]
*/

/* Time  Complexity: O(Y^2 * 4^(Y^2)) */
/* Space Complexity: O(Y^2) */
class Solution{
public:
	int solution(std::vector<char>& A, int Y, std::string U)
	{
		std::vector<std::vector<char>> matrix(Y, std::vector(Y, 'a'));

		// Form a Matrix
		int pointer = 0;
		for (int i = 0; i < Y; i++)
		{
			for (int j = 0; j < Y; j++)
				matrix[i][j] = A[pointer++];
		}

		// Form a Word in the format [letter, digit, letter, ...]
		std::ostringstream out;

		int i = 0;
		pointer = i + 1;
		while (i < U.length())
		{
			while (pointer < U.length() && U[i] == U[pointer])
				pointer++;

			out << U[i] << pointer - i;

			i = pointer;
			pointer++;
		}

		// Word in necessarity format
		std::string W = out.str();
		for (int i = 0; i < Y; i++)
		{
			for (int j = 0; j < Y; j++)
			{
				if (W[0] == matrix[i][j])
				{
					int up    = i;
					int down  = i;
					int left  = j;
					int right = j;

					if (dfs(matrix, i, j, W, 1, up, down, left, right))
						return true;
				}
			}
		}

		return false;
	}

private:
	bool dfs(std::vector<std::vector<char>>& matrix,
	         int i,
	         int j,
	         std::string& W,
	         int x,
			 int up,
			 int down,
			 int left,
			 int right)
	{
		if (x == W.length())
			return down - up <= 2 && right - left <= 2; // Within submatrix_3x3

		// Up, Down, Left, Right
		std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

		for (const auto& dir : directions)
		{
			int row = i + dir.first;
			int col = j + dir.second;

			if (row >= 0 && row < matrix.size() && col >= 0 && col < matrix[0].size())
			{
				if (std::isdigit(W[x]) && matrix[row][col] - '0' >= W[x] - '0'
				   ||
				   W[x] == matrix[row][col])
				{
					int u = std::min(up,    row);
					int d = std::max(down,  row);
					int l = std::min(left,  col);
					int r = std::max(right, col);

					if (dfs(matrix, row, col, W, x+1, u, d, l, r))
						return true;
				}
			}
		}

		return false;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<char> A = {'x', '1', 'd', '2', '1', 'a', '1', 'd', 'c', '2', 'r', '1', '2', 'y', '3', 'i'};
	// int Y = 4;
	// std::string U = "carry";     // does INDEED exist

	/* Example 2 */
	// std::vector<char> A = {'x', '1', 'd', '2', '1', 'a', '1', 'd', 'c', '2', 'r', '1', '2', 'y', '3', 'i'};
	// int Y = 4;
	// std::string U = "carrw";  // does NOT    exist

	/* Example 3 */
	std::vector<char> A = {'x', '1', 'd', '2', '1', 'a', '1', 'd', 'c', '2', 'r', '1', '2', 'y', '3', 'i'};
	int Y = 4;
	std::string U = "ccyyyrdd";     // Exist but out of 3x3 submatrix, therefore - FALSE


	std::cout << "\n\t===================";
	std::cout << "\n\t=== JOHN PUZZLE ===";
	std::cout << "\n\t===================\n";


	/* Write Input */
	std::cout << "\n\tMatrix: \n\t\t";
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < Y; j++)
			std::cout << A[i * Y + j] << " ";

		std::cout << "\n\t\t";
	}
	std::cout << "\n\tU = \"" << U << "\"\n";

	/* Solution */
	bool found = sol.solution(A, Y, U);

	/* Write Output */
    if (found)
		std::cout << "\n\t" << "Word \"" << U << "\" does INDEED exist in the matrix!\n\n";
    else
	{
		std::cout << "\n\tWord \"" << U << "\" does NOT exist in the matrix!\n";
		std::cout << "\t(Atleast not within 3x3 submatrix)\n\n";
	}


	return 0;
}
