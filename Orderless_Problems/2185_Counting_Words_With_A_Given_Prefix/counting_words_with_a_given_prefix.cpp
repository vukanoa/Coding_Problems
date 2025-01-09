/*
    ============
    === EASY ===
    ============

    ========================================
    2185) Counting Words with a Given Prefix
    ========================================

    ============
    Description:
    ============

    You are given an array of strings words and a string pref.

    Return the number of strings in words that contain pref as a prefix.

    A prefix of a string s is any leading contiguous substring of s.

    ==============================================================
    FUNCTION: int prefixCount(vector<string>& words, string pref);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["pay","attention","practice","attend"], pref = "at"
    Output: 2
    Explanation: The 2 strings that contain "at" as a prefix are: "attention"
                 and "attend".

    --- Example 2 ---
    Input: words = ["leetcode","win","loops","success"], pref = "code"
    Output: 0
    Explanation: There are no strings that contain "code" as a prefix.


    *** Constraints ***
    1 <= words.length <= 100
    1 <= words[i].length, pref.length <= 100
    words[i] and pref consist of lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simple Brute-Force. If you know about the built-in function "find", then
    this becomes even simpler and more efficient.

    if function "find" finds a prefix within the parentheses in the string,
    it will return a starting index. Otherwise it will return "string::npos",
    i.e. -1.

    However, since we're looking for a PREFIX, it MUST begin at index 0. Thus,
    if our "find" funciton returns anything other than 0, we know we did NOT
    find our prefix.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  85.23% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int prefixCount(vector<string>& words, string pref)
    {
        const int N = words.size();
        int result = 0;

        for (const string& word : words)
        {
            if (pref.length() <= word.length() && word.find(pref) == 0)
                result++;
        }

        return result;
    }
};
