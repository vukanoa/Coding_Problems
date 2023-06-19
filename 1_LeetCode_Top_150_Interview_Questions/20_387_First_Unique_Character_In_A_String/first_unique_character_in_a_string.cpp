#include <iostream>

/*
	============
	=== EASY ===
	============

	=======================================
	387) First Unique Character In a String
	=======================================

	============
	Description:
	============

	Given a string s, find the first non-repeating character in it and return
	its index. If it does not exist, return -1.

	======================================
	FUNCTION: int firstUniqChar(string s);
	======================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "leetcode"
	Output: 0

	--- Example 2 ---
	Input: s = "loveleetcode"
	Output: 2

	--- Example 3 ---
	Input: s = "aabb"
	Output: -1	

	*** Constraints ***
    1 <= s.length <= 105
    s consists of only lowercase English letters.

*/


/*
	------------
	--- IDEA ---
	------------

	Fill the vector "map" with occurrences of each letter in the string.

	After that, just iterate through the array from the beginning(since we
	have to return the first one that doens't repeat) and as we iterate, just
	check if that letter has number of occurrences of 1.

	If it is:
		return index of that number;
	
	Otherwise continue iterating through the array. If it happens that there
	are no numbers with occurrences of 1, then return -1 at the very end.
	
*/

/* Time  Beats: 97.95% */
/* Space Beats: 89.28% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int firstUniqChar(string s)
    {
		// 26 is the number of lowercase English letters
        std::vector<int> map(26, 0); // This is constant, hence Space O(1)

        for (char& c : s)
            map[c - 'a']++;

        for (int i = 0; i < s.length(); i++)
        {
            if (map[s[i] - 'a'] == 1)
                return i;
        }

        return -1;
    }
};
