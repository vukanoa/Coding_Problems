#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    =================================================
    1160) Find Words That Can Be Formed by Characters
    =================================================

    ============
    Description:
    ============

    You are given an array of strings words and a string chars.

    A string is good if it can be formed by characters from chars (each
    character can only be used once).

    Return the sum of lengths of all good strings in words.

    ===================================================================
    FUNCTION: int countCharacters(vector<string>& words, string chars);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["cat","bt","hat","tree"], chars = "atach"
    Output: 6
    Explanation: The strings that can be formed are "cat" and "hat" so the
                 answer is 3 + 3 = 6.

    --- Example 2 ---
    Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
    Output: 10
    Explanation: The strings that can be formed are "hello" and "world" so the
                 answer is 5 + 5 = 10.

    *** Constraints ***
    1 <= words.length <= 1000
    1 <= words[i].length, chars.length <= 100
    words[i] and chars consist of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    vector of 26 characters is going to be used as a Hash Map to count how many
    of each character is in original "chars".

    Each time we find out that there is more in some words[i] than in "chars"
    of some letters, we break that inner loop and continue with the next word
    in "words".

    If we find out that some word can indeed be formed with characters from
    "chars", we add the lenght of it to "result", as we're asked to do.

    There's not much to it than this. It's straightforward.

*/

/* Time  Beats: 99.07% */
/* Space Beats: 66.56% */

/* Time  Complexity: O(n * m) */
/* Space Complexity: O(1)     */
class Solution {
public:
    int countCharacters(vector<string>& words, string chars)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        int result = 0;

        vector<int> letters(26, 0);
        for (const char& chr : chars)
            letters[chr - 'a']++;

        for (int i = 0; i < words.size(); i++)
        {
            vector<int> letters_copy = letters;
            bool can_be_formed = true;

            for (const char& chr : words[i])
            {
                if (letters_copy[chr - 'a'] == 0)
                {
                    can_be_formed = false;
                    break;
                }
                else
                    letters_copy[chr - 'a']--;
            }

            if (can_be_formed)
                result += words[i].length();
        }

        return result;
    }
};
