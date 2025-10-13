/*
    ============
    === EASY ===
    ============

    =======================================
    2027) Minimum Moves to Convert a String
    =======================================

    ============
    Description:
    ============

    You are given a string s consisting of n characters which are either
    'X' or 'O'.

    A move is defined as selecting three consecutive characters of s and
    converting them to 'O'. Note that if a move is applied to the character
    'O', it will stay the same.

    Return the minimum number of moves required so that all the characters of s
    are converted to 'O'.

    =====================================
    FUNCTION: int minimumMoves(string s);
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "XXX"
    Output: 1
    Explanation: XXX -> OOO
    We select all the 3 characters and convert them in one move.

    --- Example 2 ---
    Input: s = "XXOX"
    Output: 2
    Explanation: XXOX -> OOOX -> OOOO
    We select the first 3 characters in the first move, and convert them to 'O'
    Then we select the last 3 characters and convert them so that the final
    string contains all 'O's.

    --- Example 3 ---
    Input: s = "OOOO"
    Output: 0
    Explanation: There are no 'X's in s to convert.


    *** Constraints ***
    3 <= s.length <= 1000
    s[i] is either 'X' or 'O'.

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
/* Space Beats:  65.86% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minimumMoves(string s)
    {
        const int N = s.length();
        int result = 0;

        int i = 0;
        while (i < N)
        {
            if (s[i] == 'X')
            {
                result++;
                i += 2;
            }

            // Increment
            i++;
        }

        return result;
    }
};
