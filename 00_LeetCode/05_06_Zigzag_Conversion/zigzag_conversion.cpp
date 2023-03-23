#include <iostream>
#include <vector>
#include <cmath>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    6) ZigZag Conversion
    ================================

	============
	Description:
	============

	The String "PAYPALISHIRING" is written in a zigzag pattern on a given
	number of rows like this:

	3   P   A   H   N
	1   A P L S I I G
	3   Y   I   R

	and then read line by line: "PAHNAPLSIIGYIR"

	Write the code that will take a string and make this conversion given a
	number of rows:

	================================================
	FUNCTION: string convert(string s, int numRows);
	================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "PAYPALISHIRING", numRows = 3
	Output: "PAHNAPLSIIGYIR"

	P   A   H   N
	A P L S I I G
	Y   I   R



	--- Example 2 ---
	Input: s = "PAYPALISHIRING", numRows = 4
	Output: "PYNALSIGYAHRPI"
	Explanation:

	P     I     N
	A   L S   I G
	Y A   H R
	P     I



	--- Example 3 ---
	Input: s = "A", numRows = 1
	Output: "A"



	--- Example 4 ---
	Input: s = "SOMETHINGWRITTEN" numRows = 5
	Output: "SGONWNMIREEHITTT"
	S       G
	O     N W     N
	M   I   R   E
	E H     I T
	T       T



	--- Example 5 ---
	Input: s = "LONGESTSENTENCEWRITTENEVER" numRows = 6
	Output: "LTEONETNNENTEGSCIVETERESWR"

	L         T         E
	O       N E       T N
	N     E   N     T   E
	G   S     C   I     V
	E T       E R       E
	S         W         R



	--- Example 6 ---
	Input: s = "MANACHERALGORITHM" numRows = 2
	Output: "MNAHEALORTHACRGIM"
	Output: "MNCEAGRTMAAHRLOIH"

	M N C E A G R T M
	A A H R L O I H


	*** Constraints ***
	1 <= s.lenght <= 1000
	s consists of English letters (lower-case and upper-case), ',' and '.'.
	1 <= numRows <= 1000
*/


/*
	------------
	--- IDEA ---
	------------

	--- Solution_1 ---

	Our first task is to determine the size of the matrix, as this will allow
	us to create a 2D array where we can simulate writing the input stirng in a
	zig-zag pattern.

	The number of rows of the matrix will be: "numRows".
	We need to calculate the number of columns we need. Let's conisder a part
	bordered with ('|' and '+' and '-'), one column, and a diagonal, as one
	SECTION.

	A B C D E F G H I J K L M N O P R Q S T U V W X

	+-------+---------+---------+
	|A      |I       Q|         |
	|B     H|J     P S|         |
	|C   G  |K   O   T|  X      |
	|D F    |L N     U|W        |
	|E      |M       V|         |
	+-------+---------+---------+

	Each section will have at most "numRows" - 1 columns in it(the last might
	have fewer columns), as can be seen in the above example.

	In each section, we will have:
		2 * numRows - 2
	characters, (numRows characters in one column and numRow - 1 in the
	diagonal).

	Thus, for a string of n characters, we will require at most:
		ceil(n / (2 * numRows - 2))
	sections, and as each section will have:
		numRows - 1 columns.

	We can say we need:
		ceil(n / (2 * numRows - 1)) * (numRows - 1)
	columns.

	So, our matrix will be of dimension, numRows x numCols, where:
		numCols = ceil(n / (2 * numRows - 2)) * (numRows - 1)


	Now this is tricky.

	Let's keep two variables currRow and currCol to represent the current cell
	of the matrix. We start from the top, traverse down through an entire
	column, then traverse diagonally up, i.e. we traverse one section and then
	repeat the same process again for the next section until the string is
	finished.

	So:
	Down -> Diagonally Up -> Down -> Diagonally Up -> Down -> Diagonally Up

	While moving from top to bottom in a column, currCol will remain the same
	but currRow will go from 0 to numRows.

	While moving diagonally up, we move one cell up and one cell right, thus
	increment currCol by 1 and decreate currRow by 1 till it reaches the top(
	currRow = 0)

	We repeat this movement until we traverse all "n" characters of the input
	string.

	Now we have filled the matrix, thus our final task is just to read the
	matrix line-by-line(ignorint empty cells)
*/



/*
	Time  Complexity: O(numRows * n)

	We initialize an empty 2D matrix of size numRows x numCols, where
	O(numCols) is equal to O(n). So it takes O(numRows * n) time.

	Then we iterate on the input string, which takes O(n) time, and again
	traverse on the matrix to generate the final string, which takes
	O(numRows * n) time.

	Thus, overall we take O(2(numRows * n) + n) = O(numRows * n) time.
*/
/*
	Space Complexity: O(numRows * n)

	We use an additional 2D array of size numRows x numCols
	where O(numCols) == O(n)
*/
class Solution{
public:
	std::string convert(const std::string& s, int numRows)
	{
		if (numRows == 1)
			return s;

		int n = int(s.size());
		int sections = ceil(n / (2 * numRows - 2.0));
		int numCols = sections * (numRows - 1);

		std::vector<std::vector<char>> matrix(numRows, std::vector<char>(numCols, ' '));

		int currRow = 0;
		int currCol = 0;
		int currStringIndex = 0;

		// Iterate in zig-zag pattern on matrix and fill it with string characters
		while (currStringIndex < n)
		{
			// Move down
			while (currRow < numRows && currStringIndex < n)
			{
				matrix[currRow][currCol] = s[currStringIndex];
				currRow++;
				currStringIndex++;
			}

			currRow -= 2;
			currCol++;

			// Move up(with moving right also)
			while (currRow > 0 && currCol < numCols && currStringIndex < n)
			{
				matrix[currRow][currCol] = s[currStringIndex];
				currRow--;
				currCol++;
				currStringIndex++;
			}
		}

		std::string answer;
		for (auto& row: matrix)
		{
			for (auto& character: row)
			{
				if (character != ' ')
					answer += character;
			}
		}

		return answer;
	}
};



