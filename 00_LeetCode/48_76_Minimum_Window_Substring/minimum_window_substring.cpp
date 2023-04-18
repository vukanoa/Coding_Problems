#include <iostream>
#include <vector>
#include <climits>

/*
	============
	=== HARD ===
	============

	============================
	76) Minimum Window Substring
	============================

	============
	Description:
	============

	Given two strings 's' and 't' lenghts 'm' and 'n' respectively, return the
	minimum window substring of 's' such that every character in 't'(including
	duplicates) is included in the window. If there is no such substring,
	return the empty string "".

	=====
	Node: The testcases will be generated such that the answer is unique.
	=====

	================================================
	FUNCTION: string minWindow(string s, string t);
	================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  s = "ADOBECODEBANC", t = "ABC"
	Output: "BANC"

	--- Example 2 ---
	Input:  s = "a", t = "a"
	Output: "a"

	--- Example 3 ---
	Input:  s = "a", t = "aa"
	Output: ""

	*** Constraints ***
	m == s.length
	n == t.length
	1 <= m, n <= 10^5
	s and t consist of uppercase and lowercase English letters.

*/


/*
	------------
	--- IDEA ---
	------------

	We can use basic "Sliding Window" approach to solve this problem.

	In any sliding window based problem we have two pointers. One "right"
	pointer,  whose job is to expand the current window, and we have the "left"
	pointer whose job is to contract a given window. At any point in time only
	one of these pointers move and the other one remains fixed.

	We keep expanding the window by moving the right pointer. When the window
	has all the desired characters(remaining == 0), we contract(if possible)
	and save the smallest window up to this point.

	The answer is the smallest desirable window.

	Example:
	s = "ABAACBAB"
	t = "ABC"

	Output is "ACB".


	Algorithm:
		1. We start two pointers, "left" and "right" initially pointing to the
		   first element of the string 's'.

		2. We use the "right" pointer to expand the window until we get a
		   desirable window i.e. a window that contains all of the characters
		   of 't'.

		3. Once we have a window with all the characters, we can move the left
		   pointer ahead one by one. If the window is still a desirable one we
		   keep on updating the minimum window size.

		4. If the window is not desirable any more, we repeat step 2 onwards.


	1)
		A B A A C B A B
		0 1 2 3 4 5 6 7
		l
		r


	2)
		A B A A C B A B
		0 1 2 3 4 5 6 7
		l r


	3)
		A B A A C B A B
		0 1 2 3 4 5 6 7
		l   r


	4)
		A B A A C B A B
		0 1 2 3 4 5 6 7
		l     r


	5)
		A B A A C B A B   // min_length = 5
		0 1 2 3 4 5 6 7
		l       r


	6)
		A B A A C B A B   // min_length = 4
		0 1 2 3 4 5 6 7
		    l     r


	7)
		A B A A C B A B   // min_length = 3
		0 1 2 3 4 5 6 7
		        l   r


	8)
		A B A A C B A B
		0 1 2 3 4 5 6 7
		          l   r


	9)
		A B A A C B A B
		0 1 2 3 4 5 6 7
		          l     r
                        ^
		                |
		                |_______ Out Of Bounds

*/


/* Time  Beats: 97.70% */
/* Space Beats: 45.37% */

/* Time  Complexity: O(s + t)
   In the worst case we might end up visiting every element of string 's'
   twice, once by left pointer and once by right pointer.
*/
/*
	Space Complexity: O(1)
*/
class Solution{
public:
	std::string minWindow(std::string s, std::string t)
	{
		std::vector<int> occurrences(128, 0);

		for (const char& c : t)
			occurrences[c]++;

		int remaining = t.length();

		int left  = 0;
		int right = 0;
		int min_start  = 0;
		int min_length = INT_MAX;

		while (right < s.length())
		{
			if (--occurrences[s[right++]] >= 0)
				remaining--;

			while (remaining == 0)
			{
				if (right - left < min_length)
				{
					min_length   = right - left;
					min_start = left;
				}

				if (++occurrences[s[left++]] > 0)
					remaining++;
			}
		}

		return min_length < INT_MAX ? s.substr(min_start, min_length) : "";
	}
};




/*
	------------
	--- IDEA ---
	------------

	Absolutely equivalent to the above Solution, just a bit more readable.
	
*/


/* Time  Beats: 97.70% */
/* Space Beats: 45.37% */

/* Time  Complexity: O(s + t)
   In the worst case we might end up visiting every element of string 's'
   twice, once by left pointer and once by right pointer.
*/
/*
	Space Complexity: O(1)
*/
class Solution_readable{
public:
	std::string minWindow(std::string s, std::string t)
	{
		std::vector<int> occurrences(128, 0);

		for (const char& c : t)
			occurrences[c]++;

		int remaining = t.length();

		int left  = 0;
		int right = 0;
		int min_start  = 0;
		int min_length = INT_MAX;

		while (right < s.length())
		{
			if (occurrences[s[right]] > 0)
				remaining--;

			occurrences[s[right]]--;

			while (remaining == 0)
			{
				if (right - left + 1 < min_length)
				{
					min_start  = left;
					min_length = right - left + 1;
				}

				if (occurrences[s[left]] >= 0)
					remaining++;

				occurrences[s[left]]++;
				left++;
			}

			right++;
		}

		return min_length < INT_MAX ? s.substr(min_start, min_length) : "";
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::string s = "ADOBECODEBANC";
	std::string t = "ABC";

	/* Example 2 */
	// std::string s = "a";
	// std::string t = "a";

	/* Example 3 */
	// std::string s = "a";
	// std::string t = "aa";

	/* Example 4 */
	// std::string s = "ABAACBAB";
	// std::string t = "ABC";

	/* Example 5 */
	// std::string s = "CBAEBBSSBECCA";
	// std::string t = "SEC";

	std::cout << "\n\t================================";
	std::cout << "\n\t=== MINIMUM WINDOW SUBSTRING ===";
	std::cout << "\n\t================================\n";


	/* Write Input */
	std::cout << "\n\tString s: \"" << s << "\"";
	std::cout << "\n\tString t: \"" << t << "\"";


	/* Solution */
	std::string str = sol.minWindow(s, t);


	/* Write Output */
	std::cout << "\n\n\tMinimum Substring: \"" << str << "\"\n\n";


	return 0;
}
