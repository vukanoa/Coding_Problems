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

using namespace std;

/*
	------------
	--- IDEA ---
	------------

	If the string is empty - return empty vector.

	// button_letters
	Make a single array of strings where index corresponds to value of buttons

	vec_results is going to store each "full" combination of all n digits in
	the given string "digits".

	Helper function: "combine"
		* We pass original given String "digits" so we know when to stop.
		* We pass "vec_results" to store each "full" combination.
		* We pass the "index" of a current letter of the current digit we're working on.
		* We pass "str_combination" which represents the combinations of letters until this current digit.
			Once we get to the very last digits in collecting the combinations of letter, then at
			that point our "index" is going to be digits.length() and thus recursion will unwind
			and the next "i" will be tried with the previous combination.
			This will happen until we finish with the last letter of a first digits in our given string.
*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(n^2) */
class Solution{
public:
	/* Space Complexity: O(n) */
	void combine(string digits, vector<string>& vec_results, string button_letters[], int index, string str_combination)
	{
		if (index == digits.length())
		{
			vec_results.push_back(str_combination);
			return;
		}

		string letters = button_letters[digits[index] - '0'];

		for (int i = 0; i < letters.length(); i++)
		{
			combine(digits, vec_results, button_letters, index + 1, str_combination + letters[i]);
		}
	}

	vector<string> letterCombinations(string digits)
	{
		if (digits.length() == 0)
			return {};

		/* Space Complexity: O(n) */
		vector<string> vec_results;

		/* Space Complexity: O(1) since this array won't grow as the input string "digits" increases */
		string button_letters[10] = 
		{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

		combine(digits, vec_results, button_letters, 0, "");

		return vec_results;
	}
};


int
main()
{
	Solution sol;
	vector<string> vec_results;

	/* Example 1 */
	// string digits = "23";

	/* Example 2 */
	// string digits = "";
	
	/* Example 3 */
	// string digits = "2";

	/* Example 4 */
	string digits = "2789";

	std::cout << "\n\t=============================================";
	std::cout << "\n\t=== LETTER COMBINATIONS OF A PHONE NUMBER ===";
	std::cout << "\n\t=============================================\n";

	vec_results = sol.letterCombinations(digits);

	std::cout << "\n\tString: \"" << digits << "\"\n";

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
