/*
    ============
    === EASY ===
    ============

    =======================================================
    1876) Substrings of Size Three with Distinct Characters
    =======================================================

    ============
    Description:
    ============

    A string is good if there are no repeated characters.

    Given a string s, return the number of good substrings of length three in
    s.

    Note that if there are multiple occurrences of the same substring, every
    occurrence should be counted.

    A substring is a contiguous sequence of characters in a string.

    ============================================
    FUNCTION: int countGoodSubstrings(string s);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "xyzzaz"
    Output: 1
    Explanation: There are 4 substrings of size 3: "xyz", "yzz", "zza", and "zaz".
    The only good substring of length 3 is "xyz".

    --- Example 2 ---
    Input: s = "aababcabc"
    Output: 4
    Explanation: There are 7 substrings of size 3: "aab", "aba", "bab", "abc", "bca", "cab", and "abc".
    The good substrings are "abc", "bca", "cab", and "abc".


    *** Constraints ***
    1 <= s.length <= 100
    s consists of lowercase English letters.

*/

#include <string>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Prime of example of the most basic Sliding-Window technique.

*/

/* Time  Beats: 32.78% */
/* Space Beats: 41.59% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // At most 3 at the time
class Solution {
public:
    int countGoodSubstrings(string s)
    {
        const int N = s.length();
        int result = 0;

        int L = 0;
        int R = 2;

        unordered_map<char,int> freq;
        freq[s[0]]++;
        freq[s[1]]++;

        while (R < N)
        {
            freq[s[R]]++;

            if (freq.size() == 3)
                result++;

            freq[s[L]]--;
            if (freq[s[L]] == 0)
                freq.erase(s[L]);

            // Slide-Window
            L++;
            R++;
        }

        return result;
    }
};
