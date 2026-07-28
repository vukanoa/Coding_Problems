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

    (Note: This Solution is for didactic purposes. It is NOT the most efficient
           way to solve it. For the more efficient way, check out the 2nd
           solution "Solution_Optimized" down below)


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




/*
    ------------
    --- IDEA ---
    ------------

    Simply count the frequencies of each character in string s and then go
    through those frequencies in ALPHABETIC order and place two characters in
    the result string, where one character goes at index "idx" and the other
    at index "N-1 - idx".

    Each time we increment the "idx" variable.

    If 'N' is ODD, that means the original string s certainly has a MIDDLE
    character that has an ODD frequency.

    Now this is important--ODD frequency can either be 1 or 3,5,7,etc.

    Why do we make this distinction?

    Because there there are: 3, 5, 7, 9, etc. then we'd take two of those at
    each turn and we'd place them at [idx] and [N-1 - idx] indices until we're
    left with a SINGLE frequency character.

    The SINGLE frequency character is the MIDDLE CHARACTER that we put at the
    very end of the processing.

    MIDDLE CHARACTER EXISTS IF AND ONLY IF THE N IS ODD!

    Therefore, if (N & 1), i.e. "N is ODD", we put mid_chr at [idx] which is
    now the middle position.

*/

/* Time  Beats: 80.00% */
/* Space Beats: 80.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Optimized {
public:
    string smallestPalindrome(string s)
    {
        const int N = s.size();
        string result(N, '0');

        int freq[26] = {0};
        for (const char& chr : s)
            freq[chr - 'a']++;

        int idx = 0;
        char mid_chr = '0';
        for (int i = 0; i < 26; i++)
        {
            if (freq[i] == 0)
                continue;

            while (freq[i] >= 2)
            {
                result[idx]       = static_cast<char>(i + 'a');
                result[N-1 - idx] = static_cast<char>(i + 'a');

                idx++;
                freq[i] -= 2;
            }   

            if (freq[i] == 1)
                mid_chr = static_cast<char>(i + 'a');
        }

        if (N & 1) // If size of string s is ODD--There is 1 char with freq 1
            result[idx] = mid_chr;

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Here we not only reuse 's', thus reducing the Space Complexity down to O(1)
    but we also do it in HALF THE TIME of the above solution since we are only
    processing the first half of s.

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Optimized_Further {
public:
    string smallestPalindrome(string s)
    {
        const int N = s.size();
        int freq[26] = {0};

        /*
            Traverse the only the first half   (N >> 1  <==>  N / 2)

            If N is ODD--do NOT traverse that middle character since that
            middle character absolute MUST and WILL remain where it already is.

            No need to "rearrange" it. That's the only position where that
            character can be at.

            Example:

                s = "fbgccyccgbf"
                          ^
                          |

            No matter the lexicographical ordering of this PALINDROME(it MUST
            remain a palindrome) can have 'y' and ANY OTHER POSITION than where
            already is.


            Also, [(s[i] & 31) -1] means that both s[i]='a' and s[i]='A' would
            BOTH be at index 0.

            'a' =  97  ==>   97 & 31 = 1  ==>   1 - 1 = 0
            'A' =  65  ==>   65 & 31 = 1  ==>   1 - 1 = 0

            ..

            'c' =  99  ==>  99 & 31 = 3   ==>   3 - 1 = 2
            'C' =  67  ==>  67 & 31 = 3   ==>   3 - 1 = 2

            ...

            'z' = 122  ==> 122 & 31 = 26  ==>  26 - 1 = 25
            'Z' =  90  ==>  90 & 31 = 26  ==>  26 - 1 = 25

        */
        for (int i = 0; i < (N >> 1); i++)            
            freq[(s[i] & 31) - 1]++; // Both 'a' and 'A' would be at 0

        int idx = 0;
        for (int i = 0; i < 26; i++)
        {
            while (freq[i]-- > 0)
            {                
                // Conversion to "char" is IMPLICIT
                s[idx]       = i + 'a';
                s[N-1 - idx] = i + 'a';

                // Increment
                idx++;
            }
        }

        return s;
    }
};
