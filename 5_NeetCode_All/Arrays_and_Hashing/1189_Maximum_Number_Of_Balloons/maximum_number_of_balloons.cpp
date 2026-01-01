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
/* Space Beats: 93.68% */

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




/*
    ------------
    --- IDEA ---
    ------------

    Edge cases are taken care of properly even without explicitly covering
    them.

*/

/* Time  Beats: 72.19% */
/* Space Beats: 48.64% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxNumberOfBalloons(std::string text)
    {
        std::vector<int> balloon(26, 0);
        balloon['b' - 'a'] = 1;
        balloon['a' - 'a'] = 1;
        balloon['l' - 'a'] = 2;
        balloon['o' - 'a'] = 2;
        balloon['n' - 'a'] = 1;

        std::vector<int> letters(26, 0);
        for (char& chr : text)
            letters[chr - 'a']++;

        letters['b' - 'a'] /= balloon['b' - 'a'];
        letters['a' - 'a'] /= balloon['a' - 'a'];
        letters['l' - 'a'] /= balloon['l' - 'a'];
        letters['o' - 'a'] /= balloon['o' - 'a'];
        letters['n' - 'a'] /= balloon['n' - 'a'];

        int result = std::min({letters['b' - 'a'], letters['a' - 'a'],
                               letters['l' - 'a'], letters['o' - 'a'],
                               letters['n' - 'a']});

        return result;
    }
};
