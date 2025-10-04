/*
    ============
    === EASY ===
    ============

    ====================================
    2278) Percentage of Letter in String
    ====================================

    ============
    Description:
    ============

    Given a string s and a character letter, return the percentage of
    characters in s that equal letter rounded down to the nearest whole percent

    ======================================================
    FUNCTION: int percentageLetter(string s, char letter);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "foobar", letter = "o"
    Output: 33
    Explanation:
    The percentage of characters in s that equal the letter 'o' is
    2 / 6 * 100% = 33% when rounded down, so we return 33.

    --- Example 2 ---
    Input: s = "jjjj", letter = "k"
    Output: 0
    Explanation:
    The percentage of characters in s that equal the letter 'k' is 0%, so we
    return 0.


    *** Constraints ***
    1 <= s.length <= 100
    s consists of lowercase English letters.
    letter is a lowercase English letter.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  33.53% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int percentageLetter(string s, char letter)
    {
        const int N = s.length();
        int result = 0;

        
        int count = 0;
        for (int i = 0; i < N; i++)
        {
            if (s[i] == letter)
                count++;
        }

        double double_result = 1.0 * count / N;

        return static_cast<int>(double_result * 100);
    }
};
