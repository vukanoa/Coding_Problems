/*
    ============
    === HARD ===
    ============

    =====================================================
    3579) Minimum Steps to Convert String with Operations
    =====================================================

    ============
    Description:
    ============

    You are given two strings, word1 and word2, of equal length. You need to
    transform word1 into word2.

    For this, divide word1 into one or more contiguous

    . For each substring substr you can perform the following operations:

        + Replace: Replace the character at any one index of substr with
                   another lowercase English letter.

        + Swap: Swap any two characters in substr.

        + Reverse Substring: Reverse substr.

    Each of these counts as one operation and each character of each substring
    can be used in each type of operation at most once (i.e. no single index
    may be involved in more than one replace, one swap, or one reverse).

    Return the minimum number of operations required to transform word1 into
    word2.

    ========================================================
    FUNCTION: int minOperations(string word1, string word2);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word1 = "abcdf", word2 = "dacbe"
    Output: 4
    Explanation:
    Divide word1 into "ab", "c", and "df". The operations are:
        For the substring "ab",
            Perform operation of type 3 on "ab" -> "ba".
            Perform operation of type 1 on "ba" -> "da".
        For the substring "c" do no operations.
        For the substring "df",
            Perform operation of type 1 on "df" -> "bf".
            Perform operation of type 1 on "bf" -> "be".


    --- Example 2 ---
    Input: word1 = "abceded", word2 = "baecfef"
    Output: 4
    Explanation:
    Divide word1 into "ab", "ce", and "ded". The operations are:
        For the substring "ab",
            Perform operation of type 2 on "ab" -> "ba".
        For the substring "ce",
            Perform operation of type 2 on "ce" -> "ec".
        For the substring "ded",
            Perform operation of type 1 on "ded" -> "fed".
            Perform operation of type 1 on "fed" -> "fef".


    --- Example 3 ---
    Input: word1 = "abcdef", word2 = "fedabc"
    Output: 2
    Explanation:
    Divide word1 into "abcdef". The operations are:
        For the substring "abcdef",
            Perform operation of type 3 on "abcdef" -> "fedcba".
            Perform operation of type 2 on "fedcba" -> "fedabc".


    *** Constraints ***
    1 <= word1.length == word2.length <= 100
    word1 and word2 consist only of lowercase English letters.

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

/* Time  Beats: 5.12% */
/* Space Beats: 5.12% */

/* Time  Complexity: O(N^2 * 26^2)  --->  O(N^2)  */
/* Space Complexity: O(N^2)                       */
class Solution_Memoization {
private:
    vector<vector<int>> memo;

public:
    int minOperations(string word1, string word2)
    {
        const int N = word1.size();
        memo.assign(N, vector<int>(N, -1));

        return solve(0, 0, word1, word2, N);
    }

private:
    int solve (int i, int j, const string &arr1, const string &arr2, const int& N)
    {
        if (i >= N)
            return 0;

        if (j >= N)
            return 1e5;

        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }

        int dont_start_substr = solve(i, j + 1, arr1, arr2, N);

        int reversed     = compute_operations(i, j, arr1, arr2, false);
        int not_reversed = compute_operations(i, j, arr1, arr2, true);
        int start_substr = min(reversed, not_reversed) + solve(j + 1, j + 1, arr1, arr2, N);

        return memo[i][j] = min(start_substr, dont_start_substr);
    }

    int compute_operations(int i, int j, const string &arr1, const string &arr2, bool is_reversed)
    {
        int operations = is_reversed ? 1 : 0;
        int copy_i = i;

        int idx = is_reversed ? j : i;
        int mul = is_reversed ? -1 : 1;

        int N = arr1.size();

        vector<vector<int>> freq_of_mismatched(26, vector<int>(26, 0));

        for (int k = i; k <= j; k++)
        {
            if (arr1[copy_i] != arr2[idx])
            {
                char wanted = arr1[copy_i];
                char got    = arr2[idx];

                if (freq_of_mismatched[got - 'a'][wanted - 'a'] > 0)
                {
                    freq_of_mismatched[got - 'a'][wanted - 'a']--;
                }
                else
                {
                    freq_of_mismatched[wanted - 'a'][got - 'a']++;
                    operations++;
                }
            }

            copy_i++;
            idx += mul;
        }

        return operations;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 95.35% */
/* Space Beats: 83.81% */

/* Time  Complexity: O(N^2 * 26^2)  --->  O(N^2)  */
/* Space Complexity: O(N^2)                       */
class Solution_Tabulation {
private:
    static const int MAXN = 1005;
    static const int INF  = 1000000000;
    int dp[MAXN][MAXN];

public:
    int minOperations(const string& word1, const string& word2)
    {
        const int N = word1.size();

        // const char* s1 = word1.c_str();
        // const char* s2 = word2.c_str();

        for (int i = 0; i <= N; ++i)
        {
            for (int j = 0; j <= N; ++j)
                dp[i][j] = INF;
        }
        dp[0][0] = 0;

        for (int i = 0; i < N; ++i)
        {
            int base = dp[i][i];

            if (base < INF)
            {
                for (int j = i; j < N; ++j)
                {
                    int cost_normal  = mininumOpr(word1, word2, i, j, false);
                    int cost_reverse = mininumOpr(word1, word2, i, j, true) + 1;

                    int total_min = cost_normal < cost_reverse ? cost_normal : cost_reverse;
                    int candidate = base + total_min;

                    if (candidate < dp[j+1][j+1])
                        dp[j+1][j+1] = candidate;
                }
            }

            for (int k = i + 1; k <= N; k++)
            {
                if (dp[i][k-1] < dp[i][k])
                    dp[i][k] = dp[i][k-1];
            }
        }

        return dp[N][N];
    }

private:
    static inline int mininumOpr(const string& word1, const string& word2, int i, int j, bool rev)
    {
        int operations = 0;

        int idx_1 = i;
        int idx_2 = rev ? j : i;

        int step = rev ? -1 : 1;
        int freq[26][26] = {};

        for (int k = i; k <= j; ++k, ++idx_1, idx_2 += step)
        {
            char chr_1 = word1[idx_1];
            char chr_2 = word2[idx_2];

            if (chr_1 != chr_2)
            {
                int want = chr_1 - 'a';
                int got  = chr_2 - 'a';

                if (freq[got][want] > 0)
                {
                    freq[got][want]--;
                }
                else
                {
                    freq[want][got]++;
                    operations++;
                }
            }
        }

        return operations;
    }
};
