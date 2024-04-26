#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    409) Longest Palindrome
    ===========================

    ============
    Description:
    ============

    Given a string s which consists of lowercase or uppercase letters, return
    the length of the longest palindrome that can be built with those letters.

    Letters are case sensitive, for example, "Aa" is not considered a
    palindrome here.

    ==========================================
    FUNCTION: int longestPalindrome(string s);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abccccdd"
    Output: 7
    Explanation: One longest palindrome that can be built is "dccaccd", whose
                 length is 7.

    --- Example 2 ---
    Input: s = "a"
    Output: 1
    Explanation: The longest palindrome that can be built is "a", whose length
                 is 1.


    *** Constraints ***
    1 <= s.length <= 2000
    s consists of lowercase and/or uppercase English letters only.

*/

/*
    ------------
    --- IDEA ---
    ------------

    If we were to use only lowercase and uppercase, then we'd have:
        std::vector<int> letters(57);

    Why 57 and not 52? (You may ask)

    Because in ASCII, at positions: 91, 92, 93, 94, 95 there are non-letter
    characters, thus we would almost have to include all those 5 not to
    overcomplicate our life even more.

    Now each time we index, we'd have to do this:

        letters[chr - 'A']

    Therefore, since 71 additional bytes isn't much and since it's constant
    different and since 128 itself is constant, then we can proceed and pretend
    to care about all 128 characters and as an extension have easier indexing,
    thus making our life a bit easier.


    First we're going to count occurrences of all the lowercase and uppercase
    letters we're using, i.e. the only characters we care in our 128 ASCII
    table.

    Characters that we do NOT care about are going to have 0 as its occurrence
    number anyway, which doesn't create any problems, therefore we can just
    ignore that.

    Now go through all of those 128 occurrence numbers in vector "ascii" and
    each time you find out that the occurrence of that particular character
    (i.e. letter,  because we only care about lowercase and uppercase English
     letters) is greater than or equals than 2, then we can divide it by 2 and
     temporarily store it and then multiply by 2 again.

    You may ask - What is the purpose of dividing a number by 2 and then
    immediately multiplying it by 2 again?

    The purpose is to count how many characters can we use to create a
    palindrome.

    Remember that a palindrome has to be read in the same way:
        1. From left  to right, and
        2. From right to left

    Therefore, we only care about the even number of occurrences. If the number
    occurs odd number of times, we do not care about that one additional
    character.

    If we have s = "cccbbb" (3 c's and 3 b's)

    3 b's // We care only about 2 b's
    3 c's // We care only about 2 c's

    The longest palindrome we can create is of length 4: "cbbc" or "bccb".

    But... Is that REALLY TRUE?
    No!

    A palindrome itself can have an odd number of characters!
    However, the important thing is - If the number occurs odd number of times
    we can indlude that one additional character in our palindrome constructing
    but we can do that ONLY ONCE GLOBALLY!

    What does "only once globally" means here?

    It means that if, in the above example, we include this one additional b
    character in our palindrome constructing, then we CANNOT and MUST NOT use
    the one additional c character that exists as well.

    Remember:
        3 b's
        3 c's

    Previously we thought that: "cbbc" or "bccb" are the longest palindromes,
    but now we know that's now true. Now we know that if we include that one
    additional character and thus form an ODD LENGTH PALINDROME, we'd be better
    off than not including any one of those additional characters in those
    odd number of occurrence letters.

    Thus, the longest palindrome is either:
        1. "cbcbc", or  // one additional is taken from 3 c's
        2. "bcccb", or  // one additional is taken from 3 c's
        3. "bcbcb", or  // one additional is taken from 3 b's
        4. "cbbbc", or  // one additional is taken from 3 b's


    Since we're only asked to return the LENGTH of the longest palindrome, we
    do not care which one additional character out of all the odd occurring
    letters shall we include. It doesn't matter as long as we include exactly
    one out of all the odd occuring character(i.e. lowercase and uppercase
    English letters, since those are the ones we care about exclusively)

    Therefore, now we iterate through all of 128 fields in vector "ascii" and
    each time we find that the occurence of some character is an odd number
    (occurrence of non-lowercase and non-uppercase will always be 0), we only
    mark that such number of occurrence exists in vector "ascii".

    We do that by:
        if (ascii[i] & 1)
            odd = true;

    Once we're done with iterating through all 128 fields in vector "ascii" and
    once we have cumulatively added all the even number of occurrences (if we
    stumble upon an occurrence of 7, we would include 6 characters, i.e. we
    would add 6 to our "palindrome_length" variable), then at the very end we
    only ask ourselves - Were there ANY lowercase or uppercase English letters
    that did occur odd number of times?

    If the answer is yes - We increment "palindrome_length" by 1.

    At the end we return "palindrome_length"

*/

/* Time  Beats: 100.00% */
/* Space Beats:  87.85% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // Cause it's always only lowercase and uppercase
class Solution {
public:
    int longestPalindrome(std::string s)
    {
        /*
           We're using 128 instead of only lowercase and uppercase because it's
           easier to index. We don't have to subtract 'A'(65) each time we're
           accessing an element. Besides that it's only ~60 bytes more.
        */
        std::vector<int> ascii(128);

        /* Count occurrence of each letter in string s */
        for (const char& chr : s)
            ascii[chr]++;

        int palindrome_length = 0;
        bool odd = false;

        for (int i = 0; i < 128; i++)
        {
            if (ascii[i] & 1)
                odd = true;

            if (ascii[i] >= 2)
                palindrome_length += ascii[i] / 2 * 2;
        }

        if (odd)
            palindrome_length++;

        return palindrome_length;
    }
};
