/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    4104) Count Valid Substrings II
    ===============================

    ============
    Description:
    ============

    You are given a string s consisting only of the characters 'a', 'b', and
    'c'.

    A string is called valid if it does not contain "abc" as a subsequence.

    Return the number of valid substrings in s. Substrings with different
    starting or ending indices are counted separately.

    ===================================================
    FUNCTION: long long countValidSubstrings(string s);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abac"
    Output: 9
    Explanation:
    The following substrings don't contain "abc" as a subsequence:
        s[0..0] = "a"
        s[0..1] = "ab"
        s[0..2] = "aba"
        s[1..1] = "b"
        s[1..2] = "ba"
        s[1..3] = "bac"
        s[2..2] = "a"
        s[2..3] = "ac"
        s[3..3] = "c"
    Thus, the answer is 9.


    --- Example 2 ---
    Input: s = "abc"
    Output: 5
    Explanation:
    The following substrings don't contain "abc" as a subsequence:
        s[0..0] = "a"
        s[0..1] = "ab"
        s[1..1] = "b"
        s[1..2] = "bc"
        s[2..2] = "c"
    Thus, the answer is 5.


    --- Example 3 ---
    Input: s = "ac"
    Output: 3
    Explanation:
    All substrings in s don't contain "abc" as a subsequence. Thus, the answer
    is 3.


    *** Constraints ***
    1 <= s.length <= 10^5
    s only consists of 'a', 'b', and 'c' characters.

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

/* Time  Beats: 13.42% */
/* Space Beats:  9.56% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long countValidSubstrings(string s)
    {
        const int N = s.length();

        vector<int> next_a_from(N+1, N);
        vector<int> next_b_from(N+1, N);
        vector<int> next_c_from(N+1, N);

        /* Build Next Occurrence Arrays */
        for (int i = N-1; i >= 0; i--)
        {
            next_a_from[i] = (s[i] == 'a') ? i : next_a_from[i+1];
            next_b_from[i] = (s[i] == 'b') ? i : next_b_from[i+1];
            next_c_from[i] = (s[i] == 'c') ? i : next_c_from[i+1];
        }

        long long total_substrings   = 1LL * N * (N + 1) / 2;
        long long invalid_substrings = 0LL;

        /* Count Invalid Substrings */
        for (int start_idx = 0; start_idx < N; start_idx++)
        {
            int idx_a = next_a_from[start_idx];
            if (idx_a == N)
                continue;

            int idx_b = next_b_from[idx_a + 1];
            if (idx_b == N)
                continue;

            int idx_c = next_c_from[idx_b + 1];
            if (idx_c == N)
                continue;

            invalid_substrings += N - idx_c;
        }

        return total_substrings - invalid_substrings;
    }
};
