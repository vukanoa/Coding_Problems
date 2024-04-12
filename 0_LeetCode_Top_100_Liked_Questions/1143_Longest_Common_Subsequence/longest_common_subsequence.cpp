#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	================================
	1143) Longest Common Subsequence
	================================

	============
	Description:
	============

	Given two strings text1 and text2, return the length of their longest
	common subsequence. If there is no common subsequence, return 0.

	A subsequence of a string is a new string generated from the original
	string with some characters(can be none) deleted without changing the
	relative order of the remaining characters.

		- For example, "ace" is a subsequence of "abcde".

	A common subsequence of two strings is a subsequence that is common to both
	strings.

	===================================================================
	FUNCTION: int longestCommonSubsequence(string text1, string text2);
	===================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  text = "abcde", text2 = "ace"
	Output: 3
	Explanation: The longest common subsequence is "ace" and its length is 3.

	--- Example 2 ---
	Input:  text1 = "abc", text2 = "abc"
	Output: 3
	Explanation: The longest common subsequence is "abc" and its length is 3.

	--- Example 3 ---
	Input:  text1 = "abc", text2 = "def"
	Output: 0
	Explanation: There is no such common subsequence, so the result is 0.

	*** Constraints ***
	1 <= text1.length, text2.length <= 1000
	text1 and text2 consist of only lowercase English characters.

*/

/*

bbcde
ace

"oxcpqrsvwf"
"shmtulqrypy"

*/


/*
	------------
	--- IDEA ---
	------------

	Consider this example:

	1. "abcde"
	    #

	2. "ace"
	    #


	Let's look at the first character in the string. In this case: They match.
	So does it, atleast make sense to you that if both of the characters match
	each other then we can break it into a subproblem.

	Now the new problem we're looking at is: Find the longest common
	subsequence between the remainder of both strings, with these:

	1. "bcde"
	2. "ce"

	Plus 1 because the first two characters matched. ('a' and 'a')
	We know that the longest common subsequence in this subproblem is going
	to be at least 1, because of the previous two a's.

	And that is what the Dynamic Programming is all about - Finding the
	subproblem.

	Now what if the initial example looked like this:
	(We replaced 'a', in the first string, with 'b')

	1. "bbcde"
	    #

	2. "ace"
	    #

	Now these two characters don't match, so what do we do then?
	We can't do what we just did. We can't add 1 and find the longest common
	subsequence in the subproblem:

	1. "bcde"
	2. "ce"

	We can't do that, but we can break it into the different subproblem.
	We can say that it's possible that the longest common subsequence could be
	between these two:

	1. "bbcde"
	2. "ce"

		Or it could be between:

	1. "bcde"
	2. "ace"


	Let's draw all of this, using the 1st Example:

	1. "abcde"
	2. "ace"

                   j

           a     c     e
        +-----+-----+-----+=====+
     a  |     |     |     |     =
        +-----+-----+-----+=====+
     b  |     |     |     |     =
 i      +-----+-----+-----+=====+
     c  |     |     |     |     =
        +-----+-----+-----+=====+
     d  |     |     |     |     =
        +-----+-----+-----+=====+
     e  |     |     |     |     =
        +-----+-----+-----+=====+
        =     =     =     =     =
        +=====+=====+=====+=====+


	So the entire longest commong subsequence value is going to be at:
		dp['a']['a'] <==> dp[0][0]

	We want to compute that value. However, you'll find out that to compute
	that you want to solve

		dp[0][1] // RIGHT
		dp[1][0] // LEFT
		dp[1][1] // DIAGONAL


	So, in this example:

                   j
           #
           a     c     e
        +-----+-----+-----+=====+
   # a  |     |     |     |     =
        +-----+-----+-----+=====+
     b  |     |     |     |     =
 i      +-----+-----+-----+=====+
     c  |     |     |     |     =
        +-----+-----+-----+=====+
     d  |     |     |     |     =
        +-----+-----+-----+=====+
     e  |     |     |     |     =
        +-----+-----+-----+=====+
        =     =     =     =     =
        +=====+=====+=====+=====+

	'a' in the first string and 'a' in the second string match, thus we have
	to continue computing - Diagonally.
	That will represent doing a subproblem:

	1. "bcde"
	2. "ce"

	Now:

                   j
                 #
           a     c     e
        +-----+-----+-----+=====+
     a  |     |     |     |     =
        +-----+-----+-----+=====+
   # b  |     |     |     |     =
 i      +-----+-----+-----+=====+
     c  |     |     |     |     =
        +-----+-----+-----+=====+
     d  |     |     |     |     =
        +-----+-----+-----+=====+
     e  |     |     |     |     =
        +-----+-----+-----+=====+
        =     =     =     =     =
        +=====+=====+=====+=====+

	Since 'b' in the first stirng and 'c' in the second do not match, now we
	won't go diagonally. We're going to look at a different subproblem.
	Since these two characters do not match, we have to check two different
	subproblems.

	Either in this one:

	// RIGHT
	1. "bcde"
	2. "e"

		Or in this one:

	// DOWN
	1. "cde"
	2. "ce"


	Now just by looking at this first:
	// RIGHT
	1. "bcde"
	2. "e"

	You can see that the longest common subsequence is 1.

	But when you look at the other:
	// DOWN
	1. "cde"
	2. "ce"

	This is going to end up being 2.

	Now if we follow this rule, at one point we will end up in this situation:


                   j

          'a'   'c'   'e'   ''
        +-----+-----+-----+=====+
    'a' |     |     |     |     =
        +-----+-----+-----+=====+
    'b' |     |     |     |     =
 i      +-----+-----+-----+=====+
    'c' |     |     |     |     =
        +-----+-----+-----+=====+
    'd' |     |     |     |     =
        +-----+-----+-----+=====+
    'e' |     |     |     |     =
        +-----+-----+-----+=====+
     '' =     =     =     =     =
        +=====+=====+=====+=====+

	First of all, what are these bold parts of the grid?
	There are empty string. For example:

	1. "cde"
	2. ''

	The longest commont subsequence between these is: 0

	So these cells will all have 0 and since we're doing a Bottom-Up approach
	, going from the most righ the most down upwards, that will the
	"initial" value.


                   j

          'a'   'c'   'e'   ''
        +-----+-----+-----+=====+
    'a' |     |     |     |  0  =
        +-----+-----+-----+=====+
    'b' |     |     |     |  0  =
 i      +-----+-----+-----+=====+
    'c' |     |     |     |  0  =
        +-----+-----+-----+=====+
    'd' |     |     |     |  0  =
        +-----+-----+-----+=====+
    'e' |     |     |     |  0  =
        +-----+-----+-----+=====+
     '' =  0  =  0  =  0  =  0  =
        +=====+=====+=====+=====+





	So our path would look like:


                   j

          'a'   'c'   'e'   ''
        +-----+-----+-----+=====+
    'a' |  3  |     |     |  0  =
        +-----+-----+-----+=====+
    'b' |     |  2  |     |  0  =
 i      +-----+-----+-----+=====+
    'c' |     |  2  |     |  0  =
        +-----+-----+-----+=====+
    'd' |     |     |  1  |  0  =
        +-----+-----+-----+=====+
    'e' |     |     |  1  |  0  =
        +-----+-----+-----+=====+
     '' =  0  =  0  =  0  =  0  =
        +=====+=====+=====+=====+

	This is how we got the result.

	However the way we're going to solve this code is with "Brute Force-ish".
	It's still Dynammic Programming but what we have to do is for every value
	in this cell(except for the 0-cells).
	Since we're going to do a Bottom up we will have to fill the values like
	this: (I will number from 1 onwards)

	THIS ARE NOT VALUES. THIS IS JUST THE ORDER IN WHICH WE COMPUTE THE VALUES
	IN CELLS.


                   j

          'a'   'c'   'e'   ''
        +-----+-----+-----+=====+
    'a' |  15 |  14 | 13  |  0  =
        +-----+-----+-----+=====+
    'b' |  12 |  11 | 10  |  0  =
 i      +-----+-----+-----+=====+
    'c' |  9  |  8  |  7  |  0  =
        +-----+-----+-----+=====+
    'd' |  6  |  5  |  4  |  0  =
        +-----+-----+-----+=====+
    'e' |  3  |  2  |  1  |  0  =
        +-----+-----+-----+=====+
     '' =  0  =  0  =  0  =  0  =
        +=====+=====+=====+=====+





	However, these below, are indeed all the values:


                   j

          'a'   'c'   'e'   ''
        +-----+-----+-----+=====+
    'a' |  3  |  2  |  1  |  0  =
        +-----+-----+-----+=====+
    'b' |  2  |  2  |  1  |  0  =
 i      +-----+-----+-----+=====+
    'c' |  2  |  2  |  1  |  0  =
        +-----+-----+-----+=====+
    'd' |  1  |  1  |  1  |  0  =
        +-----+-----+-----+=====+
    'e' |  1  |  1  |  1  |  0  =
        +-----+-----+-----+=====+
     '' =  0  =  0  =  0  =  0  =
        +=====+=====+=====+=====+

	So this is a Bottom Up Dynammic Programming Solution.

	The code is, now, really simple. It's self-explanatory of the IDEA above.
*/


