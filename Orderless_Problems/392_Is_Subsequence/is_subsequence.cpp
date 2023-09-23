#include <iostream>
#include <vector>

/*
	============
	=== EASY ===
	============

	===========================
	392) Is Subsequence
	===========================

	============
	Description:
	============

	Given two strings s and t, return true if s is a subsequence of t, or false
	otherwise.

	A subsequence of a string is a new string that is formed from the original
	string by deleting some (can be none) of the characters without disturbing
	the relative positions of the remaining characters. (i.e., "ace" is a
	subsequence of "abcde" while "aec" is not).

	Follow up: Suppose there are lots of incoming s, say s1, s2, ..., sk where
	k >= 10^9, and you want to check one by one to see if t has its
	subsequence.
	In this scenario, how would you change your code?

	=================================================
	FUNCTION: bool isSubsequence(string s, string t);
	=================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "abc", t = "ahbgdc"
	Output: true

	--- Example 2 ---
	Input: s = "axc", t = "ahbgdc"
	Output: false

	*** Constraints ***
	0 <= s.length <= 100
	0 <= t.length <= 104
	s and t consist only of lowercase English letters.

*/

/* Time  Beats: 100% */
/* Space Beats: 90.84% */

/* Time  Complexity: O(t.length()) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isSubsequence(string s, string t)
    {
        if (s.length() == 0 && t.length() == 0)
            return true;
        else if (s.length() == 0 && t.length() > 0)
            return true;
        else if (s.length() > 0 && t.length() == 0)
            return false;
        
        int i = 0;
        int j = 0;

        for (j = 0; j < t.length(); j++)
        {
            if (s[i] == t[j])
            {
                i++;
                if (i == s.size())
                    return true;
            }
        }

        return false;
    }
};




/* Time  Beats: 100% */
/* Space Beats: 55.75% */

/* Time  Complexity: O(std::min(s.length(), t.length()))) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isSubsequence(string s, string t)
    {       
        int i = 0;
        int j = 0;

        while (i < s.length() && j < t.length())
        {
            if (s[i] == t[j])
                i++;
                
            j++;
        }

        return i == s.length() ? true : false;
    }
};
