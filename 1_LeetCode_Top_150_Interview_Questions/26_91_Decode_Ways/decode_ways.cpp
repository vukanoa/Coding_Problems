#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	91) Decode Ways
	===========================

	============
	Description:
	============

	A message containing letters from A-Z can be encoded into numbers using the
	following mapping:

	'A' -> "1"
	'B' -> "2"
	...
	'Z' -> "26"

	To decode an encoded message, all the digits must be grouped then mapped
	back into letters using the reverse of the mapping above (there may be
	multiple ways). For example, "11106" can be mapped into:

	"AAJF" with the grouping (1 1 10 6)
	"KJF" with the grouping (11 10 6)


	=====
	Note: that the grouping (1 11 06) is invalid because "06" cannot be mapped
	      into 'F' since "6" is different from "06".

	      Given a string s containing only digits, return the number of ways to
	      decode it.

	      The test cases are generated so that the answer fits in a 32-bit
		  integer.
	=====

	==========================================
	FUNCTION: int numDecodings(std::string s);
	==========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "12"
	Output: 2
	Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).

	--- Example 2 ---
	Input: s = "226"
	Output: 3
	Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6),
	or "BBF" (2 2 6).

	--- Example 3 ---
	Input: s = "06"
	Output: 0
	Explanation: "06" cannot be mapped to "F" because of the leading zero
	("6" is different from "06").

	*** Constraints ***
	1 <= s.length <= 100
	s contains only digits and may contain leading zero(s).

*/




/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 5.23% */
/* Space Beats: 72.79% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
public:
	int numDecodings(std::string s)
	{
		std::vector<int> dp(s.length() + 1, 0);
		dp[s.length()] = 1;

		return dfs(s, dp, 0);
	}

private:
	int dfs(std::string& s, std::vector<int>& dp, int i)
	{
		if (dp[i] != 0)
			return dp[i];
		
		if (s[i] == '0')
			return 0;

		int result = dfs(s, dp, i + 1);
		
		/* if (a and (b or (c and d and e))) */
		if (
		       i + 1 < s.length()
			   &&
			   (
		           s[i] == '1' 
		           || 
				   (
		               s[i] == '2'
					   && 
				       (
					       s[i + 1] == '0' ||
		                   s[i + 1] == '1' ||
		                   s[i + 1] == '2' ||
		                   s[i + 1] == '3' ||
		                   s[i + 1] == '4' ||
		                   s[i + 1] == '5' ||
		                   s[i + 1] == '6'
					   )
		           )
		       )
		   )
		{
			result += dfs(s, dp, i + 2);
		}

		dp[i] = result;

		return result;
	}
};




/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats:  5.23% */
/* Space Beats: 92.67% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int memo[100] = {}; // 100 is listed to be a constraint
    int numDecodings(const std::string& s)
	{
        return dp(s, 0);
    }

private:
    int dp(const string& s, int i)
	{
        if (i == s.size())
			return 1;

        if (memo[i] != 0)
			return memo[i];

        int res = 0;

		// Single digit
        if (s[i] != '0')
            res += dp(s, i+1);

		// Two digits
        if (i+1 < s.size() && (s[i] == '1' || s[i] == '2' && s[i+1] <= '6'))
            res += dp(s, i+2);

        return memo[i] = res;
    }
};




/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats:  100% */
/* Space Beats: 92.67% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up { 
public:
    int numDecodings(const std::string& s)
	{
        int n = s.size();
		int dp  = 0;
		int dp1 = 1;
		int dp2 = 0;

        for (int i = n - 1; i >= 0; i--)
		{
			// Single digit
            if (s[i] != '0')
                dp += dp1;

			// Two digits
            if (i+1 < s.size() && (s[i] == '1' || s[i] == '2' && s[i+1] <= '6'))
                dp += dp2;

            dp2 = dp1;
            dp1 = dp;
            dp = 0;
        }

        return dp1;
    }
};
