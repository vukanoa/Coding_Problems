#include <iostream>
#include <vector>

/*
	============
	=== HARD ===
	============

	===============================
	10) Regular Expression Matching
	===============================

	============
	Description:
	============

	Given an input string s and a pattern p, implement regular expression
	matching with support for '.' and '*' where:

		'.' Matches any single character.
		'*' Matches zero or more of the preceding element.

	The matching should cover the entire input string (not partial).

	===========================================
	FUNCTION: bool isMatch(string s, string p);
	===========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "aa", p = "a"
	Output: false
	Explanation: "a" does not match the entire string "aa".

	--- Example 2 ---
	Input: s = "aa", p = "a*"
	Output: true
	Explanation: '*' means zero or more of the preceding element, 'a'.
	Therefore, by repeating 'a' once, it becomes "aa".

	--- Example 3 ---
	Input: s = "ab", p = ".*"
	Output: true
	Explanation: ".*" means "zero or more (*) of any character (.)".


	*** Constraints ***
    1 <= s.length <= 20
    1 <= p.length <= 20
    s contains only lowercase English letters.
    p contains only lowercase English letters, '.', and '*'.
    It is guaranteed for each appearance of the character '*', there will be a
	previous valid character to match.

*/


/*
	------------
	--- IDEA ---
	------------

	'*' means - 0 or more occurences of character before '*'
	'.' means - matches any single character

	A few examples to consider:

	For p = "a.b"
		
		All these, do INDEED match:
		s = "acb"  -> true
		s = "aab"  -> true
		s = "atb"  -> true

		All these, do NOT match:
		s = "ab"   -> false
		s = "acby" -> false
		s = "cb"   -> false



	For p = "a*b"

		All these, do INDEED match:
		s = "b"     -> true
		s = "ab"    -> true
		s = "aab"   -> true
		s = "aaab"  -> true

		All these, do NOT match:
		s = "a"   -> false
		s = "acb" -> false

	
	For p = "a*b.*y"

		All these, do INDEED match:
		s = "by"    -> true
		s = "bwy"   -> true
		s = "abwy"  -> true
		s = "abwmy" -> true

		All these, do NOT match:
		s = "ay"    -> false
		s = "ab"    -> false

	First, let's look at the recurrence relationship or how we are going to
	fill up the table in Bottom-Up Dynamic Programming approach.

	T[i][j]

	T is a 2D boolean matrix.
	i is index in the text;
	j is index in the pattern;
	
	So, if T[i][j] == true, it means that value at position 'i' in the text and
	'j' value in pattern match, then there is a regular expression match.


	So how does T[i][j] gets its value?
		if (s[i] == p[j] || p[j] == '.') then
			T[i][j] becomes T[i - 1][j - 1] because value at 'i' matches
			pattern 'j', so since those characters are already matching, so
			without them or removing them from text and pattern, whatever is
			left we check if that is a regular expression match or not.

		On the other hand,
		if (p[j] == '*') then
			in that case we have two conditions:
				1. We can have 0 occurrences of the value right before this
				   pattern j, i.e. value of p[j - 1].

				   So for 0 occurences, it's T[i][j - 2]


				or 

				2. We could have 1 or more occurences of the value right before
				   pattern j, i.e. value of p[j - 1], but we can only apply
				   that if:

					   if (s[i] == p[j - 1] || p[j - 1] == '.') then
						   in that case, T[i][j] gets the value of T[i - 1][j]
	



	If this is not clear or if it's a bit confusing, look at the next example
	and the simulation down here that will hopefully clarify this logic:

	s = "xaabyc"
	p = "xa*b.c"

	First thing we do is we take the 2D boolean matrix.
	Number of rows and columns in this matrix is going to be one more than the
	length of the text and length of the pattern, respectively.

	Then, first thing we're going to do is initialize the 0th row and 0th
	column.

					 0     1     2     3     4     5     6
						   x     a     *     b     .     c
				  +-----+-----+-----+-----+-----+-----+-----+
			0     |  T  |  F  |  F  |  F  |  F  |  F  |  F  |
				  +-----+-----+-----+-----+-----+-----+-----+
			1  x  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			2  a  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			3  a  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			4  b  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			5  y  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			6  c  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
	
	So why is T[0][0] == true?
	Because if you have an empty string and an empty pattern, they we'll count
	that as a regular expression match.

	Why is the entire 0th column == false?
	If you have an empty pattern and a non-empty string s, then the answer will
	always be false.

	Opposite is not true. You can have an empty string s and a non-empty
	pattern that do match. Example:

		s = ""
		p = "a*b*"
	
	So the first row won't always be "false" but for this example it is.


				                                Rules
				  ____________________________________________________________________________
		          |                                                                          |
		          |    if (s[i] == p[j] || p[j] == '.')                                      |
		          |        T[i - 1][j - 1]                                                   |
		          |__________________________________________________________________________|
		T[i][j] = |                                                                          |
				  |    if (p[j] == '*')                                                      |
		          |        T[i][j - 2]                                                       |
		          |                                                                          |
		          |        if (s[i] == p[j - 1] || p[j - 1] == '.')                          |
		          |            T[i - 1][j]                                                   |
   		          |__________________________________________________________________________|
				  |                                                                          |
				  |    T[i][j] = false                                                       |
   		          |__________________________________________________________________________|


	Now, let's start filling the matrix:
	We start from T[1][1].

	What is it equal to?
	Since s[i] == p[j] || p[j] == '.', T[i][j] becomes T[i - 1][j - 1].
	i.e. T[1][1] = T[0][0] = true

					 0     1     2     3     4     5     6
						   x     a     *     b     .     c
				  +-----+-----+-----+-----+-----+-----+-----+
			0     |  T  |  F  |  F  |  F  |  F  |  F  |  F  |
				  +-----+-----+-----+-----+-----+-----+-----+
			1  x  |  F  |  T  |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			2  a  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			3  a  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			4  b  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			5  y  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			6  c  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+

		If we have only:
			s = "x"
			p = "x"
			
			and since the do match, then what we are left with is:

			s = ""
			p = ""

			which do match as well, there we would've returned true.

		Now we move to the next column(2nd one in the 0th row)
		The pattern is "a" and the value is "x" so since they do not match, we
		should return "false".


					 0     1     2     3     4     5     6
						   x     a     *     b     .     c
				  +-----+-----+-----+-----+-----+-----+-----+
			0     |  T  |  F  |  F  |  F  |  F  |  F  |  F  |
				  +-----+-----+-----+-----+-----+-----+-----+
			1  x  |  F  |  T  |  F  |  T  |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			2  a  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			3  a  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			4  b  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			5  y  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+
			6  c  |  F  |     |     |     |     |     |     |
				  +-----+-----+-----+-----+-----+-----+-----+

		Now since the pattern is the '*', we have to check the middle condition
		from the above rules.

		if (T[i][j] == '*') then
			T[i][j] = T[i][j - 2] // Which is T

		We had:
			s = "x"
			p = "xa*"

			So since we stumbled upon a '*', we check if two before matched.

		We continue using these Rules:
				                                Rules
				  ____________________________________________________________________________
		          |                                                                          |
		          |    if (s[i] == p[j] || p[j] == '.')                                      |
		          |        T[i - 1][j - 1]                                                   |
		          |__________________________________________________________________________|
		T[i][j] = |                                                                          |
				  |    if (p[j] == '*')                                                      |
		          |        T[i][j - 2]                                                       |
		          |                                                                          |
		          |        if (s[i] == p[j - 1] || p[j - 1] == '.')                          |
		          |            T[i - 1][j]                                                   |
   		          |__________________________________________________________________________|
				  |                                                                          |
				  |    T[i][j] = false                                                       |
   		          |__________________________________________________________________________|

*/

