#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===============================
    345) Reverse Vowels Of A String
    ===============================

    ============
    Description:
    ============

    Given a string s, reverse only all the vowels in the string and return it.

    The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both
    lower and upper cases, more than once.

    =========================================
    FUNCTION: string reverseVowels(string s);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "hello"
    Output: "holle

    --- Example 2 ---
    Input: s = "leetcode"
    Output: "leotcede"


    *** Constraints ***
    1 <= s.length <= 3 * 10^5
    s consist of printable ASCII characters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Fill vector "vowels" with both lowercase and uppercase vowels and then
    assign variable 'i' to 0 and variable 'j' to vowels.size()-1 and starting
    swapping s[vowels[i]] and s[vowels[j]].

    Each time you swap, increment i, but decrement j.

    Once they meet, we stop and return string s.

*/

/* Time  Beats: 59.12% */
/* Space Beats: 21.67% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string reverseVowels(std::string s)
    {
        std::vector<int> vowels;

        for (int i = 0; i < s.length(); i++)
        {
            char chr = s[i];

            if (chr == 'a' || chr == 'A' ||
                chr == 'e' || chr == 'E' ||
                chr == 'i' || chr == 'I' ||
                chr == 'o' || chr == 'O' ||
                chr == 'u' || chr == 'U')
            {
               vowels.push_back(i);
            }
        }

        int i = 0;
        int j = vowels.size()-1;

        while (i <= j)
            std::swap(s[vowels[i++]], s[vowels[j--]]);

        return s;
    }
};
