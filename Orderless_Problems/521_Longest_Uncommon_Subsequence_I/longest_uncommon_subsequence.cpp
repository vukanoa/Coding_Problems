#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===================================
    521) Longest Uncommon Subsequence I
    ===================================

    ============
    Description:
    ============

    Given two strings a and b, return the length of the longest uncommon
    subsequence between a and b. If no such uncommon subsequence exists, return
    -1.

    An uncommon subsequence between two strings is a string that is a
    subsequence of exactly one of them.

    ================================================
    FUNCTION: int findLUSlength(string a, string b);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: a = "aba", b = "cdc"
    Output: 3
    Explanation: One longest uncommon subsequence is "aba" because "aba" is a
                 subsequence of "aba" but not "cdc". Note that "cdc" is also a
                 longest uncommon subsequence.

    --- Example 2 ---
    Input: a = "aaa", b = "bbb"
    Output: 3
    Explanation: The longest uncommon subsequences are "aaa" and "bbb".

    --- Example 3 ---
    Input: a = "aaa", b = "aaa"
    Output: -1
    Explanation: Every subsequence of string a is also a subsequence of string
                 b. Similarly, every subsequence of string b is also a
                 subsequence of string a. So the answer would be -1.


    *** Constraints ***
    1 <= a.length, b.length <= 100
    a and b consist of lower-case English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Why is this even a problem?

*/

/* Time  Beats: 100.00% */
/* Space Beats:  70.66% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findLUSlength(string a, string b)
    {
        if (a == b)
            return -1;

        return max(a.length(), b.length());
    }
};
