/*
    ============
    === EASY ===
    ============

    =====================================================
    1790) Check If One String Swap Can Make Strings Equal
    =====================================================

    ============
    Description:
    ============

    You are given two strings s1 and s2 of equal length. A string swap is an
    operation where you choose two indices in a string (not necessarily
    different) and swap the characters at these indices.

    Return true if it is possible to make both strings equal by performing at
    most one string swap on exactly one of the strings. Otherwise, return false

    ====================================================
    FUNCTION: bool areAlmostEqual(string s1, string s2);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s1 = "bank", s2 = "kanb"
    Output: true
    Explanation: For example, swap the first character with the last character
                 of s2 to make "bank".

    --- Example 2 ---
    Input: s1 = "attack", s2 = "defend"
    Output: false
    Explanation: It is impossible to make them equal with one string swap.

    --- Example 3 ---
    Input: s1 = "kelb", s2 = "kelb"
    Output: true
    Explanation: The two strings are already equal, so no string swap operation
                 is required.


    *** Constraints ***
    1 <= s1.length, s2.length <= 100
    s1.length == s2.length
    s1 and s2 consist of only lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    For one string to be "one swap away" from the other, the first necessary
    condition is that both strings contain the exact same characters in the
    exact same amount.

    However, that's not the only condition that is necessary. To be "one swap
    away", two strings either have to:
        1) Be equal, or
        2) Not have the same characters at EXACTLY 2 indices.

    If they are equal, it's clear that we shall return true. That's why they've
    told us this piece of information:

        "A string swap is an operation where you choose two indices in a string
         (NOT NECESSARILY DIFFERENT)"

    "Not necessarily different" is crucial. It is precisely for that reason
    that we are allowed to "not swap" at all effectively.

    If we picked index 2 and index 2, and "swap" those two characters, we won't
    change anything.

    That's why we're allowed to return "true" if two strings are equal.


    However, the 2nd option is more "tricky". Imagine we have these two strings

        s1 = "abcd"
        s2 = "dcba"

    In this case first condition(i.e. that both strings contain the exact same
    characters in the exact same amount) is fulfilled.

    However, the second condition(i.e. Not have the same characters at EXACTLY
    2 indices) is not.

    They differ at index 0, index 1, index 2, index 3.
    We cannot swap all of them, we're allowed to perform only a single swap.
    That's why we return "false".

    However, if we had

        s1 = "abcd"
        s2 = "abdc"

    They only differ at exactly 2 indices: index 2 and index 3. If we swap
    those two characters(only in either of the strings), they will become
    equal.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  97.48% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool areAlmostEqual(string s1, string s2)
    {
        const int N = s1.length();

        if (s1 == s2)
            return true;

        vector<int> counter1(26, 0);
        vector<int> counter2(26, 0);

        int different_at_same_indices = 0;
        for (int i = 0; i < N; i++)
        {
            counter1[s1[i] - 'a']++;
            counter2[s2[i] - 'a']++;

            if (s1[i] != s2[i])
                different_at_same_indices++;
        }

        return counter1 == counter2 && different_at_same_indices == 2;
    }
};
