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

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Idea is almost equivalent as Solution for:

        LeetCode: 5. "Longest Palindromic Substring"

    However we don't have to check if the current palindromic substring is the
    longest. We ONLY have to count each palindromic substring.

    We must do it in two passes because there are 2 kinds of palindromes:
        1. Palindorme of ODD  number of letters (i.e. "abcba")
        2. Palindorme of EVEN number of letters (i.e. "abba" )


    1) ODD Palindromes:

                    "abcba"  --->  "abcba" --->  "abcba"
                       L             L R          L   R
                       R


    2) EVEN palindromes:

                    "abba"   --->  "abba"
                      LR            L  R

        It's VERY important to notice that we CANNOT start our "mid" in
        EVEN palindromes at index "N-1".

        Why?
        The comment below explains it in detail. Make sure to understand that.

        for (int mid = 0; mid < N-1; mid++) // mid must stop at N-2 because:
        {
            int L = mid;
            int R = mid+1; // If mid = N-1, then R = N (null terminator, valid)
                           // However, after R++, R becomes N+1, causing
                           // undefined behavior (possible segfault or garbage
                           // access). That's why it's important for mid to go:
                           //
                           // [0...N-2] and not [0...N-1]


            ....
        }


    If at any point in these two types of checking for a palindrome we find
    that at some point it's no longer a palindrome, we can immediately break
    the inner loop and start from the next letter as a mid.

    At the end we just return "result".

*/

/* Time  Beats: 87.24% */
/* Space Beats: 91.03% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int countSubstrings(string s)
    {
        const int N = s.size();
        int result = 0;

        /* Odd */
        for (int mid = 0; mid < N; mid++)
        {
            int L = mid;
            int R = mid;

            while (L >= 0 && R < N)
            {
                if (s[L] != s[R])
                    break;

                result++;

                L--; // Decrement
                R++; // Increment
            }
        }

        /* Even palindromes */
        for (int mid = 0; mid < N-1; mid++)
        {
            int L = mid;
            int R = mid+1; // If mid = N-1, then R = N (null terminator, valid)
                           // However, after R++, R becomes N+1, causing
                           // undefined behavior (possible segfault or garbage
                           // access). That's why it's important for mid to go:
                           //
                           // [0...N-2] and not [0...N-1]

            while (L >= 0 && R < N)
            {
                if (s[L] != s[R])
                    break;

                result++;

                L--; // Decrement
                R++; // Increment
            }
        }

        return result;
    }
};
