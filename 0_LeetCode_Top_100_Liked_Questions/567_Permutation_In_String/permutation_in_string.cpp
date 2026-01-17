/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    567) Permutation In String
    ===========================

    ============
    Description:
    ============

    Given two strings s1 and s1, return true if s2 contains a permutation of
    s1, or false otherwise.

    In other words, return true if one of s1's premutations is the substring of
    s2.

    ====================================================
    FUNCTION: bool checkInclusion(string s1, string s2);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  s1 = "ab", s2 = "eidbaooo"
    Output: true
    Explanation: s2 contains one permutation of s1 ("ba").

    --- Example 2 ---
    Input:  s1 = "ab", s2 = "eidboaoo"
    Output: false

    *** Constraints ***
    1 <= s1.length, s2.length <= 10^4
    s1 and s2 consist of lowercase English letters

*/


#include <cstring>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Idea is Very Similar to:
        LeetCode Problem 438 "Find All Anagrams In A String"

    The only thing that differs is the return type.

    In the 438-th Problem we needed to count all the anagrams, while in this
    one we only have to tell if there is a permutation of s1 in s2.

    So it's even easier.

*/

/* Time  Beats: 92.60% */
/* Space Beats: 91.21% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_1 {
public:
    bool checkInclusion(string s1, string s2)
    {
        const int SIZE_ONE = s1.size();
        const int SIZE_TWO = s2.size();

        if (SIZE_ONE > SIZE_TWO)
            return false;

        vector<int> freq_s1(26, 0);
        vector<int> freq_s2(26, 0);

        /* First window */
        for (int i = 0; i < s1.length(); i++)
        {
            freq_s1[s1[i] - 'a']++;
            freq_s2[s2[i] - 'a']++;
        }

        if (freq_s1 == freq_s2)
            return true;

        int L  = 0;
        int R = SIZE_ONE;

        /* Sliding Window */
        while (R < SIZE_TWO)
        {
            freq_s2[s2[L] - 'a']--;
            L++;

            freq_s2[s2[R] - 'a']++;
            R++;

            if (freq_s1 == freq_s2)
                return true;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, implemented in another way.

    This one uses basic integer arrays on the Stack instead of utilizing
    "vectors".

    It's handy to know and see both.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  68.34% */

/* Time  Complexity: O(M + N * 128) --> O(M + N) */
/* Space Complexity: O(1)           --> O(1)     */
class Solution_2 {
public:
    bool checkInclusion(string s1, string s2)
    {
        const int M = s1.size();
        const int N = s2.size();

        if (N < M)
            return false;

        int freq_s1[26] = {0};
        int freq_s2[26] = {0};

        for (const char& chr : s1) // O(M)
            freq_s1[chr - 'a']++;

        int L = 0;
        for (int R = 0; R < N; R++) // O(N)
        {
            freq_s2[s2[R] - 'a']++;

            if ((R - L + 1) < M)
                continue;

            if (memcmp(freq_s1, freq_s2, sizeof(freq_s1)) == 0) // O(128)
                return true;

            freq_s2[s2[L] - 'a']--;
            L++;
        }

        return false;
    }
};
