/*
    ============
    === EASY ===
    ============

    =========================================================
    4043) Count Rotations with Exactly K Equal Adjacent Pairs
    =========================================================

    ============
    Description:
    ============

    You are given a string s of length n and an integer k.

    A cyclic rotation of s is obtained by choosing a prefix of s whose length
    is between 0 and n - 1 (inclusive), and moving it to the end of the string
    while preserving the order of all characters.

    For every cyclic rotation of s, let its score be the number of indices i
    such that 0 <= i < n - 1 and the characters at positions i and i + 1 are
    equal.

    Return the number of cyclic rotations of s whose score equals k.

    ==============================================
    FUNCTION: int countRotations(string s, int k);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aab", k = 1
    Output: 2
    Explanation:
    The cyclic rotations of s are:
        "aab": The characters at positions 0 and 1 are equal, so score = 1.
        "aba": No two adjacent characters are equal, so score = 0.
        "baa": The characters at positions 1 and 2 are equal, so score = 1.
    Since score equals k for 2 cyclic rotations of s, the answer is 2.

    --- Example 2 ---
    Input: s = "abca", k = 0
    Output: 1
    Explanation:
    The cyclic rotations of s are:
        "abca": No two adjacent characters are equal, so score = 0.
        "bcaa": The characters at positions 2 and 3 are equal, so score = 1.
        "caab": The characters at positions 1 and 2 are equal, so score = 1.
        "aabc": The characters at positions 0 and 1 are equal, so score = 1.
    Since score equals k for only 1 cyclic rotation of s, the answer is 1.


    *** Constraints ***
    2 <= n == s.length <= 100
    s only consists of lowercase English letters.
    0 <= k <= n - 1

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  44.26% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int countRotations(string s, int k)
    {
        const int N = s.size();
        int result = 0;

        s += s; // Concatenate s to iself

        int score = 0;
        int L = 0;
        int R = 0;
        while (R < N-1)
        {
            if (s[R] == s[R+1])
                ++score;

            // Increment
            ++R;
        }

        if (score == k)
            ++result;

        while (R < 2*N - 2)
        {
            if (s[L] == s[L+1]) --score;
            if (s[R] == s[R+1]) ++score;

            if (score == k)
                ++result;

            // Increment
            ++L;
            ++R;
        }

        return result;
    }
};
