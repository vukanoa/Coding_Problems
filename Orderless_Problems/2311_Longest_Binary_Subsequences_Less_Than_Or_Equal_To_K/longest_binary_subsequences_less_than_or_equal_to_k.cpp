/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    2311) Longest Binary Subsequnces Less Than or Equal to K
    ========================================================

    ============
    Description:
    ============

    You are given a binary string s and a positive integer k.

    Return the length of the longest subsequence of s that makes up a binary
    number less than or equal to k.

    =====
    Note: The subsequence can contain leading zeroes.
          The empty string is considered to be equal to 0.
          A subsequence is a string that can be derived from another string by
          deleting some or no characters without changing the order of the
          remaining characters.
    =====

    ==================================================
    FUNCTION: int longestSubsequence(string s, int k);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "1001010", k = 5
    Output: 5
    Explanation: The longest subsequence of s that makes up a binary number
                 less than or equal to 5 is "00010", as this number is equal to
                 2 in decimal. Note that "00100" and "00101" are also possible,
                 which are equal to 4 and 5 in decimal, respectively. The
                 length of this subsequence is 5, so 5 is returned.


    --- Example 2 ---
    Input: s = "00101001", k = 1
    Output: 6
    Explanation: "000001" is the longest subsequence of s that makes up a
                 binary number less than or equal to 1, as this number is equal
                 to 1 in decimal. The length of this subsequence is 6, so 6 is
                 returned.


    *** Constraints ***
    1 <= s.length <= 1000
    s[i] is either '0' or '1'.
    1 <= k <= 10^9

*/

#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    It looks like a Memoization problem(and it can be! Check out the 2nd
    Solution down below), but it's actually much more simple.
    The key is to realize that we MUST take all zeroes. We're not "allowed" to
    skip it.

    Once we realize that, we take as many 1s from the right as we can, before
    exceeding k.

    It can be shown that greedily using 1s from the right is always better than
    to skip it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  74.82% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int longestSubsequence(string s, int k)
    {
        const int N = s.length();

        int ones = 0;

        int val = 0;
        int pow = 1;

        for (int i = N-1; i >= 0 && val + pow <= k; i--)
        {
            if (s[i] == '1')
            {
                ones++;
                val += pow;
            }

            pow <<= 1;
        }

        return count(s.begin(), s.end(), '0') + ones;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is indeed less Space-efficient, however, this is a much more
    natural way given the Constraints.

    It's a classic take-skip Memoization problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  18.71% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Memoization {
private:
    int memo[1001];

public:
    int longestSubsequence(string s, int k)
    {
        int N = s.length();

        /* Allocating Memory on the Stack */
        memset(memo, -1, sizeof(memo));

        return solve(s, N-1, 0, 0LL, k);
    }

private:
    int solve(string &s, int idx, int power, long long value, int &k)
    {
        if (idx < 0)
            return 0;

        if (memo[idx] != -1)
            return memo[idx];

        int take = 0;
        if (s[idx] == '1')
        {
            // If we can take the 1 and not exceed k and not Overflow
            if (power < 63 && value + (1LL << power) <= k)
                take = 1 + solve(s, idx-1, power+1, value + (1LL << power), k);
        }
        else // We CAN always and SHOULD always take 0
        {
            take = 1 + solve(s, idx-1, power+1, value, k);
        }

        int skip = solve(s, idx-1, power, value, k);

        return memo[idx] = max(take, skip);
    }
};
