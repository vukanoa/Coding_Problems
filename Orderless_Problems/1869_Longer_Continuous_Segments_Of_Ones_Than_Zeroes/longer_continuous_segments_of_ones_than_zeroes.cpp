/*
    ============
    === EASY ===
    ============

    ===================================================
    1869) Longer Contiguous Segments of Ones than Zeros
    ===================================================

    ============
    Description:
    ============

    Given a binary string s, return true if the longest contiguous segment of
    1's is strictly longer than the longest contiguous segment of 0's in s, or
    return false otherwise.

        + For example, in s = "110100010" the longest continuous segment of 1s
          has length 2, and the longest continuous segment of 0s has length 3.

    =====
    Note: that if there are no 0's, then the longest continuous segment of 0's
          is considered to have a length 0. The same applies if there is no 1's
    =====

    =======================================
    FUNCTION: bool checkZeroOnes(string s);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "1101"
    Output: true
    Explanation:
    The longest contiguous segment of 1s has length 2: "1101"
    The longest contiguous segment of 0s has length 1: "1101"
    The segment of 1s is longer, so return true.

    --- Example 2 ---
    Input: s = "111000"
    Output: false
    Explanation:
    The longest contiguous segment of 1s has length 3: "111000"
    The longest contiguous segment of 0s has length 3: "111000"
    The segment of 1s is not longer, so return false.

    --- Example 3 ---
    Input: s = "110100010"
    Output: false
    Explanation:
    The longest contiguous segment of 1s has length 2: "110100010"
    The longest contiguous segment of 0s has length 3: "110100010"
    The segment of 1s is not longer, so return false.

    *** Constraints ***
    1 <= s.length <= 100
    s[i] is either '0' or '1'.

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
/* Space Beats:  71.08% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool checkZeroOnes(string s)
    {
        const int N = s.length();
        if (N == 1)
            return s[0] == '1';

        int ones   = 0;
        int zeroes = 0;

        int L = 0;
        int R = 1;
        while (R < N)
        {
            if (s[R-1] != s[R])
            {
                if (s[R-1] == '0')
                    zeroes = max(zeroes, R - L);
                else
                    ones = max(ones, R - L);

                L = R;
            }

            // Increment
            R++;
        }

        // For the ending "block"
        if (s[R-1] == '0')
            zeroes = max(zeroes, R - L);
        else
            ones = max(ones, R - L);


        return ones > zeroes;
    }
};
