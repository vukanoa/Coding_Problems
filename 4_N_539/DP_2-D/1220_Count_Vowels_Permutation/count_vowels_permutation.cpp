#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ==============================
    1220) Count Vowels Permutation
    ==============================

    ============
    Description:
    ============

    Given an integer n, your task is to count how many strings of length n can
    be formed under the following rules:

        + Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
        + Each vowel 'a' may only be followed by an 'e'.
        + Each vowel 'e' may only be followed by an 'a' or an 'i'.
        + Each vowel 'i' may not be followed by another 'i'.
        + Each vowel 'o' may only be followed by an 'i' or a 'u'.
        + Each vowel 'u' may only be followed by an 'a'.

    Since the answer may be too large, return it modulo 10^9 + 7.

    ===========================================
    FUNCTION: int countVowelPermutation(int n);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1
    Output: 5
    Explanation: All possible strings are: "a", "e", "i" , "o" and "u".

    --- Example 2 ---
    Input: n = 2
    Output: 10
    Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io",
                 "iu", "oi", "ou" and "ua".

    --- Example 3 ---
    Input: n = 5
    Output: 68


    *** Constraints ***
    1 <= n <= 2 * 10^4

*/

/* Time  Beats: 67.69% */
/* Space Beats: 80.20% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countVowelPermutation(int n)
    {
        const int MOD = 1e9 + 7;

        vector<vector<int>> record = {{1, 2, 4}, {0, 2}, {1, 3}, {2}, {2, 3}};
        vector<long long> vowels(5, 1), vowels_val;

        long long result = 0;

        while (--n)
        {
           vowels_val = vowels;

           for (int i = 0; i < 5; i++)
           {
              vowels[i] = 0;

              for (int j : record[i])
              {
                  vowels[i] += vowels_val[j];
                  vowels[i] %= MOD;
              }
           }
        }

        for (long long &i : vowels)
        {
           result += i;
           result %= MOD;
        }

        return result;
    }
};
