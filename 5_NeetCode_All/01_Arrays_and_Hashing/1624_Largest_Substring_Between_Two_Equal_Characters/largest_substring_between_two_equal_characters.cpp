#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ====================================================
    1624) Largest Substring Between Two Equal Characters
    ====================================================

    ============
    Description:
    ============

    Given a string s, return the length of the longest substring between two
    equal characters, excluding the two characters. If there is no such
    substring return -1.

    A substring is a contiguous sequence of characters within a string.

    ========================================================
    FUNCTION: int maxLengthBetweenEqualCharacters(string s);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aa"
    Output: 0
    Explanation: The optimal substring here is an empty substring between the
                 two 'a's.

    --- Example 2 ---
    Input: s = "abca"
    Output: 2
    Explanation: The optimal substring here is "bc".

    --- Example 3 ---
    Input: s = "cbzxy"
    Output: -1
    Explanation: There are no characters that appear twice in s.


    *** Constraints ***
    1 <= s.length <= 300
    s contains only lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Remember the first and last occurence of each letter.

    If some letter didn't occur even once(i.e. its letters[i].first == INT_MAX)
    or if it occured only once(i.e. its letters[i].second == INT_MIN), then
    skip those.

    Take the biggest difference out of those that occur more than once, i.e.
    their:
        1) letters[i].first  < INT_MAX
            &&
        2) letters[i].second > INT_MIN

    Return the biggest difference.
    (Note that you must subtract '1' as well)

    Example:
        a b c a
        0 1 2 3

        3 - 0 = 3, but that's not the right answer. The right answer is 2.

        Therefore:
            last_occurrence_idx - first_occurence_idx - 1

*/

/* Time  Beats: 100.00% */
/* Space Beats:  46.29% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s)
    {
        vector<pair<int, int>> letters(26, {INT_MAX, INT_MIN});

        for (int i = 0; i < s.length(); i++)
        {
            letters[s[i] - 'a'].first  = min(letters[s[i] - 'a'].first,  i);
            letters[s[i] - 'a'].second = max(letters[s[i] - 'a'].second, i);
        }

        int result = -1;
        for (int i = 0; i < 26; i++)
        {
            if (letters[i].first < INT_MAX && letters[i].second > INT_MIN)
                result = max(result, letters[i].second - letters[i].first - 1);
        }


        return result;
    }
};
