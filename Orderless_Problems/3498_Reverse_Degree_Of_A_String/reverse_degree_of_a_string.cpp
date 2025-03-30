/*
    ============
    === EASY ===
    ============

    ================================
    3498) Reverse Degree of a String
    ================================

    ============
    Description:
    ============

    Given a string s, calculate its reverse degree.

    The reverse degree is calculated as follows:

        1. For each character, multiply its position in the reversed alphabet
           ('a' = 26, 'b' = 25, ..., 'z' = 1) with its position in the string
           (1-indexed).

        2. Sum these products for all characters in the string.

    Return the reverse degree of s.

    ======================================
    FUNCTION: int reverseDegree(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abc"
    Output: 148

    --- Example 2 ---
    Input: s = "zaza"
    Output: 160


    *** Constraints ***
    1 <= s.length <= 1000
    s contains only lowercase English letters.

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
/* Space Beats:  84.21% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int reverseDegree(string s)
    {
        const int N = s.length();
        int sum = 0;

        for (int i = 0; i < N; i++)
            sum += (i+1) * (26 - (s[i] - 'a'));

        return sum;
    }
};
