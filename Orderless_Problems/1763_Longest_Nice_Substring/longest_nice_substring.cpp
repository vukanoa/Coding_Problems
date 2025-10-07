/*
    ============
    === EASY ===
    ============

    ============================
    1763) Longest Nice Substring
    ============================

    ============
    Description:
    ============

    A string s is nice if, for every letter of the alphabet that s contains, it
    appears both in uppercase and lowercase. For example, "abABB" is nice
    because 'A' and 'a' appear, and 'B' and 'b' appear. However, "abA" is not
    because 'b' appears, but 'B' does not.

    Given a string s, return the longest substring of s that is nice. If there
    are multiple, return the substring of the earliest occurrence. If there are
    none, return an empty string.

    ================================================
    FUNCTION: string longestNiceSubstring(string s);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "YazaAay"
    Output: "aAa"
    Explanation: "aAa" is a nice string because 'A/a' is the only letter of the
                 alphabet in s, and both 'A' and 'a' appear. "aAa" is the
                 longest nice substring.

    --- Example 2 ---
    Input: s = "Bb"
    Output: "Bb"
    Explanation: "Bb" is a nice string because both 'B' and 'b' appear. The
                 whole string is a substring.

    --- Example 3 ---
    Input: s = "c"
    Output: ""
    Explanation: There are no nice substrings.


    *** Constraints ***
    1 <= s.length <= 100
    s consists of uppercase and lowercase English letters.

*/

#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 67.24% */
/* Space Beats: 29.67% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    string longestNiceSubstring(string s)
    {
        const int N = s.length();
        if (N < 2)
            return "";
        
        unordered_set<char> uset(s.begin(), s.end());
        
        // Find the first character that breaks the "nice" property
        for (int i = 0; i < N; i++)
        {
            char chr = s[i];
            char opposite = islower(chr) ? (chr - 'a' + 'A') : (chr - 'A' + 'a');
            
            // If the opposite case doesn't exist--this chr breaks niceness
            if (uset.find(opposite) == uset.end())
            {
                // Split at this position and recursively check both sides
                string left  = longestNiceSubstring(s.substr(0, i));
                string right = longestNiceSubstring(s.substr(i + 1));
                
                return left.length() >= right.length() ? left : right;
            }
        }
        
        // If we never found a breaking character, the entire string is nice
        return s;
    }
};
