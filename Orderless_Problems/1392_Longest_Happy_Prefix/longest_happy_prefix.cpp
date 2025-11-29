/*
    ============
    === HARD ===
    ============

    ===========================
    1392) Longest Happy Prefix
    ===========================

    ============
    Description:
    ============

    A string is called a happy prefix if is a non-empty prefix which is also a
    suffix (excluding itself).

    Given a string s, return the longest happy prefix of s. Return an empty
    string "" if no such prefix exists.

    =========================================
    FUNCTION: string longestPrefix(string s);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "level"
    Output: "l"
    Explanation: s contains 4 prefix excluding itself ("l", "le", "lev",
                 "leve"), and suffix ("l", "el", "vel", "evel"). The largest
                 prefix which is also suffix is given by "l".

    --- Example 2 ---
    Input: s = "ababab"
    Output: "abab"
    Explanation: "abab" is the largest prefix which is also suffix. They can
                 overlap in the original string.


    *** Constraints ***
    1 <= s.length <= 10^5
    s contains only lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 85.66% */
/* Space Beats: 92.02% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string longestPrefix(string& s)
    {
        const int N = s.size();
        vector<int> dp(N);

        int j = 0;
        for (int i = 1; i < N; i++)
        {
            if (s[i] == s[j])
            {
                j++;
                dp[i] = j;
            }
            else if (j > 0)
            {
                j = dp[j - 1];
                i--;
            }
        }

        return s.substr(0, j);
    }
};
