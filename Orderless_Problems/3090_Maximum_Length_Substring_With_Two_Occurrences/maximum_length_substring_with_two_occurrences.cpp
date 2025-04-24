/*
    ============
    === EASY ===
    ============

    ===================================================
    3090) Maximum Length Substring With Two Occurrences
    ===================================================

    ============
    Description:
    ============

    Given a string s, return the maximum length of a  such that it contains at
    most two occurrences of each character.

    ===============================================
    FUNCTION: int maximumLengthSubstring(string s);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "bcbbbcba"
    Output: 4
    Explanation: The following substring has a length of 4 and contains at most
                 two occurrences of each character: "bcbbbcba".

    --- Example 2 ---
    Input: s = "aaaa"
    Output: 2
    Explanation: The following substring has a length of 2 and contains at most
                 two occurrences of each character: "aaaa".


    *** Constraints ***
    2 <= s.length <= 100
    s consists only of lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explantory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  92.69% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maximumLengthSubstring(string s)
    {
        const int N = s.length();
        int result = 0;

        int L = 0;
        int R = 0;

        vector<int> freq(26, 0);
        int max_freq = 0;
        while (R < N)
        {
            freq[s[R] - 'a']++;

            while (L < R && freq[s[R] - 'a'] > 2)
            {
                freq[s[L] - 'a']--;
                L++;
            }

            result = max(result, R - L + 1);

            // Increment
            R++;
        }

        return result;
    }
};
