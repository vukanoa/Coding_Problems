/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    3983) Subsequence After One Replacement
    =======================================

    ============
    Description:
    ============

    You are given two strings s and t consisting of lowercase English letters.

    You may choose at most one index in s and replace the character at that
    index with any lowercase English letter.

    Return true if it is possible to make s a subsequence of t; otherwise,
    return false.

    ======================================================
    FUNCTION: bool canMakeSubsequence(string s, string t);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "cat", t = "chat"
    Output: true
    Explanation:
        + Replace s[1] from 'a' to 'h'. The resulting string is "cht".

        + "cht" is a subsequence of "chat" because we can match 'c', 'h', and
          't' in order.


    --- Example 2 ---
    Input: s = "plane", t = "apple"
    Output: false
    Explanation:
        + The characters 'p', 'l', and 'e' can be matched in t, but the
           remaining characters cannot be matched while preserving the required
           order.

        + Even after replacing any one character in s, it is impossible to make
          s a subsequence of t.


    *** Constraints ***
    1 <= s.length, t.length <= 10^5
    s and t consist only of lowercase English letters.

*/

#include <string>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Greedy {
public:
    bool canMakeSubsequence(string s, string t)
    { 
        const int N = s.size();
        const int M = t.size();

        if (N > M)
            return false;

        int i = 0; // We can skip at most ONE
        int j = 0; // Everything has to match

        for (const auto& chr : t)
        {
            if (s[i] == chr)
                i++;

            i = max(i, j+1); // This makes AT MOST one skip

            if (s[j] == chr)
                j++;

            if (i == N || j == N)
                return true;
        }

        return false;
    }
};
