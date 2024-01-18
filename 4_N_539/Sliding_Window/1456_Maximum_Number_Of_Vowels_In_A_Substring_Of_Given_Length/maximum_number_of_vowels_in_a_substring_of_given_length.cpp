#include <iostream>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================================================
    1456) Maximum Number of Vowels in a Substring of Given Length
    =============================================================

    ============
    Description:
    ============

    Given a string s and an integer k, return the maximum number of vowel letters in any substring of s with length k.

    Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.

    =========================================
    FUNCTION: int maxVowels(string s, int k);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abciiidef", k = 3
    Output: 3
    Explanation: The substring "iii" contains 3 vowel letters.

    --- Example 2 ---
    Input: s = "aeiou", k = 2
    Output: 2
    Explanation: Any substring of length 2 contains 2 vowels.

    --- Example 3 ---
    Input: s = "leetcode", k = 3
    Output: 2
    Explanation: "lee", "eet" and "ode" contain 2 vowels.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of lowercase English letters.
    1 <= k <= s.length

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory

*/

/* Time  Beats: 30.75% */
/* Space Beats: 20.93% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Sliding_Window_1 {
public:
    int maxVowels(string s, int k)
    {
        std::unordered_set<char> uset = {'a', 'e', 'i', 'o', 'u'};

        int max_vowels = 0;
        int vowels = 0;
        for (int i = 0; i < k; i++)
        {
            if (uset.find(s[i]) != uset.end())
                vowels++;
        }

        max_vowels = std::max(max_vowels, vowels);

        int left  = 0;
        int right = k;
        while (right < s.length())
        {
            if (uset.count(s[right]))
                vowels++;

            if (uset.count(s[left]))
                vowels--;

            max_vowels = std::max(max_vowels, vowels);
            left++;
            right++;
        }

        return max_vowels;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 65.85% */
/* Space Beats: 97.69% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Sliding_Window_2 {
public:
    int max_vowelsVowels(std::string s, int k)
    {
        int max_vowels = 0;
        int vowels = 0;

        int left  = 0;
        int right = 0;

        while (right < s.length())
        {
            if (is_vowel(s[right]))
                vowels++;

            if (right - left + 1 == k)
            {
                max_vowels = std::max_vowels(max_vowels, vowels);

                if (is_vowel(s[left]))
                    vowels--;

                left++;
            }

            right++;
        }

        return max_vowels;
    };

private:
    bool is_vowel(char& c)
    {
        return (c == 'a' ||
                c == 'e' ||
                c == 'i' ||
                c == 'o' ||
                c == 'u');
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory

*/

/* Time  Beats: 27.51% */
/* Space Beats: 20.93% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxVowels(std::string s, int k)
    {
        std::unordered_set<char> uset = {'a', 'e', 'i', 'o', 'u'};

        int max_vowels = 0;
        int vowels = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            vowels += uset.find(s[i]) != uset.end() ? 1 : 0;

            if (i - k >= 0)
                vowels -= uset.find(s[i - k]) != uset.end() ? 1 : 0;

            max_vowels = max(max_vowels, vowels);
        }

        return max_vowels;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

    (Same approach, but this uses Bit Mask instead of a Hash Set)

    Computers are much better at performing bitwise operations.

*/

/* Time  Beats: 98.58% */
/* Space Beats: 72.36% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxVowels(std::string s, int k)
    {
        auto is_vowel = [](char c)
        {
            static const uint32_t b1 = 0x208222;
            static const uint8_t  b2 = 0x1f;
            static const uint8_t  b3 = 0x1;

            return (b1 >> (c & b2)) & b3;
        };

        int max_vowels = 0;
        int vowels = 0;
        for(int i = 0, j = i - k; i < s.size(); ++i, ++j)
        {
            vowels += is_vowel(s[i]);
            if (i >= k)
                vowels -= is_vowel(s[j]);

            max_vowels = max(max_vowels, vowels);
        }

        return max_vowels;
    };
};
