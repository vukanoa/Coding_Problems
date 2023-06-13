#include <iostream>
#include <vector>

/*
	============
	=== EASY ===
	============

	==============================
	171) Excel Sheet Column Number
	==============================

	============
	Description:
	============

	Given a string columnTitle that represents the column title as appears in
	an Excel shet, return its corresponding column number.

	For example:
	A -> 1
	B -> 2
	C -> 3
	...
	Z -> 26
	AA -> 27
	AB -> 28
	...

	================================================
	FUNCTION: int titleToNumber(string columnTitle);
	================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  columnTitle = "A"
	Output: 1

	--- Example 2 ---
	Input:  columnTitle = "AB"
	Output: 28

	--- Example 3 ---
	Input:  columnTitle = "ZY"
	Output: 701

	*** Constraints ***
	1 <= cout.length <= 7
	columnTitle consists only of uppercase English letters.
	columnTitle is in the range ["A', "FXSHRXW"].

*/


/*
	------------
	--- IDEA ---
	------------

	A -> 1
	...
	Z -> 26
	AA -> 27
	AB -> 28

	Self-Explanatory
	
*/

/* Time  Beats: 100% */
/* Space Beats: 95.36% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int titleToNumber(std::string columnTitle)
    {
        int n = columnTitle.length();
        int result = 0;

        for(auto& c : columnTitle)
        {
            result *= 26;
            result += c - 'A' + 1;
        }

        return result;
    }
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::string columnTitle = "A";

	/* Example 2 */
	// std::string columnTitle = "AB";

	/* Example 3 */
	std::string columnTitle = "ZY";

	/* Example 4 */
	// std::string columnTitle = "AAA";

	/* Example 5 */
	// std::string columnTitle = "FXSHRXW";


	std::cout << "\n\t=================================";
	std::cout << "\n\t=== EXCEL SHEET COLUMN NUMBER ===";
	std::cout << "\n\t=================================\n";


	/* Write Input */
	std::cout << "\n\tString: \"" << columnTitle << "\"\n";


	/* Solution */
	int result = sol.titleToNumber(columnTitle);


	/* Write Output */
	std::cout << "\n\tResult: " << result << "\n\n";


	return 0;
}

