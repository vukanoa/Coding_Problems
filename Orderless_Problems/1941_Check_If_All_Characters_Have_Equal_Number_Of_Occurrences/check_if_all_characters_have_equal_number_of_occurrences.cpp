/*
    ============
    === EASY ===
    ============

    ==============================================================
    1941) Check if All Characters have Equal number of Occurrences
    ==============================================================

    ============
    Description:
    ============

    Given a string s, return true if s is a good string, or false otherwise.

    A string s is good if all the characters that appear in s have the same
    number of occurrences (i.e., the same frequency).

    ==============================================
    FUNCTION:  bool areOccurrencesEqual(string s);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abacbc"
    Output: true
    Explanation: The characters that appear in s are 'a', 'b', and 'c'. All
    characters occur 2 times in s.

    --- Example 2 ---
    Input: s = "aaabb"
    Output: false
    Explanation: The characters that appear in s are 'a' and 'b'.
    'a' occurs 3 times while 'b' occurs 2 times, which is not the same number
    of times.

    *** Constraints ***
    1 <= s.length <= 1000
    s consists of lowercase English letters.

*/

#include <string>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory

*/

/* Time  Beats: 100.00% */
/* Space Beats:  46.13% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // O(26)
class Solution {
public:
    bool areOccurrencesEqual(string s)
    {
        unordered_map<char, int> freq;
        for (const char& chr : s)
        {
            freq[chr]++;
        }

        int prev_freq = freq.begin()->second;
        for (const auto& entry : freq)
        {
            if (entry.second != prev_freq)
                return false;
        }

        return true;
    }
};
