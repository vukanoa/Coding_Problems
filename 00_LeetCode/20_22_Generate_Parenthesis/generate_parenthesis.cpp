#include <iostream>
#include <vector>


/*
	==============
	=== MEDIUM ===
	==============
	
	===========================
	22) Generate Parenthesis
	===========================
	
	============
	Description:
	============

	Given "n" pairs ofparentheses, write a function to generate all
	combinations of well-formed parenthesis.
	
	==============================================================
	FUNCTION: std::vector<std::string> generateParenthesis(int n);
	==============================================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input:  n = 3
	Output: ["((()))", "(()())", "(())()", "()(())", "()()()"]
	
	--- Example 2 ---
	Input: n = 1
	Output: ["()"]
	
	*** Constraints ***
	1 <= n <= 8

*/

/*

	((()))
	(()())
	(())()
	()(())
	()()()
*/

class Solution{
public:
	std::vector<std::string> generateParenthesis(int n)
	{
		std::vector<std::string> valid_combinations;
		std::string curr_str;
		backtrack(valid_combinations, curr_str, 0, 0, n);

		return valid_combinations;
	}

	void backtrack(std::vector<std::string>& valid_combinations, std::string curr_str, int open, int close, int n)
	{
		if (curr_str.length() == n * 2)
		{
			valid_combinations.push_back(curr_str);
			return;
		}

		if (open < n)
		{
			curr_str.append("(");
			backtrack(valid_combinations, curr_str, open + 1, close, n);
			curr_str.pop_back();
		}

		if (close < open)
		{
			curr_str.append(")");
			backtrack(valid_combinations, curr_str, open, close + 1, n);
			curr_str.pop_back();
		}
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	int n = 3;

	/* Example 2 */
	// int n = 1;

	std::cout << "\n\t============================";
	std::cout << "\n\t=== GENERATE PARENTHESIS ===";
	std::cout << "\n\t============================\n";

	std::cout << "\n\tN = " << n << "\n";

	std::vector<std::string> valid_combinations = sol.generateParenthesis(n);

	int i = 1;
	for(const auto& x : valid_combinations)
		std::cout << "\n\t" << i++ << ". \"" << x << "\"\n";
	
	std::cout << "\n";

	return 0;
}
