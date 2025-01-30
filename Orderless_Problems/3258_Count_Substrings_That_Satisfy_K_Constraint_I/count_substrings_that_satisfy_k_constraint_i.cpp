/*
    ============
    === EASY ===
    ============

    ==================================================
    3258) Count Substrings that Satisfy K-Constraint I
    ==================================================

    ============
    Description:
    ============

    You are given a binary string s and an integer k.

    A binary string satisfies the k-constraint if either of the following
    conditions holds:

        The number of 0's in the string is at most k.
        The number of 1's in the string is at most k.

    Return an integer denoting the number of substrings of s that satisfy the
    k-constraint.

    ==========================================================
    FUNCTION: int countKConstraintSubstrings(string s, int k);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "10101", k = 1
    Output: 12
    Explanation:
    Every substring of s except the substrings "1010", "10101", and "0101"
    satisfies the k-constraint.

    --- Example 2 ---
    Input: s = "1010101", k = 2
    Output: 25
    Explanation:
    Every substring of s except the substrings with a length greater than 5
    satisfies the k-constraint.

    --- Example 3 ---
    Input: s = "11111", k = 1
    Output: 15
    Explanation:
    All substrings of s satisfy the k-constraint.


    *** Constraints ***
    1 <= s.length <= 50
    1 <= k <= s.length
    s[i] is either '0' or '1'.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The most simple Brute-Force.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  91.79% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int countKConstraintSubstrings(string s, int k)
    {
        const int N = s.length();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            int ones   = 0;
            int zeroes = 0;

            if (s[i] == '1')
                ones++;
            else
                zeroes++;

            result++;

            for (int j = i+1; j < N; j++)
            {
                if (s[j] == '1')
                    ones++;
                else
                    zeroes++;

                if (ones > k && zeroes > k)
                    break;

                result++;
            }
        }

        return result;
    }
};
