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
#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  99.96% */

/* Time  Complexity: O(max(N, M)) */
/* Space Complexity: O(1)         */
class Solution {
public:
    int compareVersion(string& version1, string& version2)
    {
        const int N = version1.size();
        const int M = version2.size();

        int revision_1 = 0;
        int revision_2 = 0;

        int i = 0;
        int j = 0;
        while (i < N || j < M)
        {
            while (i < N && version1[i] != '.')
            {
                revision_1 = 10*revision_1 + (version1[i] - '0');
                i++;
            }

            while (j < M && version2[j] != '.')
            {
                revision_2 = 10*revision_2 + (version2[j] - '0');
                j++;
            }

            if (revision_1 < revision_2)
                return -1;

            if (revision_1 > revision_2)
                return 1;

            revision_1 = 0;
            revision_2 = 0;

            // Increment
            i++;
            j++;
        }

        return 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  48.40% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(N + M) */
class Solution_String_Functions {
public:
    int compareVersion(string& version1, string& version2)
    {
        const int N = version1.length();
        const int M = version2.length();

        int i = 0;
        int j = 0;
        while (i < N || j < M)
        {
            auto dot_idx_1 = version1.find('.', i);
            auto dot_idx_2 = version2.find('.', j);

            int revision_1;
            int revision_2;


            // Revision 1
            string str1 = version1.substr(i, dot_idx_1 - i);   // Get substring of revision
            str1.erase(0, str1.find_first_not_of('0'));        // Remove leading 0s

            revision_1 = str1.empty() ? 0 : stoi(str1);        // Assign
            i = dot_idx_1 == string::npos ? N : dot_idx_1 + 1; // Update i


            // Revision 2
            string str2 = version2.substr(j, dot_idx_2 - j);   // Get substring of revision
            str2.erase(0, str2.find_first_not_of('0'));        // Remove leading 0s

            revision_2 = str2.empty() ? 0 : stoi(str2);        // Assign
            j = dot_idx_2 == string::npos ? M : dot_idx_2 + 1; // Update j


            // Compare
            if (revision_1 < revision_2)
                return -1;

            if (revision_1 > revision_2)
                return 1;
        }

        return 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_String_Stream {
public:
    int compareVersion(string version1, string version2)
    {
        stringstream ss1(version1);
        stringstream ss2(version2);

        string token1;
        string token2;

        while (ss1.good() || ss2.good()) // .good() means not EOF yet
        {
            if ( ! getline(ss1, token1, '.')) token1 = "0";
            if ( ! getline(ss2, token2, '.')) token2 = "0";

            int num1 = stoi(token1);
            int num2 = stoi(token2);

            if (num1 < num2) return -1;
            if (num1 > num2) return 1;
        }

        return 0;
    }
};
