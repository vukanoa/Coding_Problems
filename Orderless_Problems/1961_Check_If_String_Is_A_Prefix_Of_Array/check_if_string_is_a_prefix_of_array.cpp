/*
    ============
    === EASY ===
    ============

    ==========================================
    1961) Check if String Is a Prefix of Array
    ==========================================

    ============
    Description:
    ============

    Given a string s and an array of strings words, determine whether s is a
    prefix string of words.

    A string s is a prefix string of words if s can be made by concatenating
    the first k strings in words for some positive k no larger than
    words.length.

    Return true if s is a prefix string of words, or false otherwise.

    ===============================================================
    FUNCTION: bool isPrefixString(string s, vector<string>& words);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "iloveleetcode", words = ["i","love","leetcode","apples"]
    Output: true
    Explanation:
    s can be made by concatenating "i", "love", and "leetcode" together.

    --- Example 2 ---
    Input: s = "iloveleetcode", words = ["apples","i","love","leetcode"]
    Output: false
    Explanation:
    It is impossible to make s using a prefix of arr.


    *** Constraints ***
    1 <= words.length <= 100
    1 <= words[i].length <= 20
    1 <= s.length <= 1000
    words[i] and s consist of only lowercase English letters.

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

/* Time  Beats: 100.00% */
/* Space Beats:  98.25% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool isPrefixString(string s, vector<string>& words)
    {
        const int N = s.length();
        const int M = words.size();
        int i = 0;

        for (int j = 0; j < M && i < N; j++)
        {
            for (const auto& chr : words[j])
            {
                if (i == N || s[i++] != chr)
                    return false;
            }
        }

        return i == N;
    }
};
