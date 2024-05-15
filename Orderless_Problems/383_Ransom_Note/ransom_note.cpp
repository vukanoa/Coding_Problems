#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    383) Ransom Note
    ===========================

    ============
    Description:
    ============

    Given two strings ransomNote and magazine, return true if ransomNote can be
    constructed by using the letters from magazine and false otherwise.

    Each letter in magazine can only be used once in ransomNote.

    ================================================================
    FUNCTION: bool canConstruct(string ransomNote, string magazine);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: ransomNote = "a", magazine = "b"
    Output: false

    --- Example 2 ---
    Input: ransomNote = "aa", magazine = "ab"
    Output: false

    --- Example 3 ---
    Input: ransomNote = "aa", magazine = "aab"
    Output: true


    *** Constraints ***
    1 <= ransomNote.length, magazine.length <= 10^5
    ransomNote and magazine consist of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Since both ransomeNote and magazine are consisted of only lowercase English
    letters, we can use a vector of ints of size 26, because there are exactly
    26 lowercase English characters.

    We will be using that vector as a Hash Map, though now we can consider this
    vector to be O(1) in Time because O(26) is O(1). Plus, vectors are nicely
    optimized, so it's even faster to use a vector than a Hash Map.

    Now, since in the 3rd Example, we're told:

        Input: ransomNote = "aa", magazine = "aab"
        Output: true

    Meaning - We can have redundant characters in magazine, i.e. characters
    that do NOT exist in ransomNote, but not the other way around.

    Therefore, only if some characters is greater than 0 in our "Hash Map"(i.e.
    vector) are we going to decrement it by one.

    If we, however, stumble upon an empty entry, meaning - That character does
    exist in magazine but does NOT exist in the ransomNote, we can just ignore
    that.

    As you can see in the above 3rd Example, character 'b' exists in magazine,
    but does NOT exist in ransomNote, however we are still returning "true",
    since we can indeed form a word in ransomNote from the characters in
    magazine.

    At the end of processing magazine, if we've managed to "nullify", or to
    cover every letter that appears in ransomNote, then we can return true.

    To check that, we're going to take use of another vector called
    "null_vector" that is a vector with 26 0's.

    If, at the end, ransom_letters is also a vector of 26 0's, then we've
    succeded in our attempt.

    Otherwise, we return false.

*/

/* Time  Beats: 90.73% */
/* Space Beats: 80.91% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool canConstruct(std::string ransomNote, std::string magazine)
    {
        std::vector<int> ransom_letters(26, 0);
        std::vector<int> null_vector(26, 0);

        for (const char& chr : ransomNote)
            ransom_letters[chr - 'a']++;

        for (const char& chr : magazine)
        {
            if (ransom_letters[chr - 'a'] > 0)
                ransom_letters[chr - 'a']--;
        }

        return ransom_letters == null_vector;
    }
};
