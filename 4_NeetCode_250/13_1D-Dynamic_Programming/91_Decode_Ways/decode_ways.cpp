/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    91) Decode Ways
    ===========================

    ============
    Description:
    ============

    A message containing letters from A-Z can be encoded into numbers using the
    following mapping:

    'A' -> "1"
    'B' -> "2"
    ...
    'Z' -> "26"

    To decode an encoded message, all the digits must be grouped then mapped
    back into letters using the reverse of the mapping above (there may be
    multiple ways). For example, "11106" can be mapped into:

    "AAJF" with the grouping (1 1 10 6)
    "KJF" with the grouping (11 10 6)


    =====
    Note: that the grouping (1 11 06) is invalid because "06" cannot be mapped
          into 'F' since "6" is different from "06".

          Given a string s containing only digits, return the number of ways to
          decode it.

          The test cases are generated so that the answer fits in a 32-bit
          integer.
    =====

    ==========================================
    FUNCTION: int numDecodings(std::string s);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "12"
    Output: 2
    Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).

    --- Example 2 ---
    Input: s = "226"
    Output: 3
    Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6),
    or "BBF" (2 2 6).

    --- Example 3 ---
    Input: s = "06"
    Output: 0
    Explanation: "06" cannot be mapped to "F" because of the leading zero
    ("6" is different from "06").

    *** Constraints ***
    1 <= s.length <= 100
    s contains only digits and may contain leading zero(s).

*/

#include <cstring>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------


    Example 1:

                                "11106"

            ______________________._______________________
            __________1______________________11___________
            ____1__________11___________1__________10_____
            _1____10_____F___________F___________6________
            _____6_______________________________T________
                 T

    We have two "T"s, so the answer is: 2.

    For recursion to stop It's either that:
        1. memo[i] is not 0

           or

        2. s[i] == 0


    if s[i] == 0, that's F. It means that "combination" is not possible, thus
    return 0.

    Essentially: memo[i] = memo[i + 1] + memo[i + 2];

    And we do that recursively.

    At one point, index "i" will get out of bounds if a combination is okay, so
    that's why we have to have: memo(s.length() + 1, 0) and that's why we have to
    assign memo[s.length()] = 1;

    If we have, successfully, gone through all the elements, without returning
    0, that means that "path" is valid and must be included in overall count of
    results.

    So:
        memo[s.length() + 1] = 1

    is necessary.


    Example 2:

                                "12"
                             ___________
                             _____1_____
                             __2____12__
                             T_____T____

    Again, two T's, so the answer is: 2

    Go through the code for this example and you'll get it.
    ODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  79.49% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Top_Down__Memoization {
private:
    int memo[101];

public:
    int numDecodings(string s)
    {
        const int N = s.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(0, s);
    }

private:
    int solve(int idx, string& s)
    {
        const int N = s.size();

        if (idx >= N)
            return 1;

        if (memo[idx] != -1)
            return memo[idx];

        if (s[idx] == '0')
            return memo[idx] = 0;

        if (idx < N-1 && s[idx] >= '3' && s[idx + 1] == '0')
            return memo[idx] = 0; // Cannot decode "30", "40", ..., "90"

        int take_one = solve(idx + 1, s);
        int take_two = 0;

        if (idx < N-1 && (s[idx] == '1' || (s[idx] == '2' && s[idx + 1] <= '6')))
            take_two = solve(idx + 2, s);

        return memo[idx] = take_one + take_two;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.05% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Bottom_Up__Tabulation {
public:
    int numDecodings(string s)
    {
        const int N = s.size();

        vector<int> dp(N+1, 0);
        dp[N] = 1;

        for (int i = N-1; i >= 0; i--)
        {
            /* One digit */
            if (s[i] != '0')
                dp[i] += dp[i + 1];

            /* Two digits */
            if (i + 1 < N && (s[i] == '1' || (s[i] == '2' && s[i+1] <= '6')))
                dp[i] += dp[i + 2];
        }

        return dp[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea, but implemented in O(1) Space because we can see that we don't
    need to use entire array of dp, but only 3 elements.

    Similar to a House Robber problem or the Kadane's Algorithm.

*/
/* Time  Beats: 100.00% */
/* Space Beats:  98.83% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up__Tabulation__Space_Optimized {
public:
    int numDecodings(string s)
    {
        const int N = s.size();

        int next_next = 1;
        int next      = s.back() == '0' ? 0 : 1;

        for (int i = N-2; i >= 0; i--)
        {
            int curr = 0;
            if (s[i] != '0')
            {
                if (s[i] >= '3' && s[i+1] == '0')
                    return 0; // Cannot decode "30", "40", ..., "90"

                if (s[i] == '1' || (s[i] == '2' && s[i+1] <= '6'))
                    curr = next + next_next;
                else
                    curr = next;
            }

            next_next = next;
            next      = curr;
        }

        return next;
    }
};
