#include <iostream>
#include <vector>
#include <functional>

/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    2466) Count Ways to Build Good Strings
    ======================================

    ============
    Description:
    ============

    Given the integers zero, one, low, and high, we can construct a string by
    starting with an empty string, and then at each step perform either of the
    following:

        Append the character '0' zero times.
        Append the character '1' one times.

    This can be performed any number of times.

    A good string is a string constructed by the above process having a length
    between low and high (inclusive).

    Return the number of different good strings that can be constructed
    satisfying these properties. Since the answer can be large, return it
    modulo 109 + 7.

    =====================================================================
    FUNCTION: int countGoodStrings(int low, int high, int zero, int one);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: low = 3, high = 3, zero = 1, one = 1
    Output: 8
    Explanation:
    One possible valid good string is "011".
    It can be constructed as follows: "" -> "0" -> "01" -> "011".
    All binary strings from "000" to "111" are good strings in this example.


    --- Example 2 ---
    Input: low = 2, high = 3, zero = 1, one = 2
    Output: 5
    Explanation: The good strings are "00", "11", "000", "110", and "011".


    *** Constraints ***
    1 <= low <= high <= 10^5
    1 <= zero, one <= low

*/

/*
    ------------
    --- IDEA ---
    ------------

    Key observation here is: YOU DO NOT HAVE TO BUILD THE STRINGS!!!

    Then it become an easy, classical, "decision tree" to memoization Solution.

*/

/* Time  Beats: 27.59% */
/* Space Beats:  7.04% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Memoization {
public:
    long long countGoodStrings(int low, int high, int zero, int one)
    {
        long long mod = 1e9 + 7;
        std::vector<long long> memo(high + 1, -1);

        std::function<long long(int)> dfs;
        dfs = [&](int length) -> long long
        {
            if (length > high)
                return 0;

            if (memo[length] != -1)
                return memo[length];

            memo[length] = length >= low ? 1 : 0;
            memo[length] += dfs(length + zero) + dfs(length + one);

            return memo[length] % mod;
        };

        return dfs(0);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 87.04% */
/* Space Beats: 52.04% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Tabulation {
public:
    long long countGoodStrings(int low, int high, int zero, int one)
    {
        long long mod = 1e9 + 7;

        std::vector<long long> dp(high + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= high; i++)
        {
            int left  = (i - zero >= 0) ? dp[i - zero] : 0;
            int right = (i - one  >= 0) ? dp[i - one]  : 0;

            dp[i] = (left + right) % mod;
        }

        long long result = 0;
        for (int i = low; i <= high; i++)
            result += dp[i];

        return result % mod;
    }
};
