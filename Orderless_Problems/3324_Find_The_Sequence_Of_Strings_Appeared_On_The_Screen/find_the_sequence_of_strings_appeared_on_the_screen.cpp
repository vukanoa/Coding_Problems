/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    3324) Find the Sequence of Strings Appeared on the Screen
    =========================================================

    ============
    Description:
    ============

    You are given a string target.

    Alice is going to type target on her computer using a special keyboard that
    has only two keys:

        + Key 1 appends the character "a" to the string on the screen.
        + Key 2 changes the last character of the string on the screen to its
          next character in the English alphabet. For example, "c" changes to
          "d" and "z" changes to "a".

    Note that initially there is an empty string "" on the screen, so she can
    only press key 1.

    Return a list of all strings that appear on the screen as Alice types
    target, in the order they appear, using the minimum key presses.

    =======================================================
    FUNCTION: vector<string> stringSequence(string target);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: target = "abc"
    Output: ["a","aa","ab","aba","abb","abc"]
    Explanation:
    The sequence of key presses done by Alice are:
        Press key 1, and the string on the screen becomes "a".
        Press key 1, and the string on the screen becomes "aa".
        Press key 2, and the string on the screen becomes "ab".
        Press key 1, and the string on the screen becomes "aba".
        Press key 2, and the string on the screen becomes "abb".
        Press key 2, and the string on the screen becomes "abc".


    --- Example 2 ---
    Input: target = "he"
    Output: ["a","b","c","d","e","f","g","h","ha","hb","hc","hd","he"]


    *** Constraints ***
    1 <= target.length <= 400
    target consists only of lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Literally just do what you're told.

*/

/* Time  Beats: 81.43% */
/* Space Beats: 46.15% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */ // Really O(1) because "result" isn't Additional
class Solution {
public:
    vector<string> stringSequence(string target)
    {
        const int N = target.length();
        vector<string> result = {};
        // result.push_back(string("a"));

        int letter_idx = 0; // Starting from 0
        string curr_str = string("a");
        while (result.empty() || result.back() != target)
        {
            result.push_back(curr_str);

            if (curr_str.back() == target[letter_idx])
            {
                curr_str += 'a';
                letter_idx++;
            }
            else
            {
                char chr = static_cast<char>(((curr_str.back() - 'a' + 1) % 26) + 'a');
                curr_str.pop_back();
                curr_str += chr;
            }

        }

        return result;
    }
};
