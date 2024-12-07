#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === EASY ===
    ============

    ===========================
    392) Is Subsequence
    ===========================

    ============
    Description:
    ============

    Given two strings s and t, return true if s is a subsequence of t, or false
    otherwise.

    A subsequence of a string is a new string that is formed from the original
    string by deleting some (can be none) of the characters without disturbing
    the relative positions of the remaining characters. (i.e., "ace" is a
    subsequence of "abcde" while "aec" is not).

    Follow up: Suppose there are lots of incoming s, say s1, s2, ..., sk where
    k >= 10^9, and you want to check one by one to see if t has its
    subsequence.
    In this scenario, how would you change your code?

    =================================================
    FUNCTION: bool isSubsequence(string s, string t);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abc", t = "ahbgdc"
    Output: true

    --- Example 2 ---
    Input: s = "axc", t = "ahbgdc"
    Output: false

    *** Constraints ***
    0 <= s.length <= 100
    0 <= t.length <= 104
    s and t consist only of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100% */
/* Space Beats: 55.75% */

/* Time  Complexity: O(std::min(s.length(), t.length()))) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isSubsequence(string s, string t)
    {
        int i = 0;
        int j = 0;

        while (i < s.length() && j < t.length())
        {
            if (s[i] == t[j])
                i++;

            j++;
        }

        return i == s.length() ? true : false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

// It seems slow and inefficient, but that's because we are testing it on the
// original Test cases and not as suggested in Follow-Up.

/* Time  Beats: 5.09% */
/* Space Beats: 5.06% */

/* Time  Complexity: O(n + m) */ // n <==> t.length()   m <==> s.length()
/* Space Complexity: O(n * k) */ // k is the average number of unique characters in t
class Solution_Follow_Up { // Dynamic Progrmaming
public:
    bool isSubsequence(string& s, string& t)
    {
        const int n = t.length();
        std::vector<std::unordered_map<char, int>> next(n + 1);

        // Build the `next` vector in reverse order
        for (int i = n-1; i >= 0; i--)
        {
            next[i] = next[i + 1]; // Copy the next map
            next[i][t[i]] = i + 1; // Update the current character's position
        }

        int i = 0;
        for (const char& chr : s)
        {
            if (next[i].count(chr))
                i = next[i][chr]; // Move to the next position in `t`
            else
                return false; // Character not found in `t`
        }

        return true; // All characters in `s` were found in sequence in `t`
    }
};
