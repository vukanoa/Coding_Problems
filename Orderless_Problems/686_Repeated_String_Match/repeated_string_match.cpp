/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    686) Repeated String Match
    ===========================

    ============
    Description:
    ============

    Given two strings a and b, return the minimum number of times you should
    repeat string a so that string b is a substring of it. If it is impossible
    for b to be a substring of a after repeating it, return -1.

    =====
    Note: string "abc" repeated 0 times is "", repeated 1 time is "abc" and
          repeated 2 times is "abcabc". 
    =====

    ======================================================
    FUNCTION: int repeatedStringMatch(string a, string b);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: a = "abcd", b = "cdabcdab"
    Output: 3
    Explanation: We return 3 because by repeating a three times "abcdabcdabcd",
                 b is a substring of it.

    --- Example 2 ---
    Input: a = "a", b = "aa"
    Output: 2


    *** Constraints ***
    1 <= a.length, b.length <= 10^4
    a and b consist of lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 24.86% */
/* Space Beats: 84.20% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int repeatedStringMatch(string a, string b)
    {
        int repetitions = 1;

        string repeated_a = a;
        while (repeated_a.size() < b.size())
        {
            repeated_a += a;
            repetitions++;
        }

        if (repeated_a.find(b) != string::npos)
            return repetitions;

        repeated_a += a;

        if (repeated_a.find(b) != string::npos)
            return repetitions + 1;

        return -1;
    }
};
