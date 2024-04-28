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




/*
    ------------
    --- IDEA ---
    ------------

    A bit of a different approach than above. Instead of first finding indices
    of all the vowels in string s, we know swap vowels as we stumble upon them
    from both left and right side.

    In each iteration we first iterate through s from left to right until we
    hit a vowel.

    Then we iterate through s from right to left until we hit a vowel.

    Those indices are represented in "start" and "end", respectively.
    (That means - In subsequent iterations we will begin from "start" and from
     "end", respectively)

    Then we swap those two characters within the string s.

    Once start == end or start < end, we break the "while loop" and return s.

*/

/* Time  Beats: 43.67% */
/* Space Beats: 33.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    std::string reverseVowels(std::string s)
    {
        // Convert the input string to a character array.
        std::string word = s;

        std::string vowels = "aeiouAEIOU";

        int start = 0;
        int end = s.length() - 1;

        while (start < end)
        {
            // Move "start" pointer towards the end until it points to a vowel
            while (start < end && vowels.find(word[start]) == string::npos)
                start++;

            // Move "end" pointer towards the start until it points to a vowel
            while (start < end && vowels.find(word[end]) == string::npos)
                end--;

            // Swap the vowels found at the start and end positions.
            std::swap(word[start], word[end]);

            // Move the pointers towards each other for the next iteration.
            start++;
            end--;
        }

        // Return the modified string.
        return word;
    }
};
