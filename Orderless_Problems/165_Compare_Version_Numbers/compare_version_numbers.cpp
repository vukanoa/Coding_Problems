/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    165) Compare Version Numbers
    ============================

    ============
    Description:
    ============


    Given two version strings, version1 and version2, compare them. A version
    string consists of revisions separated by dots '.'. The value of the
    revision is its integer conversion ignoring leading zeros.

    To compare version strings, compare their revision values in left-to-right
    order. If one of the version strings has fewer revisions, treat the missing
    revision values as 0.

    Return the following:

        + If version1 < version2, return -1.
        + If version1 > version2, return 1.
        + Otherwise, return 0.

    ===============================================================
    FUNCTION: int compareVersion(string version1, string version2);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: version1 = "1.2", version2 = "1.10"
    Output: -1
    Explanation: version1's second revision is "2" and version2's second
                 revision is "10": 2 < 10, so version1 < version2.

    --- Example 2 ---
    Input: version1 = "1.01", version2 = "1.001"
    Output: 0
    Explanation: Ignoring leading zeroes, both "01" and "001" represent the
                 same integer "1"

    --- Example 3 ---
    Input: version1 = "1.0", version2 = "1.0.0.0"
    Output: 0
    Explanation: version1 has less revisions, which means every missing
                 revision are treated as "0".


    *** Constraints ***
    1 <= version1.length, version2.length <= 500
    version1 and version2 only contain digits and '.'.
    version1 and version2 are valid version numbers.
    All the given revisions in version1 and version2 can be stored in a 32-bit
    integer.

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
/* Space Beats:  99.96% */

/* Time  Complexity: O(max(N1, N2)) */
/* Space Complexity: O(1)           */
class Solution {
public:
    static int compareVersion(string& v1, string& v2)
    {
        const int N1 = v1.size();
        const int N2 = v2.size();

        int x1 = 0;
        int x2 = 0;

        for (int i = 0, j = 0; i < N1 || j < N2; i++, j++)
        {
            while (i < N1 && v1[i] != '.')
                x1 = 10*x1 + (v1[i++] - '0');

            while (j < N2 && v2[j] != '.')
                x2 = 10*x2 + (v2[j++] - '0');

            if (x1 < x2)
                return -1;

            if (x1 > x2)
                return 1;

            x1 = 0;
            x2 = 0;
        }

        return 0;
    }
};