/* Time  Beats: 83.20% */
/* Space Beats: 68.18% */

/* Time  Complexity: O(n * m) */
/* Space Complexity: O(n * m) */
class Solution {
public:
	bool isMatch(string s, string p)
	{
		int m = s.size(), n = p.size();

		std::vector<std::vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
		dp[0][0] = true;

		for (int i = 0; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (p[j - 1] == '*')
				{
					dp[i][j] = dp[i][j - 2] || (i && dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
				}
				else
				{
					dp[i][j] = i && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
				}
			}
		}

		return dp[m][n];
	}
};




/* You may further reduce the memory usage down to two vectors O(n) */

/* Time  Beats: 83.20% */
/* Space Beats: 90.41% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(n) */
class Solution {
public:
	bool isMatch(string s, string p)
	{
		int m = s.size(), n = p.size();
		vector<bool> pre(n + 1, false), cur(n + 1, false);
		cur[0] = true;

		for (int i = 0; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (p[j - 1] == '*')
				{
					cur[j] = cur[j - 2] || (i && pre[j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
				}
				else
				{
					cur[j] = i && pre[j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
				}
			}

			fill(pre.begin(), pre.end(), false);
			swap(pre, cur);
		}

			return pre[n];
	}
};





/* Reduce it to one vector */

/* Time  Beats: 100% */
/* Space Beats: 90.41% */

/* Time  Complexity: O(n * m) */
/* Space Complexity: O(1) */
class Solution {
public:
	bool isMatch(string s, string p)
	{
		int m = s.size(), n = p.size();
		vector<bool> cur(n + 1, false);

		for (int i = 0; i <= m; i++)
		{
			bool pre = cur[0];
			cur[0] = !i;

			for (int j = 1; j <= n; j++)
			{
				bool temp = cur[j];
				if (p[j - 1] == '*')
				{
					cur[j] = cur[j - 2] || (i && cur[j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
				}
				else 
				{
					cur[j] = i && pre && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
				}

				pre = temp;
			}
		}

		return cur[n];
	}
};
