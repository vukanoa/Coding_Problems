#include <iostream>
#include <vector>

/*
	============
	=== EASY ===
	============

	===========================
	242) Valid Anagram
	===========================

	============
	Description:
	============

	Given two strings s and t, return true if t is an anagram of s, and false
	otherwise.

	An Anagram is a word or phrase formed by rearranging the letters of a
	different word or phrase, typically using all the original letters exactly
	once.


	Follow up: What if the inputs contain Unicode characters? How would you
	adapt your solution to such a case?

	=============================================
	FUNCTION: bool isAnagram(string s, string t);
	=============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "anagram", t = "nagaram"
	Output: true

	--- Example 2 ---
	Input: s = "rat", t = "car"
	Output: false

	*** Constraints ***
	1 <= s.length, t.length <= 5 * 104
	s and t consist of lowercase English letters.


*/


/*
	------------
	--- IDEA ---
	------------

	Initialize two vectors with 26 0's.
	Each index represents one letter in a lowercase English alphabet.
	
	If s and t are not of the same length, they are certainly not anagrams.

	Otherwise, fill the vects and at the end check if those two vectors are
	equal.

	Alternatively, we could have one less vector by making s characters
	increment the values in the vector and t characters decrementing them.

	At the end, instead of comparing two vectors, just check if the vector has
	all the 0's.

	If it does. then return true.
	False otherwise.
	
*/

/* Time  Beats: 74.67% */
/* Space Beats: 81.34% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isAnagram(std::string s, std::string t)
    {
        if (s.length() != t.length())
            return false;
        
        std::vector<int> vec_s (26, 0);
        std::vector<int> vec_t (26, 0);

        for (int i = 0; i < s.length(); i++)
        {
            vec_s[s[i] - 'a']++;
            vec_t[t[i] - 'a']++;
        }

        return vec_s == vec_t;
    }
};
