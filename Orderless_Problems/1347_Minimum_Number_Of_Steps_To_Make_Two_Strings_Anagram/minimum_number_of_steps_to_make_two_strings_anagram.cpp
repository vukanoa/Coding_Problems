/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    1347) Minimum Number of Steps to Make Two Strings Anagram
    =========================================================

    ============
    Description:
    ============


    You are given two strings of the same length s and t. In one step you can
    choose any character of t and replace it with another character.

    Return the minimum number of steps to make t an anagram of s.

    An Anagram of a string is a string that contains the same characters with a
    different (or the same) ordering.


    ===========================================
    FUNCTION: int minSteps(string s, string t);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "bab", t = "aba"
    Output: 1
    Explanation: Replace the first 'a' in t with b, t = "bba" which is anagram
                 of s.

    --- Example 2 ---
    Input: s = "leetcode", t = "practice"
    Output: 5
    Explanation: Replace 'p', 'r', 'a', 'i' and 'c' from t with proper
                 characters to make t anagram of s.

    --- Example 3 ---
    Input: s = "anagram", t = "mangaar"
    Output: 0
    Explanation: "anagram" and "mangaar" are anagrams. 


    *** Constraints ***
    1 <= s.length <= 5 * 10^4
    s.length == t.length
    s and t consist of lowercase English letters only.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 56.71% */
/* Space Beats: 35.30% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minSteps(string s, string t)
    {
        int result = 0;

        vector<int> freq(26, 0);
        for (int i = 0; i < s.size(); i++)
        {
            freq[t[i] - 'a']++;
            freq[s[i] - 'a']--;
        }

        for (int i = 0; i < 26; i++)
            result += max(0, freq[i]);
        
        return result;
    }
};
