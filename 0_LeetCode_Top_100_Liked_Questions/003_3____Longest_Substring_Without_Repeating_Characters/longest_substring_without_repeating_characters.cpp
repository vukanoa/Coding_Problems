#include <iostream>
#include <map>
#include <set>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	=================================================
	3) Longest Substring Without Repeating Characters
	=================================================

	============
	Description:
	============

	Given a string s, find the length of the longest substring(not a
	subsequence) without a repeating characters.

	======================================================
	FUNCTION: int lengthOfLongestSubstring(std::string s);
	======================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "abcabcbb"
	Output: 3
	Explanation: The answer is "abc", with the length of 3.

	--- Example 2 ---
	Input: s = "bbbbb"
	Output: 1
	Explanation: The answer is "b", with the length of 1.

	--- Example 3 ---
	Input: s = "pwwkew"
	Output: 3
	Explanation: The answer is "wke", with the lenght of 3.

	--- Example 4 ---
	Input: s = "svesvhjzhwwj"
	Output: 6
	Explanation: The answer is "esvhjz", with the length of 6.

	*** Constraints ***
	0 <= s.length <= 5 * 10^4
	s consists of English letters, digits, symbols and spaces.

*/


/*
	------------
	--- IDEA ---
	------------

	If s[j] have a duplicate in the range [i, j) with index j', we don't need
	to increase i by one, we can skip all the elements in the range [i, j'] and
	let i to be j' + 1 directly.

	In other words - when we get to s[j], we check if that element exists in
	the map, that is, we have already considered a substring that includes
	that character.

	If it exists in the map, just update its value to j + 1(Next to the current
	index)

	and check if the current index, that is 'j', makes the longest string. The
	length is measured by "j - i + 1".

	We save that value in a variable "longest".

	So if we get to a character that has already been considered, it means that
	its value is in the map and that means that we don't have to try and see
	if next few characters are substrings at all since they certainly aren't
	for the current character is repeated.

	That means we can ignore all the characters until the "right" character of
	the index of previously appeared s[j].

*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int lengthOfLongestSubstring(std::string s)
    {
        int longest = 0;
        int length = s.size();

        std::map<char,int> map;

        int i = 0;
        for(int j = 0; j < length; j++)
        {
            if (map.find(s[j]) != map.end())
                i = std::max(map[s[j]], i);

            longest = std::max(longest, j - i + 1);
            map[s[j]] = j + 1;
        }

        return longest;
    }
};




/* ====================================================================== */

/* ========= */
/* === N === */
/* ========= */


/*
	------------
	--- IDEA ---
	------------

	Maybe the intuitive idea is:
		Check every substring, check if it has any duplicates and if it doesn't
		we're just gonna take the longest one.

	So let's consider this first example:
		a b c a b c b b
		0 1 2 3 4 5 6 7

	1)
		a b c a b c b b
		0 1 2 3 4 5 6 7
		L
		R

		"a" doens't have any duplicates

		if ((R - L + 1) > longest) // It Is - Update Longest to 1
			longest = R - L + 1

	2)
		a b c a b c b b
		0 1 2 3 4 5 6 7
		L R

		"ab" doens't have any duplicates

		if ((R - L + 1) > longest) // It Is - Update Longest to 2
			longest = R - L + 1

	3)
		a b c a b c b b
		0 1 2 3 4 5 6 7
		L   R

		"abc" doens't have any duplicates

		if ((R - L + 1) > longest) // It Is - Update Longest to 3
			longest = R - L + 1

	4)
		a b c a b c b b
		0 1 2 3 4 5 6 7
		L     R

		"abca" DOES have duplicates

		So if we were to continue, we would most certainly do unnecessary work.
		Since now any left substring start at position 0 and including first 4
		characters would have duplicates and certainly would not help us with
		our end value solution.

	So this is the repeated work that we will eliminate with the very
	fundamental technique:
		*** THE SLIDING WINDOW ***

	So, we want to only check the substring without any repeating characters.
	Let's make sure that our "window", our substring doesn't contain any
	duplicates.

	So, once we get to this 2nd 'a' in 4th step, we're going to start removing
	characters from LEFT to RIGHT until we stumble on a characters that is
	repeating.

	In other words - We need to start shrinking window until we no longer have
	duplicates.

	So in our 4th step
	4)
		a b c a b c b b
		0 1 2 3 4 5 6 7
		L     R
	          ^
	          |
	repeating-|

		Remove from the Left until we find that repeating characters(inclusive)

		Before:
			a b c a b c b b
			0 1 2 3 4 5 6 7
			L     R

		After:
			a b c a b c b b
			0 1 2 3 4 5 6 7
			  L   R

		if ((R - L + 1) > longest) // It's not
			longest = R - L + 1




	5)
		a b c a b c b b
		0 1 2 3 4 5 6 7
		  L     R
	            ^
	            |
	repeating --|

		Before:
			a b c a b c b b
			0 1 2 3 4 5 6 7
			  L     R

		After:
			a b c a b c b b
			0 1 2 3 4 5 6 7
			    L   R

		if ((R - L + 1) > longest) // It's not
			longest = R - L + 1



	6)
		a b c a b c b b
		0 1 2 3 4 5 6 7
		    L     R
	              ^
	              |
	repeating ----|

		Before:
			a b c a b c b b
			0 1 2 3 4 5 6 7
			    L     R

		After:
			a b c a b c b b
			0 1 2 3 4 5 6 7
			      L   R

		if ((R - L + 1) > longest) // It's not
			longest = R - L + 1




		*** Now this 7th step is interesting ***
	7)
		a b c a b c b b
		0 1 2 3 4 5 6 7
		      L     R
	                ^
	                |
	repeating ------|

		Before:
			a b c a b c b b
			0 1 2 3 4 5 6 7
			      L     R

		After:
			a b c a b c b b
			0 1 2 3 4 5 6 7
			          L R

		We removed both 'a' and 'b' since 'b' wasn't all the way to the left.

		if ((R - L + 1) > longest) // It's not
			longest = R - L + 1




	8)
		a b c a b c b b
		0 1 2 3 4 5 6 7
		          L   R
	                  ^
	                  |
	repeating --------|

		Before:
			a b c a b c b b
			0 1 2 3 4 5 6 7
			          L   R

		After:
			a b c a b c b b
			0 1 2 3 4 5 6 7
			              R
			              L

		We removed both 'c' and 'b' since 'b' wasn't all the way to the left.

		if ((R - L + 1) > longest) // It's not
			longest = R - L + 1


	return longest;

*/


