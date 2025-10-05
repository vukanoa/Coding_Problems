/*
    ============
    === EASY ===
    ============

    ====================================
    1592) Rearrange Spaces Between Words
    ====================================

    ============
    Description:
    ============

    You are given a string text of words that are placed among some number of
    spaces. Each word consists of one or more lowercase English letters and are
    separated by at least one space. It's guaranteed that text contains at
    least one word.

    Rearrange the spaces so that there is an equal number of spaces between
    every pair of adjacent words and that number is maximized. If you cannot
    redistribute all the spaces equally, place the extra spaces at the end,
    meaning the returned string should be the same length as text.

    Return the string after rearranging the spaces.

    ============================================
    FUNCTION: string reorderSpaces(string text);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: text = "  this   is  a sentence "
    Output: "this   is   a   sentence"
    Explanation: There are a total of 9 spaces and 4 words. We can evenly
                 divide the 9 spaces between the words: 9 / (4-1) = 3 spaces.

    --- Example 2 ---
    Input: text = " practice   makes   perfect"
    Output: "practice   makes   perfect "
    Explanation: There are a total of 7 spaces and 3 words. 7 / (3-1) = 3
                 spaces plus 1 extra space. We place this extra space at the
                 end of the string.


    *** Constraints ***
    1 <= text.length <= 100
    text consists of lowercase English letters and ' '.
    text contains at least one word.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  32.65% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string reorderSpaces(string text)
    {
        const int N = text.length();
        int spaces = 0;
        vector<string> words;

        string word = "";
        for (int i = 0; i < N; i++)
        {
            if (text[i] == ' ')
            {
                spaces++;

                if ( ! word.empty())
                {
                    words.push_back(word);
                    word.clear();
                }
            }
            else
            {
                word += text[i];
            }
        }

        if ( ! word.empty())
            words.push_back(word);

        if (words.size() == 1)
            return words[0] + string(spaces , ' ');

        int number_of_gaps = words.size() - 1;
        int spaces_per_gap = spaces / number_of_gaps;
        int extra_spaces   = spaces % number_of_gaps;

        string result = words[0];
        for (int i = 1; i < words.size(); i++)
            result += string(spaces_per_gap , ' ') + words[i];

        if (extra_spaces)
            result += string(extra_spaces , ' ');

        return result;
    }
};
