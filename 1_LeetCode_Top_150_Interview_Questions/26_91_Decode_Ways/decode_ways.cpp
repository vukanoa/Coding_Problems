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

	This Code gives TLE, but I wanted to save it here since you may think about
	it this way at first.

	However, this doesn't pass the "secret tests" since we're doing a lot of
	repeated work.

	Consider this example:
	
	s =  "111111111111111111111111111111111111"
*/

/* This Code gives TLE(Time Limit Exceeded) */

/* Time  Complexity: O(2^n) */
/* Space Complexity: O(n) */
class Solution{
public:
	int numDecodings(std::string s)
	{
		int count = 0;

		dfs_backtracking(s, count, 0);

		return count;
	}

private:
	void dfs_backtracking(std::string& s, int& count, int i)
	{
		if (i == s.length())
		{
			count++;
			return;
		}
		else if (s[i] == '0')
			return;

		/* One digit */
		dfs_backtracking(s, count, i+1);

		/* Two digits */
		if (i + 1 < s.length())
		{
			if (s[i] == '1')
				dfs_backtracking(s, count, i+2);
			else if (s[i] == '2' && s[i+1] >= '0' && s[i+1] < '7')
				dfs_backtracking(s, count, i+2);
		}
	}
};




/*
	------------
	--- IDEA ---
	------------

	Example 1:

	                           "11106"

	        ______________________._______________________
	        __________1______________________11___________
	        ____1__________11___________1__________10_____
	        _1____10_____F___________F___________6________
	        _____6_______________________________T________
	             T

	We have two "T"s, so the answer is: 2.

	For recursion to stop It's either that:
	    1. dp[i] is not 0

	       or

	    2. s[i] == 0


	if s[i] == 0, that's F. It means that "combination" is not possible, thus
	return 0.

	Essentially: dp[i] = dp[i + 1] + dp[i + 2];

	And we do that recursively.

	At one point, index "i" will get out of bounds if a combination is okay, so
	that's why we have to have: dp(s.length() + 1, 0) and that's why we have to
	assign dp[s.length()] = 1;

	If we have, successfully, gone through all the elements, without returning
	0, that means that "path" is valid and must be included in overall count of
	results.

	So:
	    dp[s.length() + 1] = 1
	
	is necessary.

	
	Example 2:

	                            "12"
	                         ___________
	                         _____1_____
	                         __2____12__
	                         T_____T____
	
	Again, two T's, so the answer is: 2
	
	Go through the code for this example and you'll get it.
	
*/

/* Time  Beats: 5.23% */
/* Space Beats: 72.79% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution { 
public:
	int numDecodings(const std::string& s)
	{
		std::vector<int> dp(s.length() + 1, 0);
		dp[s.length()] = 1;

		return backtracking(s, dp, 0);
	}

private:
	int backtracking(const std::string& s, std::vector<int>& dp, int i)
	{
		if (dp[i] != 0)
			return dp[i];

		if (s[i] == '0')
			return 0;

		int result = backtracking(s, dp, i+1);

		if (i + 1 < s.length())
		{
			std::string str = s.substr(i, 2);
			int num = std::stoi(str);

			if (num >= 1 && num <= 26)
				result += backtracking(s, dp, i + 2);
		}

		dp[i] = result;

		return dp[i];
	}
};




/*
	------------
	--- IDEA ---
	------------


	Example 1:

	                            "11106"

	        ______________________._______________________
	        __________1______________________11___________
	        ____1__________11___________1__________10_____
	        _1____10_____F___________F___________6________
	        _____6_______________________________T________
	             T
	
	We have two "T"s, so the answer is: 2.

	For recursion to stop It's either that:
	    1. memo[i] is not 0

	       or

	    2. s[i] == 0


	if s[i] == 0, that's F. It means that "combination" is not possible, thus
	return 0.

	Essentially: memo[i] = memo[i + 1] + memo[i + 2];

	And we do that recursively.

	At one point, index "i" will get out of bounds if a combination is okay, so
	that's why we have to have: memo(s.length() + 1, 0) and that's why we have to
	assign memo[s.length()] = 1;

	If we have, successfully, gone through all the elements, without returning
	0, that means that "path" is valid and must be included in overall count of
	results.

	So:
	    memo[s.length() + 1] = 1
	
	is necessary.

	
	Example 2:

	                            "12"
	                         ___________
	                         _____1_____
	                         __2____12__
	                         T_____T____
	
	Again, two T's, so the answer is: 2
	
	Go through the code for this example and you'll get it.
	ODO
	
*/

