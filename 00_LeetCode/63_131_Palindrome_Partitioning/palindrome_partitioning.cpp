#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	=============================
	131) Palindrome Partitioning
	=============================

	============
	Description:
	============

	Given a string 's', partition 's' such that every substring of the
	partition is a palindrome. Return all possible palindrome partitioning of
	's'.

	=====================================================
	FUNCTION: vector<vector<string>> partition(string s);
	=====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  Input s = "aab"
	Output: [["a", "a", "b"], ["aa", "b"]]

	--- Example 2 ---
	Input:  s = "a"
	Output: [["a"]]

	*** Constraints ***
	1 <= s.length <= 16
	's' containts only lowercase English letters

*/


/*
	------------
	--- IDEA ---
	------------

	Intuition:
	- The structure of the question is quite clear that it promotes the use of
	  recursion. The recursion approach of this question can be like: we start
	  iteration from beginning and step by step we increase the size of substr
	  that we are checking for palindromes. Once the palindrome substring is
	  found, the ubstr needs to go to a vector storing those palindromes
	  substrings. This is how the brute force recursion will work.

	- The optimization of the above recursion is backtracking.
	  A backtracking algorithm uses the depth-first search method. When it
	  starts exploring the solutions, a bounding or a helper function is
	  applied so that the algorithm can check if the so-far built solution
	  satisfies the constraints. If it does, it continues searching. If it
	  doesn't, the branch would be eliminated, and the algorithm goes back to
	  the level above. In simple words - Backtraking starts from some
	  intermediate position where there is still a hope to get a new
	  palindrome.

	- In backtracking algorithm there is always a helper method or a safe
	  checker method which checks whether the built solution satisfies the
	  conditions or not. This one thing is guaranteed.


	Algorithm:
	1. As we've alread said - Backtracking always needs a helper method. In our
	   problem we will need a bool helper method which will check if a given
	   substring is indeed a palindrome. Let's name it: bool palindrome()

	2. Variables:
		- "results" is the vector for storing the vectors of palindromic
		  substrings.

		- "current_vec" is the vector for storing the ongoing substring which
		  has the potential of satisfying the conditions of palindrome.

		- "start" stores the starting position of the current substring

		- Index 'i' for traversing inside the substring.

	3. We search from "start" till the end of the string. Once we reach a
	   position 'i' such that the substring from "start" to 'i', meaning
	   s.substr(start, i - start + 1) is a palindrome, we add it to our
	   "current_vec" vector. Then we recursively call the same method to
	   execute the remaining substring. Once we reach the end of the string,
	   we add palindromes "current_vec" into the "results" of all the possible
	   partitioning.

	4. Remember that at position 'i' we find s.substr(start, i - start + 1) to
	   be a palindrome and we immediately add it to "current_vec". Now imagine
	   that there may be a position j, such that j > i, and
	   s.substr(start, j - start + 1) is also a palindrome. That means we need
	   to go back to our "start" before adding s.substr(start, i - start + 1)
	   to "current_vec" and continue to find the next palindrome position after
	   'i'. And after this evertime we simply need to remove or pop
	   s.substr(start, i - start + 1) out of "current_vec" to execute the
	   backtracking algorithm.

	5. The steps we executed in the above step is none other than the DFS.

*/



/* Time  Complexity: O(n * 2^n) */
/* Space Complexity: O(n) */
class Solution {
private:
	void backtracking_dfs(std::string& s, int start, std::vector<std::string>& current_vec, std::vector<std::vector<std::string>>& results)
	{
		if (start == s.length())
			results.push_back(current_vec);
		else
		{
			for (int i = start; i < s.length(); i++)
			{
				if (palindrome(s, start, i))
				{
					current_vec.push_back(s.substr(start, i - start + 1));
					backtracking_dfs(s, i + 1, current_vec, results);
					current_vec.pop_back();
				}
			}
		}
	}

	bool palindrome(std::string& str, int left, int right)
	{
		while (left < right)
		{
			if (str[left++] != str[right--])
				return false;
		}

		return true;
	}

public:
	std::vector<std::vector<std::string>> partition(std::string s)
	{
		std::vector<std::vector<std::string>> results;
		std::vector<std::string> current_vec;

		backtracking_dfs(s, 0, current_vec, results);

		return results;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::string s = "aab";

	/* Example 2 */
	// std::string s = "a";

	/* Example 3 */
	// std::string s = "";

	/* Example 4 */
	// std::string s = "abcba";

	/* Example 5 */
	// std::string s = "baab";

	/* Example 6 */
	// std::string s = "bab";


	std::cout << "\n\t===============================";
	std::cout << "\n\t=== PALINDROME PARTITIONING ===";
	std::cout << "\n\t===============================\n\n";

	/* Write Input */
	std::cout << "\tString: \"";
	for (const auto& x: s)
		std::cout << x;
	std::cout << "\"\n";

	/* Solution */
	std::vector<std::vector<std::string>> results = sol.partition(s);

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

			std::cout << "\"" << xx << "\"";
			first_first = false;
		}
		std::cout << "]";

		first = false;
	}
	std::cout << "]\n\n";


	return 0;
}