/* ====================================================================== */


/* Time  Beats: 40.53% */
/* Space Beats: 19.60% */
/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_N{
public:
    int lengthOfLongestSubstring(std::string s)
    {
		std::set<char> characters_set;
		int longest = 0;
		int left = 0;

		for (int right = 0; right < s.length(); right++)
		{
			while (characters_set.find(s[right]) != characters_set.end())
			{
				characters_set.erase(s[left]);
				left++;
			}

			characters_set.insert(s[right]);

			longest = std::max(longest, right - left + 1);
		}

		return longest;
	}
};




/*
	Even better implementation

	Note: Since it is said:
		s consists of English letters, digits, symbols and spaces.
	that means that we can have a:
		std::vector<int> ascii(128, -1);
*/


/* Time  Beats: 98.50% */
/* Space Beats: 85.65% */
/*	Time  Complexity: O(n)	*/
/*
	Space Complexity: O(1)
	Since it is said that s consists only of lowercase english letters
*/
class Solution_Efficient{
public:
	int lengthOfLongestSubstring(std::string s)
	{
		std::vector<int> ascii(128, -1);

		int left  = 0;
		int right = 0;

		int longest = 0;

		while (right < s.size())
		{
			char curr_char = s[right];

			int index = ascii[curr_char];
			if (index != -1 && index >= left && index < right)
				left = index + 1;

			longest = std::max(longest, right - left + 1);
			ascii[curr_char] = right;
			right++;
		}

		return longest;
	}
};




/*
	------------
	--- IDEA ---
	------------

	My Efficient way.
	
*/

/* Time  Beats: 97.47% */
/* Space Beats: 90.45% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_My_Efficient {
public:
	int lengthOfLongestSubstring(std::string s)
	{
		int n = s.length();
		std::vector<int> ascii(128, 0);

		int longest = 0;

		int left  = 0;
		int right = 0;

		while (right < n)
		{
			ascii[s[right]]++;

			while (ascii[s[right]] > 1)
				ascii[s[left++]]--;

			longest = std::max(longest, right - left + 1);

			right++;
		}

		return longest;
	}
};


int
main()
{
	Solution              sol;
	Solution_N            sol_n;
	Solution_Efficient    sol_efficient;
	Solution_My_Efficient sol_my_efficient;

	/* Example 1 */
	// std::string s = "abcabcbb";

	/* Example 2 */
	// std::string s = "bbbbb";

	/* Example 3 */
	// std::string s = "pwwkew";

	/* Example 4 */
	std::string s = "svesvhjzhwwj";


	std::cout << "\n\t======================================================";
	std::cout << "\n\t=== LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS ===";
	std::cout << "\n\t======================================================\n";

	/* Write Input */
	std::cout << "\n\tString: " << s << "\n";

	/* Solution */
	// int longest = sol.lengthOfLongestSubstring(s);
	// int longest = sol_n.lengthOfLongestSubstring(s);
	int longest = sol_efficient.lengthOfLongestSubstring(s);
	// int longest = sol_my_efficient.lengthOfLongestSubstring(s);

	/* Write Output */
	std::cout << "\n\tLongest: " << longest << "\n\n";

	return 0;
}