/* Time  Beats:  5.23% */
/* Space Beats: 92.67% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
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

		/* One digit */
		if (s[i] != '0')
			res += dp(s, i+1);

		/* Two digits */
		if (i+1 < s.size() && (s[i] == '1' || s[i] == '2' && s[i+1] <= '6'))
			res += dp(s, i+2);

		return memo[i] = res;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Bottom-Up approach.

	Consider these Examples:
	    1. s = "226"
		2. s = "229"
		3. s = "06"

	1. s = "226"
	    
		s  = "2 2 6"
	    dp = [0 0 0 0]
		      0 1 2 3
	    
		We're essentially looking at subproblems.

		For example, if we had only "6" - In how many ways could we decode it?
		The answer is, obviously, 1.

		So does that help us somehow?

		What if we had "26", but we've already concluded that string "6" can
		be decoded only in 1 way.

		Can we use that to our advantage? Yes!

		First, we have to check if the current digit(2 in our case) is != 0
		because string starting with 0 cannot be decoded in any way:
		    "0", "033243", "0111", ...

		If it's not 0, then we can count in how many ways can we decode 6 and
		then we have to consider if we can take 6(in our case) as our 2nd digit
		of a 2-digit number.

		In this case "26" can indeed be decoded. It's going to be letter 'Z'.

		So we add that as well. Now we know for a fact that string "26" can be
		decoded in 2 ways.
		    1. 2 6 --> BF
			2. 26  --> Z

		Now we have to see in how many ways can a string "226" be decoded.

		Again, can we use our, already computed, result for string "26"? Yes!

		We are essentially going to have a vector dp which will store number of
		ways in which we can decode from that digit until the end of the
		string.

		Simulation of example "226" would look like this:
		    "2 2 6"
		    [0 0 0 1]
		           ^
		 __________|
		|
		We know for a fact that an empty string can be "decoded" in only one
		way, i.e. no letter at all.

		##################
		### SIMULATION ###
		##################
		1)
		              i
		    s  = "2 2 6"
		    dp = [0 0 0 1]

		2)
		            i
		    s  = "2 2 6"
		    dp = [0 0 1 1]

		3)
		          i
		    s  = "2 2 6"
		    dp = [0 2 1 1]

		4)
		    dp = [3 2 1 1]
	


	2. s = "229"
		##################
		### SIMULATION ###
		##################
		1)
		              i
		    s  = "2 2 9"
		    dp = [0 0 0 1]

		2)
		            i
		    s  = "2 2 9"
		    dp = [0 0 1 1]

		3)
		          i
		    s  = "2 2 9"
		    dp = [0 1 1 1]

		4)
		    dp = [2 1 1 1]


	3. s = "06"
		##################
		### SIMULATION ###
		##################
		1)
		            i
		    s  = "0 6"
		    dp = [0 0 1]

		2)
		          i
		    s  = "0 6"
		    dp = [0 1 1]

		3)
		    dp = [0 1 1]

		We're returning dp[0] always.

*/

/* Time  Beats:   100% */
/* Space Beats: 32.02% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Bottom_Up {
public:
	int numDecodings(std::string s)
	{
		std::vector<int> dp(s.length() + 1, 0);
		int n = dp.size();

		dp[n-1] = 1; // or dp[s.length()] = 1

		for (int i = s.length()-1; i >= 0; i--)
		{
			/* One digit */
			if (s[i] != '0')
				dp[i] += dp[i + 1];

			/* Two digits */
			if (i + 1 < s.length() && (s[i] == '1' || (s[i] == '2' && s[i+1] >= '0' && s[i+1] < '7')))
				dp[i] += dp[i + 2];
		}

		return dp[0];
	}
};




/*
	------------
	--- IDEA ---
	------------

	Same idea, but implemented in O(1) Space because we can see that we don't
	need to use entire array of dp, but only 3 elements.

	Similar to a House Robber problem or the Kadane's Algorithm.

*/

/* Time  Beats:  100% */
/* Space Beats: 92.67% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up_Space_Efficient { 
public:
	int numDecodings(const std::string& s)
	{
		int n = s.length();

		int dp  = 0;
		int dp1 = 1;
		int dp2 = 0;

		for (int i = n - 1; i >= 0; i--)
		{
			/* One digit */
			if (s[i] != '0')
				dp += dp1;

			/* Two digits */
			if (i+1 < s.size() && (s[i] == '1' || s[i] == '2' && s[i+1] <= '6'))
				dp += dp2;

			dp2 = dp1;
			dp1 = dp;
			dp = 0;
		}

		return dp1;
	}
};
