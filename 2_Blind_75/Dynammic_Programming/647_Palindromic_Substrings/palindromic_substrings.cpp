#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    647) Palindromic Substrings
    ===========================

    ============
    Description:
    ============

    Given a string s, return the number of palindromic substrings in it.

    A string is a palindrome when it reads the same backward as forward.

    A substring is a contiguous sequence of characters within the string.

    ========================================
    FUNCTION: int countSubstrings(string s);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abc"
    Output: 3
    Explanation: Three palindromic strings: "a", "b", "c".

    --- Example 2 ---
    Input: s = "aaa"
    Output: 6
    Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

    *** Constraints ***
    1 <= s.length <= 1000
    s consists of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Idea is almost equivalent as Solution for "Longest Palindromic Substring"
    Problem.

    However we don't have to check if the current palindromic substring is the
    longest. We only have to count each palindromic substring.

    We have to do this in two passes because there are palindromes that have:
        1. Odd  number of letters // "abcba"
        2. Even number of letters // "abba"


    I) Mid different "abcba"
            Let's say we're starting here(# represents the "mid" pointer):

                    "abcba"
                       #

            Each iteration we are checking:
                    if "s[mid - x]" and "s[mid + x]" are the

            where 'x' starts from 0.
            So in the beginning it only checks a single letter which is always
            a palindrome itself, so we've covered those cases as well.

            Let's look Iteration by Iteration:

            1.      "abcba"
                      ^#^

            2.      "abcba"
                     ^ # ^



    II) Mid same "abba"
            Let's say we start like this(# represents the "mid" pointer):

                    "abba"
                      #

            Iteration by Iteration:

            1.      "abba"
                      #^
                      ^

            2.      "abba"
                     ^# ^


    If at any point in these two types of checking for a palindrome we find
    that at some point it's no longer a plindrome, we can immediately break
    the inner loop and start from the next letter as a mid.

    At the end we just return "count".

*/

/* Time  Beats: 100% */
/* Space Beats: 79.42% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countSubstrings(std::string s)
    {
        if (s.length() == 1)
            return 1;

        int n = s.length();
        int count = 0;

        // Mid different "abcba"
        for (int mid = 0; mid < n; mid++)
        {
            for (int x = 0; mid - x >= 0 && mid + x < n; x++)
            {
                if (s[mid - x] == s[mid + x])
                    count++;
                else
                    break;
            }
        }

        // Mid same "abba"
        for (int mid = 0; mid < n-1; mid++)
        {
            for (int x = 1; mid - x + 1 >= 0 && mid + x < n; x++)
            {
                if (s[mid - x + 1] == s[mid + x])
                    count++;
                else
                    break;
            }
        }

        return count;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, only implemented slightly differently. Some people may find
    this implementation easier to read and grasp.

*/

/* Time  Beats: 83.20% */
/* Space Beats: 81.57% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int countSubstrings(string s)
    {
        const int N = s.length();
        int palindromes = N; // All the individual characters in s

        /* Odd palindromes */
        for (int mid = 0; mid < N; mid++)
        {
            for (int i = mid-1, j = mid+1; i >= 0 && j < N; i--, j++)
            {
                if (s[i] != s[j])
                    break;

                palindromes++;
            }
        }

        /* Even palindromes */
        for (int mid = 0; mid < N-1; mid++)
        {
            for (int i = mid, j = mid+1; i >= 0 && j < N; i--, j++)
            {
                if (s[i] != s[j])
                    break;

                palindromes++;
            }
        }

        return palindromes;
    }
};
