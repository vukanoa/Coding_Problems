#include <iostream>
#include <vector>

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

/* Time  Beats:   100% */
/* Space Beats: 33.15% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxNumberOfBalloons(std::string text)
    {
        const int BALLOON_SIZE = 7;

        if (text.length() < BALLOON_SIZE)
            return 0;

        std::vector<int> balloon(26, INT_MAX);

        std::vector<int> letters(26, 0);

        // O(n)
        for(auto& c : text)
            letters[c - 'a']++;

        balloon['b' - 'a'] = letters['b' - 'a'];
        balloon['a' - 'a'] = letters['a' - 'a'];
        balloon['l' - 'a'] = letters['l' - 'a'] / 2;
        balloon['o' - 'a'] = letters['o' - 'a'] / 2;
        balloon['n' - 'a'] = letters['n' - 'a'];

        return *std::min_element(balloon.begin(), balloon.end());
    }
};
