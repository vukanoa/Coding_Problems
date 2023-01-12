#include <iostream>
#include <vector>

/*
	============
	=== EASY ===
	============

	===========================
	118) Pascal's Triangle
	===========================

	============
	Description:
	============

	Given an integer "numRows", return the first numRows of Pascal's Triangle.

	In Pascal's Triangle, each number is the sum of the two numbers directly
	above it as shown:

	    1
	   1 1
	  1 2 1
	 1 3 3 1
	1 4 6 4 1


	====================================================
	FUNCTION: vector<vector<int>> generate(int numRows);
	====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  numRows = 5
	Output: [[1], [1, 1], [1, 2, 1], [1, 3, 3, 1], [1, 4, 6, 4, 1]]

	--- Example 2 ---
	Input:  numRows = 1
	Output: [[1]]

	*** Constraints ***
	1 <= numRows <= 30

*/


class Solution{
public:
	std::vector<std::vector<int>> generate(int numRows)
	{
		std::vector<std::vector<int>> results;

		for (int i = 0; i < numRows; i++)
		{
			std::vector<int> row(i + 1, 1);

			for (int j = 1; j < i; j++)
				row[j] = results[i - 1][j] + results[i - 1][j - 1];

			results.push_back(row);
		}

		return results;
	}
};

int
main()
{
	Solution sol;

	/* Example 1 */
	int numRows = 5;

	/* Example 2 */
	// int numRows = 1;

	/* Example 3 */
	// int numRows = 2;

	/* Example 4 */
	// int numRows = 3;

	/* Example 5 */
	// int numRows = 4;

	std::cout << "\n\t=========================";
	std::cout << "\n\t=== PASCAL'S TRIANGLE ===";
	std::cout << "\n\t=========================\n";

	/* Write Input */
	std::cout << "\n\tPascal's Triangle of SIZE = " << numRows << "\n";

	/* Solution */
	std::vector results = sol.generate(numRows);

	/* Write Output */
	bool first = true;
	std::cout << "\n\tResults: [";
	for (auto x: results)
	{
		if (!first)
			std::cout << ", ";

		bool first_first = true;
		std::cout << "[";
		for (const auto& xx : x)
		{
			if (!first_first)
				std::cout << ", ";

			std::cout << xx;
			first_first = false;
		}
		std::cout << "]";

		first = false;
	}
	std::cout << "]\n\n";


	return 0;
}
