/*
    ============
    === HARD ===
    ============

    =======================================
    3333) Find the Original Typed String II
    =======================================

    ============
    Description:
    ============

    Alice is attempting to type a specific string on her computer. However, she
    tends to be clumsy and may press a key for too long, resulting in a
    character being typed multiple times.

    You are given a string word, which represents the final output displayed on
    Alice's screen. You are also given a positive integer k.

    Return the total number of possible original strings that Alice might have
    intended to type, if she was trying to type a string of size at least k.

    Since the answer may be very large, return it modulo 10^9 + 7.

    ======================================================
    FUNCTION: int possibleStringCount(string word, int k);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "aabbccdd", k = 7
    Output: 5
    Explanation:
    The possible strings are: "aabbccdd", "aabbccd", "aabbcdd", "aabccdd", and
    "abbccdd".

    --- Example 2 ---
    Input: word = "aabbccdd", k = 8
    Output: 1
    Explanation:
    The only possible string is "aabbccdd".

    --- Example 3 ---
    Input: word = "aaabbb", k = 3
    Output: 8


    *** Constraints ***
    1 <= word.length <= 5 * 10^5
    word consists only of lowercase English letters.
    1 <= k <= 2000

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

/* Time  Beats: 51.19% */
/* Space Beats: 16.67% */

/* Time  Complexity: O(N + k^2) */
/* Space Complexity: O(k)       */
class Solution {
private:
    static const int MOD = 1e9 + 7;

public:
    int possibleStringCount(string word, int k)
    {
        const int N = word.size();

        int curr_chr_length = 1;
        vector<int> consecutive_character_frequencies;

        for (int index = 1; index < N; index++)
        {
            if (word[index] == word[index - 1])
            {
                curr_chr_length++;
            }
            else
            {
                consecutive_character_frequencies.push_back(curr_chr_length);
                curr_chr_length = 1;
            }
        }
        consecutive_character_frequencies.push_back(curr_chr_length);

        int total_possible_combinations = 1;
        for (const int& group_length : consecutive_character_frequencies)
        {
            total_possible_combinations = static_cast<long long>(total_possible_combinations) * group_length % MOD;
        }

        if (consecutive_character_frequencies.size() >= k)
        {
            return total_possible_combinations;
        }

        vector<int> prefix_sum_dp(k, 1);
        vector<int> dp(k);
        dp[0] = 1;

        for (int group_idx = 0; group_idx < consecutive_character_frequencies.size(); group_idx++)
        {
            vector<int> new_dp(k);

            for (int position = 1; position < k; position++)
            {
                new_dp[position] = prefix_sum_dp[position - 1];

                if (position - consecutive_character_frequencies[group_idx] - 1 >= 0)
                {
                    new_dp[position] = (new_dp[position] - prefix_sum_dp[position - consecutive_character_frequencies[group_idx] - 1] + MOD) % MOD;
                }
            }

            vector<int> new_prefix_sum_dp(k);
            new_prefix_sum_dp[0] = new_dp[0];
            for (int position = 1; position < k; position++)
            {
                new_prefix_sum_dp[position] = (new_prefix_sum_dp[position - 1] + new_dp[position]) % MOD;
            }

            dp = std::move(new_dp);
            prefix_sum_dp = std::move(new_prefix_sum_dp);
        }

        return (total_possible_combinations - prefix_sum_dp[k - 1] + MOD) % MOD;
    }
};
