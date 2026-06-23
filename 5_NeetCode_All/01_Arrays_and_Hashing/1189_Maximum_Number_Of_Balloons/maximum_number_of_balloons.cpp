/*
    ============
    === EASY ===
    ============

    ================================
    1189) Maximum Number of Balloons
    ================================

    ============
    Description:
    ============

    Given a string text, you want to use the characters of text to form as many
    instances of the word "balloon" as possible.

    You can use each character in text at most once. Return the maximum number
    of instances that can be formed.

    ===============================================
    FUNCTION: int maxNumberOfBalloons(string text);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: text = "nlaebolko"
    Output: 1


    --- Example 2 ---
    Input: text = "loonbalxballpoon"
    Output: 2


    --- Example 3 ---
    Input: text = "leetcode"
    Output: 0


    *** Constraints ***
    1 <= text.length <= 10^4
    text consists of lower case English letters only.

*/

#include <climits>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  95.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // O(26) --> O(1)
class Solution {
public:
    int maxNumberOfBalloons(string text)
    {
        int result = INT_MAX;

        // b - 1
        // a - 1
        // l - 2
        // o - 2
        // n - 1

        int freq[26] = {0}; // Allocated on the STACK
        for (const char& chr : text)
            freq[chr - 'a']++;

        result = min(result, freq['b' - 'a'] / 1);
        result = min(result, freq['a' - 'a'] / 1);
        result = min(result, freq['l' - 'a'] / 2); // Two 'l' per word
        result = min(result, freq['o' - 'a'] / 2); // Two 'o' per word
        result = min(result, freq['n' - 'a'] / 1);

        return result;
    }
};