/* Time  Beats: 76.71% */
/* Space Beats: 52.60% */

/* Time  Complexity: O(n * m) */
/* Space Complexity: O(n * m) */
class Solution{
public:
	int longestCommonSubsequence(std::string& text1, std::string& text2)
	{
		int m = text1.length();
		int n = text2.length();

		std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

		for (int i = m - 1; i >= 0; i--)
		{
			for (int j = n - 1; j >= 0; j--)
			{
				if (text1[i] == text2[j])
					dp[i][j] = 1 + dp[i + 1][j + 1];
				else
					dp[i][j] = std::max(dp[i + 1][j], dp[i][j + 1]);
			}
		}

		return dp[0][0];
	}
};


int
main()
{
	Solution sol;


	/* Example 1 */
	// std::string text1 = "abcde";
	// std::string text2 = "ace";

	/* Example 2 */
	// std::string text1 = "abc";
	// std::string text2 = "abc";

	/* Example 3 */
	// std::string text1 = "abc";
	// std::string text2 = "def";

	/* Example 4 */
	std::string text1 = "oxcpqrsvwf";
	std::string text2 = "shmtulqrypy";


	std::cout << "\n\t==================================";
	std::cout << "\n\t=== LONGEST COMMOM SUBSEQUENCE ===";
	std::cout << "\n\t==================================\n";


	/* Write Input */
	std::cout << "\n\tText 1: \"" << text1 << "\"";
	std::cout << "\n\tText 2: \"" << text2 << "\"\n";


	/* Solution */
	int output = sol.longestCommonSubsequence(text1, text2);


	/* Write Output */
	std::cout << "\n\tOutput: " << output << "\n\n";


	return 0;
}
