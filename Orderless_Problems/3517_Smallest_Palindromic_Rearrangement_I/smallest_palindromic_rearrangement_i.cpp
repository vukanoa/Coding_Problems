/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    3517) Smallest Palindromic Rearrangement I
    ==========================================

    ============
    Description:
    ============

    You are given a palindromic string s.

    Return the lexicographically smallest palindromic permutation of s.

    ==============================================
    FUNCTION: string smallestPalindrome(string s);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "z"
    Output: "z"
    Explanation: A string of only one character is already the
                 lexicographically smallest palindrome.

    --- Example 2 ---
    Input: s = "babab"
    Output: "abbba"
    Explanation: Rearranging "babab" → "abbba" gives the smallest
                 lexicographic palindrome.

    --- Example 3 ---
    Input: s = "daccad"
    Output: "acddca"
    Explanation: Rearranging "daccad" → "acddca" gives the smallest
                 lexicographic palindrome.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of lowercase English letters.
    s is guaranteed to be palindromic.

*/

#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The most important thing in this problem is to know that a palindrome can
    either be:

        + Of even length
        + of odd  length

    Odd length palindrome have ONE AND ONLY ONE character that occurrs ODD
    number of times!

    This is crucial!

    Example:
        Even palindromes: "aabbaa", "abaaba",      "abbbcffcbbba"
        Odd  palindromes: "aabaa",  "abafffffaba", "abbbcfafcbba"
                             ^            ^               ^
                             |            |               |
                             |            |               |
                            b: 1        f: 5            a: 3


    So let me repeat again, if a palindrome is of ODD length there must be
    EXACTLY ONE character with ODD frequency. All of the other characters MUST
    have frequencies that are EVEN!

    Read that one more time.

    Once you understand that, know the next part is: since we want the
    lexicographically smallest string, we can only grapple with the left part
    of the palindrome.

    This "left part of the palindrome" IS THE SAME FOR BOTH ODD AND EVEN LENGTH
    PALINDROMES, it's first N/2 characters!

        Even palindrome: "cacbbcac"  // len = 8
        Odd  palindrome: "cacbbbcac" // len = 9

    the part we're fiddling with is: "cacb".

    What permutation of "cacb" is the smallest"?
    Of course, it's: "abcc".

    One simple way to do that is count the frequencies of each characters in
    our palindromic string(it is guaranteed s is a palindrome according to our
    Constraints).

    Let's consider these two examples:
        Even palindrome: "cacbbcac"  // len = 8
        Odd  palindrome: "cacbbbcac" // len = 9

    Even palindrome:

             Counter
        |  Key  :  Value |
        +----------------+
        |  'a'  :    2   |
        +----------------+
        |  'b'  :    2   |
        +----------------+
        |  'c'  :    4   |
        +----------------+


    Odd palindrome:

             Counter
        |  Key  :  Value |
        +----------------+
        |  'a'  :    2   |
        +----------------+
        |  'b'  :    3   |
        +----------------+
        |  'c'  :    4   |
        +----------------+


    However, since we're only dealing with lowercase English characters,
    instead of using a HashMap, we use vector<int> of isze 26.

    We simply go through those 26 frequencies starting from 0 which represents
    'a' and going all the way up to 25(inclusive) which is a letter 'z'.

    Since we only need to form the LEFT part, we only concatenate half of each
    frequency.


             Counter                                     Counter
        |  Key  :  Value |                          |  Key  :  Value |
        +----------------+                          +----------------+
        |  'a'  :    2   |                          |  'a'  :    1   |
        +----------------+         becomes          +----------------+
        |  'b'  :    3   |      ----------->        |  'b'  :    1   |
        +----------------+                          +----------------+
        |  'c'  :    4   |                          |  'c'  :    2   |
        +----------------+                          +----------------+


    However since we had 3 b's, we need to remember that the "extra" character
    that we need to put(since the palindrome is of ODD length) is 'b'.

    Now we just take: 1 a, 1 b, 2 c's

    left = "abcc"

    Then we add "extra character", which is 'b'.

    left = abccb

    and then we concatenate reversed string of "left" BEFORE we added this
    extra character(because that character DOES NOT repeat)

    right = "ccba"


    final = "abccbccba"

    And we're returning that.

*/

/* Time  Beats: 57.89% */
/* Space Beats: 21.05% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string smallestPalindrome(string s)
    {
        const int N = s.size();

        if (N == 1)
            return s;

        vector<int> counter(26, 0);
        for (const char& chr : s)
            counter[chr - 'a']++;

        int extra = -1;

        ostringstream out;
        for (int i = 0; i < 26; i++)
        {
            if (counter[i] & 1)
                extra = i;

            char curr_chr = i + 'a';

            for (int x = 0; x < counter[i] / 2; x++)
                out << curr_chr;
        }

        string left  = out.str();
        string right = left;
        reverse(right.begin(), right.end());

        if (extra != -1)
        {
            char extra_character = extra + 'a';
            left += extra_character;
        }

        left += right;


        return left;
    }
};
