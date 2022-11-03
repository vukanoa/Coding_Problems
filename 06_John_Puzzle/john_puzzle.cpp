#include <iostream>
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

// Check in 3x3 submatrix
int x[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int y[] = { -1, 0, 1, -1, 1, -1, 0, 1 };


std::string
transform(std::string U)
{
	std::string word;
	char cur = U[0];
	int  cnt = 0;

	word.push_back(U[0]);

	for (int i  = 0; i < U.length(); i++)
	{
		if (i > 0 && U[i] != U[i-1])
		{
			word.push_back(cnt + 48); // 0 = 48 in ASCII
			word.push_back(U[i]);
			cur = U[i];
			cnt = 1;
		}
		else
			cnt++;
	}
	word.push_back(cnt + 48); // 0 = 48 in ASCII

	return word;
}


bool
not_out_or_previous(int row, int col, int prev_row, int prev_col, int Y)
{
    return (row >= 0) && (row < Y) && (col >= 0) && (col < Y) && !(row == prev_row && col == prev_col);
}


bool search_matrix(char mat[][4], int row, int col, int prev_row, int prev_col, std::string word, std::string path, int index, int n, int Y)
{
    if (index > n || mat[row][col] != word[index]) // If character doesn't match with next character in the word
        return false;

    // Append
    path += std::string(1, word[index]) + "(" + std::__cxx11::to_string(row) + ", " + std::__cxx11::to_string(col) + ") ";


    if (index == n) // Current character matches with the last character in the word -> Found. Done.
    {
        std::cout << "\n\t" << path << "\n";
        return true;
    }

    for (int k = 0; k < 8; ++k)
    {
        if (not_out_or_previous(row + x[k], col + y[k], prev_row, prev_col, Y))
        {
            if (search_matrix(mat, row + x[k], col + y[k], row, col, word, path, index + 1, n, Y))
                return true;
        }
    }

    return false;
}


bool
solution(char mat[][4], int Y, std::string U)
{
	std::string word = transform(U);
	int n = word.size() - 1;

    for (int i = 0; i < Y; ++i)
    {
        for (int j = 0; j < Y; ++j)
        {
            if (mat[i][j] == word[0])
            {
                if (search_matrix(mat, i, j, -1, -1, word, "", 0, n, Y))
                    return true;
            }
        }
    }

    return false;
}


int
main()
{
	int Y = 4;
    char mat[4][4] = {
                            {'x', '1', 'd', '2'},
                            {'1', 'a', '1', 'd'},
                            {'c', '2', 'r', '1'},
                            {'1', 'y', '3', 'i'}
    };

	std::string U = "carry";     // does INDEED exist
	// std::string U = "carrw";  // does NOT    exist

    if (solution(mat, Y, U))
		std::cout << "\n\t" << "Word \"" << U << "\" does INDEED exist in the matrix!\n\n";
    else
		std::cout << "\n\tWord \"" << U << "\" does NOT exist in the matrix!\n\n";


    return 0;
}
