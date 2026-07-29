/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================================
    2840) Check if Strings Can be Made Equal With Operations II
    ===========================================================

    ============
    Description:
    ============

    You are given two strings s1 and s2, both of length n, consisting of
    lowercase English letters.

    You can apply the following operation on any of the two strings any number
    of times:

        + Choose any two indices i and j such that i < j and the difference
          j - i is even, then swap the two characters at those indices in the
          string.

    Return true if you can make the strings s1 and s2 equal, and false
    otherwise.

    ==================================================
    FUNCTION: bool checkStrings(string s1, string s2);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s1 = "abcdba", s2 = "cabdab"
    Output: true
    Explanation: We can apply the following operations on s1:
    - Choose the indices i = 0, j = 2. The resulting string is s1 = "cbadba".
    - Choose the indices i = 2, j = 4. The resulting string is s1 = "cbbdaa".
    - Choose the indices i = 1, j = 5. The resulting string is s1 = "cabdab" = s2.

    --- Example 2 ---
    Input: s1 = "abe", s2 = "bea"
    Output: false
    Explanation: It is not possible to make the two strings equal.

    *** Constraints ***
    n == s1.length == s2.length
    1 <= n <= 10^5
    s1 and s2 consist only of lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 91.00% */
/* Space Beats: 51.34% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool checkStrings(string s1, string s2)
    {
        const int N = s1.size();

        int freq_even_1[26] = {0};
        int freq_even_2[26] = {0};

        int freq_odd_1[26]  = {0};
        int freq_odd_2[26]  = {0};

        for (int i = 0; i < N; i++)
        {
            if (i % 2 == 0)
            {
                freq_even_1[s1[i] - 'a']++;
                freq_even_2[s2[i] - 'a']++;
            }
            else
            {
                freq_odd_1[s1[i] - 'a']++;
                freq_odd_2[s2[i] - 'a']++;
            }
        }

        return equal(freq_even_1, freq_even_1 + 26, freq_even_2) &&
               equal(freq_odd_1,  freq_odd_1  + 26, freq_odd_2);
    }
};
