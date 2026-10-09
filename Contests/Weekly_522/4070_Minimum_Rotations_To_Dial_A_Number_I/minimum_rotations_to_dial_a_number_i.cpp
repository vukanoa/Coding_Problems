/*
    ============
    === EASY ===
    ============

    ==========================================
    4070) Minimum Rotations to Dial a Number I
    ==========================================

    ============
    Description:
    ============

    You are given a string s of length 10 consisting of digits.

    The dial contains the digits 0 through 9 in order and is circular, so 0 and
    9 are adjacent. The pointer initially points to 0.

    To dial each digit of s in order, rotate the pointer until it points to
    that digit. Each rotation moves the pointer to an adjacent digit, and you
    may rotate in either direction. Dialing a digit that the pointer already
    points to requires no rotations.

    Return the minimum total number of rotations needed to dial every digit of
    s.

    =====================================
    FUNCTION: int minRotations(string s);
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "0192837465"
    Output: 25

    --- Example 2 ---
    Input: s = "1200210200"
    Output: 12


    *** Constraints ***
    s.length == 10
    s consists only of digits '0' to '9'

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
/* Space Beats:  37.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minRotations(string s)
    {
        const int N = s.size();
        int result = 0;

        char pointer = '0';
        for (int i = 0; i < N; i++)
        {
            int to_left  = 10 - abs(pointer - s[i]);
            int to_right = abs(pointer - s[i]);

            result += min(to_left, to_right);

            pointer = s[i];
        }

        return result;
    }
};
