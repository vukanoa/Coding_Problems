#include <iostream>
#include <vector>
#include <cmath>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    6) Longest Palindromic Substring
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




	--- Solution ---
	If you look carefully enough you will notice a pattern between distances
	between characters in each row.

	If we analyze the jump pattern and traverse the input string using that
	pattern we can avoid he use of additional space.

	A B C D E F G H I J K L M N O P Q S T U V W X
	! @ # $ % $ # @ ! @ # $ % $ # @ ! @ # $ % $ #

	In the above example (each character {'!', '@', '#', '$', '%'), denotes
	one "color", i.e. one row of our previously traverse matrix when mapping it
	in input string) in jumps denoted by '@', first, we jump 6 then 2, then 6
	and then again 2.

	Similarly, there is a pattern for all collors. Let's start analyzing this
	pattern using the same filled matrix.

	Notice in the below image the first and last rows we jump to the same
	position in the next section, i.e. we jump(number of characters) positions
	in each section.

	But in the rest of the rows, we must traverse to the next corresponding
	element of the same section before jumping to the next section.

	The hard part will be to calculate how to jump to the next character

	1. If we have to jump to the next section then it's simple: we only jump:
	       charsInSection
	   characters. So:
	       currIndex += charsInSection.

	2. If we have to jump to the next character in the same section, then we
	   will have to calculate how many characters are between these two
	   position and increment currIndex by that value.

	   If the total characters in a section are charsInSection and we are in
	   the ith row, then the number of characters above the current row will be
	   2 * i, and the number of characters left will be:
	       charsInBetween = charsInSection - 2 * i

	   So:
	       secondIndex = currIndex + charsInBetween

	   Thus, we can iterate over the input string in line-by-line order afer
	   writing it in a zig-zag pattern directly.

*/



/*
Time  Complexity: O(numRows * n)

We initialize an empty 2D matrix of size numRows x numCols, where O(numCols) is
equal to O(n). So it takes O(numRows * n) time.

Then we iterate on the input string, which takes O(n) time, and again traverse
on the matrix to generate the final string, which takes O(numRows * n) time.

Thus, overall we take O(2(numRows * n) + n) = O(numRows * n) time.
*/
/*
Space Complexity: O(numRows * n)

We use an additional 2D array of size numRows x numCols
where O(numCols) == O(n)
*/
class Solution_1{
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


/* Time  Complexity O(n) */
/* Space Complexity O(1) */
class Solution {
public:
    std::string convert(const std::string& s, int numRows)
    {
        if (numRows == 1)
            return s;

        std::string conv;
        int step = 2 * numRows - 2;

        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j + i < s.length(); j += step)
            {
                conv += s[j + i];
                if (i != 0 && i != numRows - 1 && j + step - i < s.length())
                    conv += s[j + step - i];
            }
        }

        return conv;
    }
};

int
main()
{
	Solution sol_1;
	Solution sol;

	/* Example 1 */
	std::string s = "PAYPALISHIRING";
	int numRows = 3;

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
	// std::string s = "LONGESTSENTENCEWRITTENEVER";
	// int numRows = 6;

	/* Example 6 */
	// std::string s = "MANACHERALGORITHM";
	// int numRows = 2;

	std::string conv_1 = sol_1.convert(s, numRows);
	std::string conv = sol.convert(s, numRows);

	// Original String
	std::cout << "\n\tOriginal  string is: " << s      << "\n\n";

	// Conv_1
	std::cout << "\n\tConverted string is: " << conv_1;

	// Conv
	std::cout << "\n\tConverted string is: " << conv;

	std::cout << "\n\n";
	return 0;
}
