/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    3756) Concatenate Non-Zero Digits and Multiply by Sum II
    ========================================================

    ============
    Description:
    ============

    You are given a string s of length m consisting of digits. You are also
    given a 2D integer array queries, where queries[i] = [li, ri].

    For each queries[i], extract the s[li..ri]. Then, perform the following:

        + Form a new integer x by concatenating all the non-zero digits from
          the substring in their original order. If there are no non-zero
          digits, x = 0.

        + Let sum be the sum of digits in x. The answer is x * sum.

    Return an array of integers answer where answer[i] is the answer to the ith
    query.

    Since the answers may be very large, return them modulo 109 + 7.

    =============================================================================
    FUNCTION: vector<int> sumAndMultiply(string s, vector<vector<int>>& queries);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "10203004", queries = [[0,7],[1,3],[4,6]]
    Output: [12340, 4, 9]
    Explanation:
        s[0..7] = "10203004"
            x = 1234
            sum = 1 + 2 + 3 + 4 = 10
            Therefore, answer is 1234 * 10 = 12340.
        s[1..3] = "020"
            x = 2
            sum = 2
            Therefore, the answer is 2 * 2 = 4.
        s[4..6] = "300"
            x = 3
            sum = 3
            Therefore, the answer is 3 * 3 = 9.

    --- Example 2 ---
    Input: s = "1000", queries = [[0,3],[1,1]]
    Output: [1, 0]
    Explanation:
        s[0..3] = "1000"
            x = 1
            sum = 1
            Therefore, the answer is 1 * 1 = 1.
        s[1..1] = "0"
            x = 0
            sum = 0
            Therefore, the answer is 0 * 0 = 0.

    --- Example 3 ---
    Input: s = "9876543210", queries = [[0,9]]
    Output: [444444137]
    Explanation:
        s[0..9] = "9876543210"
            x = 987654321
            sum = 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 = 45
            Therefore, the answer is 987654321 * 45 = 44444444445.
            We return 44444444445 modulo (109 + 7) = 444444137.


    *** Constraints ***
    1 <= m == s.length <= 10^5
    s consists of digits only.
    1 <= queries.length <= 10^5
    queries[i] = [li, ri]
    0 <= li <= ri < m

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

/* Time  Beats: 91.92% */
/* Space Beats: 95.49% */

/* Time  Complexity: O(N + Q) */
/* Space Complexity: O(N)     */
class Solution {
private:
    static constexpr int MOD = 1e9 + 7;
    static constexpr int MAX = 1e5 + 1;

    inline static int pow[MAX];

    inline static int init = []()
    {
        pow[0] = 1;
        for (int i = 1; i < MAX; i++)
            pow[i] = pow[i - 1] * 10LL % MOD;

        return 0;
    }();

public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries)
    {
        const int N = s.length();
        const int Q = queries.size();

        vector<int> prefix_digit_sum(N + 1, 0);
        vector<int> prefix_concatenated_nonzero_digits(N + 1, 0);
        vector<int> len(N + 1, 0);

        for (int i = 0; i < N; i++)
        {
            int digit = s[i] - '0';

            prefix_digit_sum[i + 1] = prefix_digit_sum[i] + digit;

            if (digit)
            {
                prefix_concatenated_nonzero_digits[i + 1] =
                    (prefix_concatenated_nonzero_digits[i] * 10LL + digit) % MOD;
                len[i + 1] = len[i] + 1;
            }
            else
            {
                prefix_concatenated_nonzero_digits[i + 1] =
                    prefix_concatenated_nonzero_digits[i];
                len[i + 1] = len[i];
            }
        }

        vector<int> result;
        result.reserve(Q);

        for (const auto& query : queries)
        {
            const int& l = query[0];
            const int& r = query[1] + 1;

            long long removed_prefix                 = prefix_concatenated_nonzero_digits[l] * 1LL * pow[len[r] - len[l]] % MOD;
            long long concatenated_nonzero_substring = (prefix_concatenated_nonzero_digits[r] - removed_prefix + MOD) % MOD;

            result.push_back(concatenated_nonzero_substring * (prefix_digit_sum[r] - prefix_digit_sum[l]) % MOD);
        }

        return result;
    }
};