/*
	------------
	--- IDEA ---
	------------

	If you look carefully enough you will notice a pattern between distances
	between characters in each row.

	If we analyze the jump pattern and traverse the input string using that
	pattern we can avoid he use of additional space.

	===================
	row = 3
	===================
	P   A   H   N
	A P L S I I G
	Y   I   R

	row  -  next in that row
	 0   -   4
	 1   -   2
	 2   -   4




	===================
	row = 4
	===================
	P     I     N
	A   L S   I G
	Y A   H R
	P     I

	row  -  next in that row
	 0   -   6
	 1   -   4
	 2   -   2
	 3   -   6




	===================
	row = 5
	===================
	P       H       U
	A     S I     O T
	Y   I   R   Y   O
	P L     I G     D Y
	A       N       A

	row  -  next in that row
	 0   -   8
	 1   -   6
	 2   -   4
	 3   -   2
	 4   -   8



	==========================
	So it's: 2 * (numRows - 1)
	==========================
	numRows              Increment
	  1   => 2 * (1 - 1) =   0
	  2   => 2 * (2 - 1) =   2
	  3   => 2 * (3 - 1) =   4
	  4   => 2 * (4 - 1) =   6
	  5   => 2 * (5 - 1) =   8
	...


	That's gonna be for 1st and last row. However, other rows will be taken
	care of by this formula:
		2 * (numRows - 1) - 2 * j

		Where 'j' is the number of "inner" row.

		numsRows = 4

		row  -  next in that row
		0    -   6
		1    -   4
		2    -   2
		3    -   6

*/


/* Time  Beats: 98.46% */
/* Space Beats: 99.30% */
/* Time  Complexity O(n) */
/* Space Complexity O(1) */
class Solution_Efficient{
public:
	std::string convert(const std::string& s, int numRows)
	{
		if (numRows == 1)
			return s;

		std::string ret = "";

		for (int curr_row = 0; curr_row < numRows; curr_row++)
		{
			int increment = 2 * (numRows - 1);

			for (int j = curr_row; j < s.length(); j += increment)
			{
				ret += s[j]; // First for that 'V' shape.

				// Only for inner rows
				if (curr_row > 0 && curr_row < numRows - 1)
				{
					// And if it's within the bounds
					if (j + increment - 2 * curr_row < s.length())
						ret += s[j + increment - 2 * curr_row];
				}
			}
		}

		return ret;
	}
};


/*
	numRows   =   Spaces in first row
	   2      =      1
	   3      =      3
	   4      =      5
	   5      =      7
	   6      =      9
	   7      =      11
	   8      =      13

	for numRows = 6, there is 9 spaces
	P_________D
	A       D
	Y     D
	P   D
	A C
	C
*/
void
print_in_zigzag(std::string& s, int numRows)
{
	if (numRows == 1)
		return;

	int rows[numRows];
	int first_last = 2 * (numRows - 1) - 1;
	int tmp = first_last;

	for (int i = 0; i < numRows - 1 ; i++)
	{
		rows[i] = tmp;
		tmp -= 2;
	}
	rows[numRows - 1] = first_last;

	
	/* Printing */
	std::cout << "\n\tVisually:\n";
	for (int i = 0; i < numRows; i++)
	{
		int increment = 2 * (numRows - 1);
		std::cout << "\t\t   ";

		for (int j = i; j < s.length(); j += increment)
		{
			std::cout << s[j];

			for (int x = 0; x < rows[i]; x++)
				std::cout << " ";

			// Only for inner rows
			if (i > 0 && i < numRows - 1)
			{
				// And if it's within the bounds
				if (j + increment - 2 * i < s.length())
				{
					std::cout << s[j + increment - 2 * i];

					/*
						1 : 1
						2 : 3
						3 : 5
						4 : 7
						5 : 9
					*/
					int after_space = 1;
					for (int x = 0; x < i - 1; x++)
						after_space += 2;

					for (int x = 0; x < after_space; x++)
						std::cout << " ";
				}
			}
		}
		std::cout << "\n";
	}
}


int
main()
{
	Solution sol;
	Solution_Efficient sol_eff;

	/* Example 1 */
	// std::string s = "PAYPALISHIRING";
	// int numRows = 3;

	/* Example 2 */
	// std::string s = "PAYPALISHIRING";
	// int numRows = 4;

	/* Example 3 */
	// std::string s = "A";
	// int numRows = 1;

	/* Example 4 */
	// std::string s = "SOMETHINGWRITTEN";
	// int numRows = 5;

	/* Example 5 */
	std::string s = "LONGESTSENTENCEWRITTENEVER";
	int numRows = 6;

	/* Example 6 */
	// std::string s = "MANACHERALGORITHM";
	// int numRows = 2;


	std::cout << "\n\t=========================";
	std::cout << "\n\t=== ZIGZAG CONVERSION ===";
	std::cout << "\n\t=========================\n";


	/* Write Input */
	std::cout << "\n\tOriginal  string is: " << s      << "\n";

	print_in_zigzag(s, numRows);


	/* Solution */
	// std::string conv = sol.convert(s, numRows);
	std::string conv = sol_eff.convert(s, numRows);


	/* Write Output */
	std::cout << "\n\n\tConverted string is: " << conv << "\n\n";

	return 0;
}
