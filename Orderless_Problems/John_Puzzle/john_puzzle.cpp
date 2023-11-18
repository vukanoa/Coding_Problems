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
class Solution_1 {
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




/* Time  Complexity: O(Y^2 * 4^(Y^2)) */
/* Space Complexity: O(Y^2) */
class Solution_2 {
private:
    struct Boundaries{
        /* Singing Cross direction */
        int up;
        int down;
        int left;
        int right;
    };

public:
    bool solution(std::vector<std::string>& A, int Y, std::string& U)
    {
        /* Convert U to W, where, for example,  U="carry", W="c1a1r2y1" */
        std::string W = convert(U);

        Boundaries boundaries; // On the stack because it's faster

        for (int i = 0; i < Y; i++)
        {
            for (int j = 0; j < Y; j++)
            {
                if (A[i][j] == W[0])
                {
                    boundaries.up    = i;
                    boundaries.down  = i;
                    boundaries.left  = j;
                    boundaries.right = j;

                    if (dfs(A, i, j, Y, boundaries, W, 0))
                        return true;
                }
            }
        }

        return false;
    }

private:
    std::string convert(std::string& U)
    {
        std::ostringstream out; // String builder. So that we don't create
                                // new string every time we append.

        int count = 1;
        int i = 0;
        while (i < U.length())
        {
            i++;
            while (i < U.length() && U[i-1] == U[i])
            {
                count++;
                i++;
            }

            out << U[i-1];
            out << count;

            count = 1;
        }

        return out.str();
    }

    bool dfs(std::vector<std::string>& A,
             int i,
             int j,
             int Y,
             Boundaries& boundaries,
             std::string& W,
             int w_idx)
    {
        /* We have found the whole word without breaking any of the rules */
        if (w_idx == W.length())
            return true;

        /* Easier to read than to have a bunch of ||'s */
        if (i < 0) return false;
        if (j < 0) return false;
        if (i == Y) return false;
        if (j == Y) return false;
        if ((i - boundaries.up   > 2)) return false;
        if ((j - boundaries.left > 2)) return false;
        if ((boundaries.down  - i > 2)) return false;
        if ((boundaries.right - j > 2)) return false;
        if (A[i][j] != W[w_idx]) return false;

        int old_up    = boundaries.up;
        int old_down  = boundaries.down;
        int old_left  = boundaries.left;
        int old_right = boundaries.right;

        boundaries.up    = std::min(boundaries.up   , i);
        boundaries.down  = std::max(boundaries.down , i);
        boundaries.left  = std::min(boundaries.left , j);
        boundaries.right = std::max(boundaries.right, j);

        char c = A[i][j];
        A[i][j] = '#'; // To prevent infinite "loop".

        /* Signing Cross direction */
        if (dfs(A, i-1, j  , Y, boundaries, W, w_idx+1)) return true; // Up
        if (dfs(A, i+1, j  , Y, boundaries, W, w_idx+1)) return true; // Down
        if (dfs(A, i  , j-1, Y, boundaries, W, w_idx+1)) return true; // Left
        if (dfs(A, i  , j+1, Y, boundaries, W, w_idx+1)) return true; // Right

        A[i][j] = c; // Return the character that was previously there

        boundaries.up    = old_up;
        boundaries.down  = old_down;
        boundaries.left  = old_left;
        boundaries.right = old_right;

        return false;
    }
};




int
main()
{
	Solution_1 sol_1;
	Solution_2 sol_2;

	/* Example 1 */
	// std::vector<char> A1 = {'x', '1', 'd', '2', '1', 'a', '1', 'd', 'c', '2', 'r', '1', '2', 'y', '3', 'i'};
    // std::vector<std::string> A2 = {"x1d2",
    //                               "1a1d",
    //                               "c2r1",
    //                               "1y3i"};
	// int Y = 4;
	// std::string U = "carry";  // does INDEED exist

	/* Example 2 */
	// std::vector<char> A1 = {'x', '1', 'd', '2', '1', 'a', '1', 'd', 'c', '2', 'r', '1', '2', 'y', '3', 'i'};
    // std::vector<std::string> A2 = {"x1d2",
    //                               "1a1d",
    //                               "c2r1",
    //                               "1y3i"};
	// int Y = 4;
	// std::string U = "carrw";  // does NOT    exist

	/* Example 3 */
	// std::vector<char> A1 = {'x', '1', 'd', '2', '1', 'a', '1', 'd', 'c', '2', 'r', '1', '2', 'y', '3', 'i'};
    // std::vector<std::string> A2 = {"x1d2",
    //                               "1a1d",
    //                               "c2r1",
    //                               "1y3i"};
	// int Y = 4;
	// std::string U = "ccyyyrdd";  // Exist but out of 3x3 submatrix, therefore - FALSE

    /* Example 4 */
	// std::vector<char> A1 = {'x', '1', 'd', '2', '1', 'a', '1', 'd', 'c', '2', 'r', '1', '2', 'y', '3', 'i'};
    // std::vector<std::string> A2 = {"x1d2",
    //                               "1a1d",
    //                               "c2r1",
    //                               "1y3i"};
	// int Y = 4;
    // std::string U = "arrri";     // does INDEED exist

    /* Example 5 */
	std::vector<char> A1 = {'x', '1', 'd', '2', '1', 'a', '1', 'd', 'c', '2', 'r', '1', '2', 'y', '3', 'i'};
    std::vector<std::string> A2 = {"x1d2",
                                  "1a1d",
                                  "c2r1",
                                  "1y3i"};
	int Y = 4;
    std::string U = "xarrri";    // Exists but out of 3x3 submatrix, therefore - FALSE



	std::cout << "\n\t===================";
	std::cout << "\n\t=== JOHN PUZZLE ===";
	std::cout << "\n\t===================\n";


	/* Write Input */
	std::cout << "\n\tMatrix: \n\t\t";
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < Y; j++)
			std::cout << A1[i * Y + j] << " ";

		std::cout << "\n\t\t";
	}
	std::cout << "\n\tU = \"" << U << "\"\n";

	/* Solution */
	bool found_1 = sol_1.solution(A1, Y, U);
	bool found_2 = sol_2.solution(A2, Y, U);

	/* Write Output */
    if (found_1)
		std::cout << "\n\t" << "Word \"" << U << "\" does INDEED exist in the matrix!";
    else
	{
		std::cout << "\n\tWord \"" << U << "\" does NOT exist in the matrix!";
		std::cout << "\t(Atleast not within 3x3 submatrix)";
	}

    if (found_2)
		std::cout << "\n\t" << "Word \"" << U << "\" does INDEED exist in the matrix!\n\n";
    else
	{
		std::cout << "\n\tWord \"" << U << "\" does NOT exist in the matrix!";
		std::cout << "\t(Atleast not within 3x3 submatrix)\n\n";
	}

	return 0;
}
