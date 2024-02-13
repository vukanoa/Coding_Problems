#include <iostream>
#include <vector>
#include <std::unordered_map>

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




/*
    ------------
    --- IDEA ---
    ------------

    Follow up: What if the inputs contain Unicode characters? How would you
    adapt your solution to such a case?

    ASCII defines 128 characters, or 256 for an extended version.

    Unicode character set, on the other hand, defines(less than that) 2^21
    characters, which, map to 0 - 2^21(though not all numbers are currently
    asigned, and some are reserved).

    Unicode is a superset of ASCII and thus it's backward compatible.
    0 - 2^21, although not all

    ASCII   - 128(256) character set, which, therefore, fits in 1 byte.
    Unicode - 2^21     character set, which, therefore, fits in 4 bytes.

    2^21 = 2097152
    2^32 = 4294967296

    Therefore, we can use a HashMap with a key of type "int" since we are sure
    it's able to hold all 2^21 characters.

    Also, we could use a vector that we'd initialize to (2^21, 0), however
    that would, in most cases, be an overkill.

    Lowecase english letters are only 26 characters so it's small enough not to
    care.

*/

/* Time  Beats: 41.97% */
/* Space Beats:  5.00% */

/* Time  Complexity: O(n) */
/*
    Space Complexity: O(1)

    Even though Unicode character set is much much larger than ASCII character
    set, it's still considered O(1) since the Space we need wouldn't grow if
    we increase the length of string s and string t.
*/
class Solution_Unicode {
public:
    bool isAnagram(string s, string t)
    {
        if (s.length() != t.length())
            return false;

        std::unordered_map<int, int> umap_s;
        std::unordered_map<int, int> umap_t;

        for (int i = 0; i < s.length(); i++)
        {
            umap_s[s[i]]++;
            umap_t[t[i]]++;
        }

        return umap_s == umap_t;
    }
};
