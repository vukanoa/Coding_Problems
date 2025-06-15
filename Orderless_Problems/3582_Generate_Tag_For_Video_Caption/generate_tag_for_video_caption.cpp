/*
    ============
    === EASY ===
    ============

    ====================================
    3582) Generate Tag for Video Caption
    ====================================

    ============
    Description:
    ============

    You are given a string caption representing the caption for a video.

    The following actions must be performed in order to generate a valid tag
    for the video:

        + Combine all words in the string into a single camelCase string
          prefixed with '#'. A camelCase string is one where the first letter
          of all words except the first one is capitalized. All characters
          after the first character in each word must be lowercase.

        + Remove all characters that are not an English letter, except the
          first '#'.

        + Truncate the result to a maximum of 100 characters.

    Return the tag after performing the actions on caption.

    =============================================
    FUNCTION: string generateTag(string caption);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: caption = "Leetcode daily streak achieved"
    Output: "#leetcodeDailyStreakAchieved"
    Explanation:
    The first letter for all words except "leetcode" should be capitalized.

    --- Example 2 ---
    Input: caption = "can I Go There"
    Output: "#canIGoThere"
    Explanation:
    The first letter for all words except "can" should be capitalized.

    --- Example 3 ---
    Input: caption = "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"
    Output: "#hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"
    Explanation:
    Since the first word has length 101, we need to truncate the last two letters from the word.


    *** Constraints ***
    1 <= caption.length <= 150
    caption consists only of English letters and ' '.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one is very easy, but you need to be VERY careful. It has a lot of
    edge cases, so be careful when writing it on your own.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  18.18% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // Result string is not considered"extra space"
class Solution {
public:
    string generateTag(string caption)
    {
        /* Remove whitespace character at the beginning */
        int x = 0;
        while (x < caption.size() && caption[x] == ' ')
        {
            x++;
            continue;
        }

        // If caption was all whitespace, then return "#"
        if (x == caption.size())
            return "#";


        //  ------------------------------------------------------------------
        const int N = caption.size();
        string result = "#";

        if (caption[x] >= 65 && caption[x] <= 90) // If it's Big letter
            result += char(caption[x] + 32);      // Make it Small
        else
            result += caption[x];                 // Append Small as is

        int used = 2; // Used '#' and caption[0]
        for (int i = x+1; i < N; i++)
        {
            if (used == 100)
                break;

            if (caption[i] == ' ')
                continue;

            if (caption[i-1] == ' ')
            {
                if (caption[i] >= 65 && caption[i] <= 90) // If it's Big letter
                    result += caption[i];                 // Append Big as is
                else
                    result += char(caption[i] - 32);      // Make it Big
            }
            else
            {
                if (caption[i] >= 65 && caption[i] <= 90) // If it's Big
                    result += char(caption[i] + 32);      // Make it Small
                else
                    result += caption[i];                 // Append Small as is
            }

            used++;
        }

        return result;
    }
};
