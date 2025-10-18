/*
    ============
    === EASY ===
    ============

    ==================================
    1370) Increasing Decreasing String
    ==================================

    ============
    Description:
    ============

    You are given a string s. Reorder the string using the following algorithm:

        + Remove the smallest character from s and append it to the result.

        + Remove the smallest character from s that is greater than the last
          appended character, and append it to the result.

        + Repeat step 2 until no more characters can be removed.

        + Remove the largest character from s and append it to the result.

        + Remove the largest character from s that is smaller than the last
          appended character, and append it to the result.

        + Repeat step 5 until no more characters can be removed.

        + Repeat steps 1 through 6 until all characters from s have been
          removed.

    If the smallest or largest character appears more than once, you may choose
    any occurrence to append to the result.

    Return the resulting string after reordering s using this algorithm.

    ======================================
    FUNCTION: string sortString(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aaaabbbbcccc"
    Output: "abccbaabccba"
    Explanation: After steps 1, 2 and 3 of the first iteration, result = "abc"
    After steps 4, 5 and 6 of the first iteration, result = "abccba"
    First iteration is done. Now s = "aabbcc" and we go back to step 1
    After steps 1, 2 and 3 of the second iteration, result = "abccbaabc"
    After steps 4, 5 and 6 of the second iteration, result = "abccbaabccba"

    --- Example 2 ---
    Input: s = "rat"
    Output: "art"
    Explanation: The word "rat" becomes "art" after re-ordering it with the
                 mentioned algorithm.


    *** Constraints ***
    1 <= s.length <= 500
    s consists of only lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 20.90% */
/* Space Beats:  8.47% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string sortString(string s)
    {
        string result = "";

        int freq[26] = {};

        for (const auto& chr: s)
            freq[chr - 'a']++;

        while (s.size() != result.size())
        {
            for (auto i = 0; i < 26; i++)
                result += string(--freq[i] >= 0 ? 1 : 0, 'a' + i); 

            for (int i = 25; i >= 0; i--)
                result += string(--freq[i] >= 0 ? 1 : 0, 'a' + i);          
        }

        return result;
    }
};
