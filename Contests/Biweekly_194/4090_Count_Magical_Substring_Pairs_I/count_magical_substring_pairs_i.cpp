/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    4090) Count Magical Substring Pairs I
    =====================================

    ============
    Description:
    ============

    You are given a string s of length n consisting of lowercase English
    letters.

    For every triplet of indices (i, j, k) satisfying 0 <= i <= j < k < n,
    define:

        s1 = s[i..j]
        s2 = s[j + 1..k]

    A pair of substrings (s1, s2) is called magical if the number of distinct
    characters in s1 is equal to the number of distinct characters in s2.

    Return the number of triplets (i, j, k) for which (s1, s2) is a magical
    pair.

    A substring is a contiguous non-empty sequence of characters within a
    string.

    ==========================================
    FUNCTION: int countMagicalPairs(string s);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aba"
    Output: 2
    Explanation:
    There are 2 valid triplets:
    No.    (i, j, k)    s1    s2    distinct(s1)    distinct(s2)
    1      (0, 0, 1)    "a"    "b"       1               1
    2      (1, 1, 2)    "b"    "a"       1               1


    --- Example 2 ---
    Input: s = "kkk"
    Output: 4
    Explanation:
    There are 4 valid triplets:
    No.    (i, j, k)    s1     s2    distinct(s1)    distinct(s2)
    1      (0, 0, 1)    "k"    "k"       1               1
    2      (0, 0, 2)    "k"    "kk"      1               1
    3      (0, 1, 2)    "kk"   "k"       1               1
    4      (1, 1, 2)    "k"    "k"       1               1


    --- Example 3 ---
    Input: s = "abcac"
    Output: 7
    Explanation:
    There are 7 valid triplets:
    No.    (i, j, k)    s1     s2    distinct(s1)    distinct(s2)
    1      (0, 0, 1)    "a"    "b"       1               1
    2      (1, 1, 2)    "b"    "c"       1               1
    3      (2, 2, 3)    "c"    "a"       1               1
    4      (3, 3, 4)    "a"    "c"       1               1
    5      (0, 1, 3)    "ab"   "ca"      2               2
    6      (0, 1, 4)    "ab"   "cac"     2               2
    7      (1, 2, 4)    "bc"   "ac"      2               2


    *** Constraints ***
    2 <= s.length <= 2000
    s consists of lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 64.36% */
/* Space Beats: 82.04% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int countMagicalPairs(string s)
    {
        const int N = s.size();
        int result = 0;

        for (int j = 0; j < N-1; j++)
        {
            int L_freq[26] = {};
            int R_freq[26] = {};

            int L_distinct = 0;
            int R_distinct = 0;

            int L_subarrays_count_with[27] = {}; // with 1..26 DISTINCT chars
            int R_subarrays_count_with[27] = {}; // with 1..26 DISTINCT chars


            for (int i = j; i >= 0; i--)
            {
                ++L_freq[s[i] - 'a'];

                if (L_freq[s[i] - 'a'] == 1)
                    ++L_distinct;

                ++L_subarrays_count_with[L_distinct];
            }

            for (int k = j+1; k < N; k++)
            {
                ++R_freq[s[k] - 'a'];

                if (R_freq[s[k] - 'a'] == 1)
                    ++R_distinct;

                ++R_subarrays_count_with[R_distinct];
            }

            for (int distinct = 1; distinct <= 26; distinct++)
            {
                result += L_subarrays_count_with[distinct] *
                          R_subarrays_count_with[distinct];
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 74.82% */
/* Space Beats: 88.42% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Bit_Manipulation {
public:
    int countMagicalPairs(string s)
    {
        const int N = s.size();
        int result = 0LL;

        // Fix the middle split point 'j' where s1 ends (at j) and s2 begins (at j+1)
        for (int j = 0; j < N-1; j++)
        {
            // count_of_subarrays_with[distinct] stores how many left substrings s[i..j] have exactly "distinct" characters
            int count_of_subarrays_with[27] = {};
            int L_freq = 0;
            int R_freq = 0;

            // Step 1: Expand s1 = s[i..j] to the left and record distinct character counts
            for (int i = j; i >= 0; i--)
            {
                L_freq |= 1 << (s[i] - 'a'); // same as ++L_freq[s[i] - 'a'], if we had: int L_freq[26] = {}

                int distinct_chars_in_s1 = __builtin_popcount(L_freq); // Count set bits
                ++count_of_subarrays_with[distinct_chars_in_s1];
            }

            // Step 2: Expand s2 = s[j+1..k] to the right and match with s1 counts
            for (int k = j+1; k < N; k++)
            {
                R_freq |= 1 << (s[k] - 'a'); // same as ++R_freq[s[k] - 'a'], if we had: int R_freq[26] = {}

                int distinct_chars_in_s2 = __builtin_popcount(R_freq); // count set bits
                result += count_of_subarrays_with[distinct_chars_in_s2]; // Add all valid LEFT subarrays that had THE SAME count
            }
        }

        return result;
    }
};
