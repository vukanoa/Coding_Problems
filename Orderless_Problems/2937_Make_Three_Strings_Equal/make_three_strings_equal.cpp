/*
    ============
    === EASY ===
    ============

    ==============================
    2937) Make Three Strings Equal
    ==============================

    ============
    Description:
    ============

    You are given three strings: s1, s2, and s3. In one operation you can
    choose one of these strings and delete its rightmost character. Note that
    you cannot completely empty a string.

    Return the minimum number of operations required to make the strings equal.
    If it is impossible to make them equal, return -1.

    =====================================================================
    FUNCTION: int findMinimumOperations(string s1, string s2, string s3);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s1 = "abc", s2 = "abb", s3 = "ab"
    Output: 2
    Explanation: Deleting the rightmost character from both s1 and s2 will
                 result in three equal strings.

    --- Example 2 ---
    Input: s1 = "dac", s2 = "bac", s3 = "cac"
    Output: -1
    Explanation: Since the first letters of s1 and s2 differ, they cannot be
                 made equal.


    *** Constraints ***
    1 <= s1.length, s2.length, s3.length <= 100
    s1, s2 and s3 consist only of lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Essentially "Longest Prefix")

*/

/* Time  Beats: 27.27% */
/* Space Beats: 35.41% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findMinimumOperations(string s1, string s2, string s3)
    {
        const int SIZE_1 = s1.length();
        const int SIZE_2 = s2.length();
        const int SIZE_3 = s3.length();

        if ( ! (s1[0] == s2[0] && s2[0] == s3[0]) )
            return -1;

        int i = 0;
        int j = 0;
        int k = 0;

        while (i < SIZE_1 && j < SIZE_2 && k < SIZE_3)
        {
            if ( ! (s1[i] == s2[j] && s2[j] == s3[k]))
                break;

            i++;
            j++;
            k++;
        }

        return SIZE_1 - i +
               SIZE_2 - j +
               SIZE_3 - k;
    }
};
