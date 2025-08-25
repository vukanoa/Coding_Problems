/*
    ============
    === EASY ===
    ============

    ==============================================
    1047) Remove All Adjacent Duplicates in String
    ==============================================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters. A
    duplicate removal consists of choosing two adjacent and equal letters and
    removing them.

    We repeatedly make duplicate removals on s until we no longer can.

    Return the final string after all such duplicate removals have been made.
    It can be proven that the answer is unique.

    ============================================
    FUNCTION: string removeDuplicates(string s);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abbaca"
    Output: "ca"
    Explanation: 
    For example, in "abbaca" we could remove "bb" since the letters are
    adjacent and equal, and this is the only possible move.  The result of this
    move is that the string is "aaca", of which only "aa" is possible, so the
    final string is "ca".

    --- Example 2 ---
    Input: s = "azxxzy"
    Output: "ay"


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 55.08% */
/* Space Beats: 74.37% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */ // Can be considered O(1) since result is no EXTRA
class Solution {
public:
    string removeDuplicates(string s)
    {
        const int N = s.length();
        string result_str;

        for (int i = 0; i < N; i++)
        {
            if (result_str.empty() || result_str.back() != s[i])
                result_str += s[i];
            else
                result_str.pop_back();
        }

        return result_str;
    }
};
