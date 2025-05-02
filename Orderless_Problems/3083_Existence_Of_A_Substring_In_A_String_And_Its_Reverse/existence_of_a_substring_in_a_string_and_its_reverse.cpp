/*
    ============
    === EASY ===
    ============

    ===========================================================
    3083) Existence of a Substrings in a String and Its Reverse
    ===========================================================

    ============
    Description:
    ============

    Given a string s, find any substring of length 2 which is also present in
    the reverse of s.

    Return true if such a substring exists, and false otherwise.

    ============================================
    FUNCTION: bool isSubstringPresent(string s);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "leetcode"
    Output: true
    Explanation: Substring "ee" is of length 2 which is also present in
                 reverse(s) == "edocteel".

    --- Example 2 ---
    Input: s = "abcba"
    Output: true
    Explanation: All of the substrings of length 2 "ab", "bc", "cb", "ba" are
                 also present in reverse(s) == "abcba".


    --- Example 3 ---
    Input: s = "abcd"
    Output: false
    Explanation: There is no substring of length 2 in s, which is also present
                 in the reverse of s.


    *** Constraints ***
    1 <= s.length <= 100
    s consists only of lowercase English letters.

*/

#include <algorithm>
#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 17.93% */
/* Space Beats: 33.47% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool isSubstringPresent(string s)
    {
        const int N = s.size();
        int result = 0;

        string copy_s = s;
        reverse(copy_s.begin(), copy_s.end());

        unordered_set<string> uset;
        for (int i = 0; i < N-1; i++)
            uset.insert(s.substr(i, 2));

        for (int i = 0; i < N-1; i++)
        {
            string substr = copy_s.substr(i, 2);
            if (uset.find(substr) != uset.end())
                return true;
        }

        return false;
    }
};
