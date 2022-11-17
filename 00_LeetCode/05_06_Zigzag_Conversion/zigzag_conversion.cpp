#include <iostream>

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

	==================================================
	FUNCTION:   string convert(string s, int numRows);
	==================================================

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

== Jump over _ letters for numRows ==
rows letters
(3)  3
(4)  5
(5)  7
(6)  9

*/

using namespace std;

/* Time  Complexity O(n) */
/* Spaee Complexity O(n) */
class Solution {
public:
    string convert(const string& s, int numRows)
    {
        if (numRows == 1)
            return s;
        
        string conv;
        
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
	Solution sol;

	/* Example 1 */
	string s = "PAYPALISHIRING";
	int numRows = 3;

	/* Example 2 */
	// string s = "PAYPALISHIRING";
	// int numRows = 4;

	/* Example 3 */
	// string s = "A";
	// int numRows = 1;

	/* Example 4 */
	// string s = "SOMETHINGWRITTEN";
	// int numRows = 5;

	/* Example 5 */
	// string s = "LONGESTSENTENCEWRITTENEVER";
	// int numRows = 6;

	/* Example 6 */
	// string s = "MANACHERALGORITHM";
	// int numRows = 2;

	string conv = sol.convert(s, numRows);

	std::cout << "\n\tOriginal  string is: " << s    << "\n\n";
	std::cout << "\n\tConverted string is: " << conv << "\n\n";

	return 0;
}
