/*
    ============
    === EASY ===
    ============

    =========================================================
    3442) Maximum Difference Between Even and Odd Frequency I
    =========================================================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters. Your task
    is to find the maximum difference between the frequency of two characters
    in the string such that:

        + One of the characters has an even frequency in the string.

        + The other character has an odd frequency in the string.

    Return the maximum difference, calculated as the frequency of the character
    with an odd frequency minus the frequency of the character with an even
    frequency.

    ======================================
    FUNCTION: int maxDifference(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aaaaabbc"
    Output: 3
    Explanation:
        The character 'a' has an odd frequency of 5, and 'b' has an even
        frequency of 2. The maximum difference is 5 - 2 = 3.

    --- Example 2 ---
    Input: s = "abcabcab"
    Output: 1
    Explanation:
        The character 'a' has an odd frequency of 3, and 'c' has an even
        frequency of 2. The maximum difference is 3 - 2 = 1.


    *** Constraints ***
    3 <= s.length <= 100
    s consists only of lowercase English letters.
    s contains at least one character with an odd frequency and one with an even frequency.

*/

#include <climits>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Counter frequency of every letter. Use "vector" for that since there are
    always going to be exactly 26 letters.

    Go through those 26 letters and consider only those that have frequency
    greater than 0.

    Try to maximize Odd  frequencies.
    Try to minimize Even frequencies.

    Return max_odd - min_even.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   9.52% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxDifference(string s)
    {
        const int N = s.length();

        vector<int> counter(26, 0);
        for (const char& chr : s)
            counter[chr - 'a']++;

        int max_odd  = INT_MIN;
        int min_even = INT_MAX;

        for (int i = 0; i < 26; i++)
        {
            if (counter[i] == 0)
                continue;

            if (counter[i] & 1)
                max_odd  = max(max_odd, counter[i]);
            else
                min_even = min(min_even, counter[i]);
        }

        return max_odd - min_even;
    }
};
