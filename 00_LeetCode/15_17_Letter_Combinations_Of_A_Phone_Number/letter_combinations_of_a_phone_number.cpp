#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============
	
	=========================================
	17) Letter Combinations of a Phone Number
	=========================================
	
	============
	Description:
	============

	Given a string containing digits from 2-9 inclusive, return all possible
	letter combinations that the number could represent. Return the answer
	in any order.
	
	=====
	Node: Number 1 does not map to any letters.
	=====
	
	===========================================================
	FUNCTION: vector<string> letterCombinations(string digits);
	===========================================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input:  digits = "23"
	Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]
	
	--- Example 2 ---
	Input:  digits = ""
	Output: []
	
	--- Example 3 ---
	Input:  digits = "2"
	Output: ["a", "b", "c"]
	
	*** Constraints ***
	0 <= digits.length <= 4
	digits[i] is a digit in the range ['2', '9'].

*/


/*
	------------
	--- IDEA ---
	------------

	If the string is empty - return empty vector.

	// button_letters
	Make a single array of strings where index corresponds to value of buttons

	// vec_results 
	To store each "full" combination of all n digits in the given
	string "digits".

	Helper function: "backtracking"
	We pass:
		Basic:
			digits, vec_results, button_letters

		Important:
			index, str_combination(Up to this point)
	
	Begin with backrackting(..., 0, "")
	// "..." denotes Basic things we pass.

	return vec_resuls
*/


/* Time  Beats: 100% */
/* Space Beats: 81.98% */
/*
	Time  Complexity: O(n * 4^n)
	Since numbers: 9 and 7 both have 4 letters, if we had digits: 9997
	That would mean: 4 * 4 * 4 * 4 string combinations in vec_result, but
	the length of each and every string is going to be "n", that is number of
	digits in vector "digits".

	So overall Time Complexity is O(n * 4^n)
	This is the Worst case Time Complexity

*/
/* Space Complexity: O(n) */
class Solution{
public:
	/* Space Complexity: O(n) */
	void backtrack(std::string digits, std::vector<std::string>& vec_results, std::string button_letters[], int index, std::string str_combination)
	{
		if (str_combination.length() == digits.length())
		{
			vec_results.push_back(str_combination);
			return;
		}

		std::string letters_of_curr_digit = button_letters[digits[index] - '0'];

		for (int i = 0; i < letters_of_curr_digit.length(); i++)
		{
			backtrack(digits, vec_results, button_letters, index + 1, str_combination + letters_of_curr_digit[i]);
		}
	}

	std::vector<std::string> letterCombinations(std::string digits)
	{
		if (digits.length() == 0)
			return {};

		/* Space Complexity: O(n) */
		std::vector<std::string> vec_results;

		/* Space Complexity: O(1) since this array won't grow as the input string "digits" increases */
		std::string button_letters[10] = 
		{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

		backtrack(digits, vec_results, button_letters, 0, "");

		return vec_results;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::string digits = "23";

	/* Example 2 */
	// std::string digits = "";
	
	/* Example 3 */
	// std::string digits = "2";

	/* Example 4 */
	// std::string digits = "2789";

	std::cout << "\n\t=============================================";
	std::cout << "\n\t=== LETTER COMBINATIONS OF A PHONE NUMBER ===";
	std::cout << "\n\t=============================================\n";


	/* Write Input */
	std::cout << "\n\tString: \"" << digits << "\"\n";

	/* Solution */
	std::vector<std::string> vec_results = sol.letterCombinations(digits);

	/* Write Output */
	bool first = true;
	std::cout << "\n\tAll Combinations: [";
	for (const auto& x: vec_results)
	{
		if (!first)
			std::cout << ", ";

		std::cout << "\"" << x << "\"";
		first = false;
	}
	std::cout << "]\n\n";	

	return 0;
}
