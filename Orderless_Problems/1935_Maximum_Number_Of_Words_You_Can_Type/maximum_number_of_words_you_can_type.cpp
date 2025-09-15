/*
    ============
    === EASY ===
    ============

    ==========================================
    1935) Maximum Number of Words You Can Type
    ==========================================

    ============
    Description:
    ============

    There is a malfunctioning keyboard where some letter keys do not work. All
    other keys on the keyboard work properly.

    Given a string text of words separated by a single space (no leading or
    trailing spaces) and a string brokenLetters of all distinct letter keys
    that are broken, return the number of words in text you can fully type
    using this keyboard.

    =================================================================
    FUNCTION: int canBeTypedWords(string text, string brokenLetters);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: text = "hello world", brokenLetters = "ad"
    Output: 1
    Explanation: We cannot type "world" because the 'd' key is broken.

    --- Example 2 ---
    Input: text = "leet code", brokenLetters = "lt"
    Output: 1
    Explanation: We cannot type "leet" because the 'l' and 't' keys are broken.

    --- Example 3 ---
    Input: text = "leet code", brokenLetters = "e"
    Output: 0
    Explanation: We cannot type either word because the 'e' key is broken.


    *** Constraints ***
    1 <= text.length <= 10^4
    0 <= brokenLetters.length <= 26
    text consists of words separated by a single space without any leading or trailing spaces.
    Each word only consists of lowercase English letters.
    brokenLetters consists of distinct lowercase English letters.

*/

#include <string>
#include <unordered_set>
using namespace std;

/* Time  Beats: 100.00% */
/* Space Beats:  47.18% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // O(26) --> O(1)
class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters)
    {
        const int N = text.length();
        int result = 0;

        unordered_set<int> uset_broken(brokenLetters.begin(), brokenLetters.end());

        bool can_type = true;
        for (int i = 0; i < N; i++)
        {
            if (text[i] == ' ')
            {
                if (can_type)
                    result++;

                can_type = true;
            }
            else if (uset_broken.count(text[i]))
            {
                can_type = false;
                while (i < N && text[i] != ' ')
                    i++;

                i--;
            }
        }

        if (can_type)
            result++;

        return result;
    }
};
