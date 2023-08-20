#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	====================================================================
	1239) Maximum Length Of a Concatenated String with Unique Characters
	====================================================================

	============
	Description:
	============

	You are given an array of strings arr. A string s is formed by the
	concatenation of a subsequence of arr that has unique characters.

	Return the maximum possible length of s.

	A subsequence is an array that can be derived from another array by
	deleting some or no elements without changing the order of the remaining
	elements.

	=======================================================
	FUNCTION: int maxLength(std::vector<std::string>& str);
	=======================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: arr = ["un","iq","ue"]
	Output: 4
	Explanation: All the valid concatenations are:
	- ""
	- "un"
	- "iq"
	- "ue"
	- "uniq" ("un" + "iq")
	- "ique" ("iq" + "ue")
	Maximum length is 4.


	--- Example 2 ---
	Input: arr = ["cha","r","act","ers"]
	Output: 6
	Explanation: Possible longest valid concatenations are "chaers" ("cha" + "ers") and "acters" ("act" + "ers").


	--- Example 3 ---
	Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
	Output: 26
	Explanation: The only string in arr has all 26 characters.


	*** Constraints ***
	1 <= arr.length <= 16
	1 <= arr[i].length <= 26
	arr[i] contains only lowercase English letter

*/

/* Time  Beats: 33.14% */
/* Space Beats: 53.02% */

/* Time  Complexity: O(2^n * 26) --> O(2^n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int maxLength(vector<string>& arr)
	{
		return backtracking(arr, "", 0);
    }

	int backtracking(std::vector<std::string>& arr, std::string str, int index)
	{
	    // Use set to check if the string contains all unique characters
        std::unordered_set<char>s(str.begin(), str.end());

        if (s.size() != str.length()) 
            return 0;

        int ret = str.length();
        for (int i = index; i < arr.size(); i++)
            ret = max(ret, backtracking(arr, str+arr[i], i+1));

        return ret;
	}
};
