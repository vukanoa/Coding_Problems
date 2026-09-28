/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    3844) Longest Almost-Palindromic Substring
    ==========================================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters.

    A substring is almost-palindromic if it becomes a substring after removing
    exactly one character from it.

    Return an integer denoting the length of the longest almost-palindromic
    substring in s.

    ==========================================
    FUNCTION: int almostPalindromic(string s);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abca"
    Output: 4
    Explanation:
    Choose the substring "abca".
        + Remove "abca".
        + The string becomes "aba", which is a palindrome.
        + Therefore, "abca" is almost-palindromic.

    --- Example 2 ---
    Input: s = "abba"
    Output: 4
    Explanation:
    Choose the substring "abba".
        + Remove "abba".
        + The string becomes "aba", which is a palindrome.
        + Therefore, "abba" is almost-palindromic.

    --- Example 3 ---
    Input: s = "zzabba"
    Output: 5
    Explanation:
    Choose the substring "zzabba".
        + Remove "zabba".
        + The string becomes "abba", which is a palindrome.
        + Therefore, "zabba" is almost-palindromic.


    *** Constraints ***
    2 <= s.length <= 2500
    s consists of only lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This problem was difficult to many people, but I didn't quite understand
    why.

    It's a pretty straightforward one if you've ever done problems with
    palindromes.

    We know there are ODD length and EVEN length palindromes.
    Now simply do them separately.

    Of course, doing palindromes is almost always done from the "middle"
    outwardly.

    However, since we're allowed to "remove" (i.e. skip) one character, then
    anytime we stumble upon two differing characters, we try two combinations:

        + One without the current character under the "left"  pointer
        + One without the current character under the "right" pointer

    and we "append" its length to the length of the already palindromic
    substring we've previously found starting at this "mid" character.


    It's important that we do NOT forget to do a (1 +) when taking the best
    result since we need to count the size of the SUBSTRING and NOT the longest
    actual palindrome after skipping.

    In other worsds--We MUST count the TOTAL length of the substring, including
    the otpinally removed character.


    Let's see an example:

        A  B  C  D  E  F  G  F  E  X  D  C  B  A
        0  1  2  3  4  5  6  7  8  9  0  1  2  3
                 L  #  #  #  #  #  R
                    ^^^^^^^^^^^^^
                          |
        __________________|
        |

        Longest "middle" palindromic substring.

        However now s[L] and s[R] are DIFFERING. Therefore, we try two
        combinations:

            1. 
                A  B  C  D  E  F  G  F  E  X  D  C  B  A
                0  1  2  3  4  5  6  7  8  9  0  1  2  3
                         L  #  #  #  #        R


            2.
                A  B  C  D  E  F  G  F  E  X  D  C  B  A
                0  1  2  3  4  5  6  7  8  9  0  1  2  3
                      L     #  #  #  #     R   


        The first one is going to get us additional 8 characters, whereas the
        second one will NOT get us ANY additional characters since C != X will
        immediately stop the bonus length.

*/

/* Time  Beats: 80.28% */
/* Space Beats: 95.31% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int almostPalindromic(string s)
    {
        const int N = s.size();
        int result = 1;

        //////////////////////////////
        /// ODD length palindromes ///
        //////////////////////////////
        for (int mid = 0; mid < N; mid++) // Starting from the MIDDLE of a palindrome
        {
            int substring_len = 1;

            int left  = mid - 1;
            int right = mid + 1;
            while (left >= 0 && right < N && s[left] == s[right])
            {
                substring_len += 2;

                --left;
                ++right;
            }

            // If substring_len is NOT entire string, then we can CERTAINLY get
            // a substring with 1 additional character(ANY adjacent character)
            // since we did NOT use our removal in the first while-loop
            if (substring_len < N) 
                result = max(result, 1 + substring_len);
            else
                result = max(result, 0 + substring_len);

            // Here we try continuing without either current left or current
            // right character
            if (left >= 0 && right < N)
            {
                int bonus_without_left  = without_removals(s, left-1, right  , N);
                int bonus_without_right = without_removals(s, left  , right+1, N);

                // +1 since we have used our 1 allowed removal
                substring_len += 1 + max(bonus_without_left, bonus_without_right);
            }

            result = max(result, substring_len);
        }


        ///////////////////////////////
        /// EVEN length palindromes ///
        ///////////////////////////////
        for (int mid = 0; mid < N-1; mid++) // Starting from the MIDDLE of a palindrome
        {
            int substring_len = 0;

            int left  = mid;
            int right = mid + 1;
            while (left >= 0 && right < N && s[left] == s[right])
            {
                substring_len += 2;

                --left;
                ++right;
            }

            // If substring_len is NOT entire string, then we can CERTAINLY get
            // a substring with 1 additional character(ANY adjacent character)
            // since we did NOT use our removal in the first while-loop
            if (substring_len < N)
                result = max(result, 1 + substring_len);
            else
                result = max(result, 0 + substring_len);

            // Here we try continuing without either current left or current
            // right character
            if (left >= 0 && right < N)
            {
                int bonus_without_left  = without_removals(s, left-1, right  , N);
                int bonus_without_right = without_removals(s, left  , right+1, N);

                // +1 since we have used our 1 allowed removal
                substring_len += 1 + max(bonus_without_left, bonus_without_right);
            }

            result = max(result, substring_len);
        }


        return result;
    }

private:
    int without_removals(string& s, int left, int right, const int& N)
    {
        int substring_len = 0;
        while (left >= 0 && right < N && s[left] == s[right])
        {
            substring_len += 2;

            --left;
            ++right;
        }

        return substring_len;
    }
};
