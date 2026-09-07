/*
    ============
    === HARD ===
    ============

    =============================
    940) Distinct Subsequences II
    =============================

    ============
    Description:
    ============

    Given a string s, return the number of distinct non-empty subsequences of
    s.

    Since the answer may be very large, return it modulo 10^9 + 7. A
    subsequence of a string is a new string that is formed from the original
    string by deleting some (can be none) of the characters without disturbing
    the relative positions of the remaining characters. (i.e., "ace" is a
    subsequence of "abcde" while "aec" is not. 

    ========================================
    FUNCTION int distinctSubseqII(string s);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abc"
    Output: 7
    Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac",
                 "bc", and "abc".

    --- Example 2 ---
    Input: s = "aba"
    Output: 6
    Explanation: The 6 distinct subsequences are "a", "b", "ab", "aa", "ba",
                 and "aba".

    --- Example 3 ---
    Input: s = "aaa"
    Output: 3
    Explanation: The 3 distinct subsequences are "a", "aa" and "aaa".


    *** Constraints ***
    1 <= s.length <= 2000
    s consists of lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  5.15% */
/* Space Beats: 55.30% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int distinctSubseqII(string s)
    {
        const int N   = s.size();
        const int MOD = 1e9 + 7;
        int result = 0;

        vector<int> dp(N, 1);

        for (int i = 0; i < N; i++)
        {
            // Try extending subsequences ending BEFORE i
            for (int j = 0; j < i; j++)
            {
                if (s[i] != s[j])
                    dp[i] = (dp[i] + dp[j]) % MOD;
            }

            result = (result + dp[i]) % MOD;
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

/* Time  Beats: 100.00% */
/* Space Beats:  43.73% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Linear_using_Character_Groups {
public:
    int distinctSubseqII(string s)
    {
        const int N   = s.size();
        const int MOD = 1e9 + 7;

        vector<int> dp(N, 1);
        vector<int> freq_ending_with(26, 0);

        int sum = 0;

        for (int i = 0; i < N; i++)
        {
            // New = single_chr + ALL_old_subsequences - duplicates_ending_with_s[i]
            dp[i] = (1 + sum - freq_ending_with[s[i]- 'a'] + MOD) % MOD;

            sum = (sum + dp[i]) % MOD;

            // Add all new subsequences ending with s[i]
            freq_ending_with[s[i] - 'a'] = (freq_ending_with[s[i] - 'a'] + dp[i]) % MOD;
        }

        return sum;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  90.96% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Optimized_Space {
public:
    int distinctSubseqII(string s)
    {
        const int N   = s.size();
        const int MOD = 1e9 + 7;

        vector<int> freq_ending_with(26, 0);

        int sum = 0;

        for (int i = 0; i < N; i++)
        {
            // New_subsequences - duplicate_subsequences
            int curr_net_subsequences = (1 + sum - freq_ending_with[s[i] - 'a'] + MOD) % MOD;

            sum = (sum + curr_net_subsequences) % MOD;

            // Update subsequences ending with this character
            freq_ending_with[s[i] - 'a'] = (freq_ending_with[s[i] - 'a'] + curr_net_subsequences) % MOD;
        }

        return sum;
    }
};
