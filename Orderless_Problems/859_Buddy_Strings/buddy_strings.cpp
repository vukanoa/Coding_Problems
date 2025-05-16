/*
    ============
    === EASY ===
    ============

    ===========================
    859) Buddy Strings
    ===========================

    ============
    Description:
    ============


    Given two strings s and goal, return true if you can swap two letters in s
    so the result is equal to goal, otherwise, return false.

    Swapping letters is defined as taking two indices i and j (0-indexed) such
    that i != j and swapping the characters at s[i] and s[j].

        For example, swapping at indices 0 and 2 in "abcd" results in "cbad".

    ===================================================
    FUNCTION: bool buddyStrings(string s, string goal);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "ab", goal = "ba"
    Output: true
    Explanation: You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is
                 equal to goal.

    --- Example 2 ---
    Input: s = "ab", goal = "ab"
    Output: false
    Explanation: The only letters you can swap are s[0] = 'a' and s[1] = 'b',
                 which results in "ba" != goal.

    --- Example 3 ---
    Input: s = "aa", goal = "aa"
    Output: true
    Explanation: You can swap s[0] = 'a' and s[1] = 'a' to get "aa", which is
                 equal to goal.


    *** Constraints ***
    1 <= s.length, goal.length <= 2 * 10^4
    s and goal consist of lowercase letters.

*/

#include <set>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  10.82% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool buddyStrings(string s, string goal)
    {
        if (s.length() != goal.length())
            return false;

        if (s == goal && unordered_set<char>(s.begin(), s.end()).size() < s.size())
            return true;

        vector<int> diff;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] != goal[i])
                diff.push_back(i);
        }

        return diff.size() == 2 && s[diff[0]] == goal[diff[1]] && s[diff[1]] == goal[diff[0]];
    }
};
