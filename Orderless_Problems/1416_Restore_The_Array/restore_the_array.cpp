/*
    ============
    === HARD ===
    ============

    ===========================
    1416) Restore the Array
    ===========================

    ============
    Description:
    ============

    A program was supposed to print an array of integers. The program forgot to
    print whitespaces and the array is printed as a string of digits s and all
    we know is that all integers in the array were in the range [1, k] and
    there are no leading zeros in the array.

    Given the string s and the integer k, return the number of the possible
    arrays that can be printed as s using the mentioned program. Since the
    answer may be very large, return it modulo 109 + 7

    ==============================================
    FUNCTION: int numberOfArrays(string s, int k);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "1000", k = 10000
    Output: 1
    Explanation: The only possible array is [1000]

    --- Example 2 ---
    Input: s = "1000", k = 10
    Output: 0
    Explanation: There cannot be an array that was printed this way and has all
                 integer >= 1 and <= 10.

    --- Example 3 ---
    Input: s = "1317", k = 2000
    Output: 8
    Explanation: Possible arrays are
    [1317],[131,7],[13,17],[1,317],[13,1,7],[1,31,7],[1,3,17],[1,3,1,7]

    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of only digits and does not contain leading zeros.
    1 <= k <= 10^9

*/

#include <cstring>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 51.84% */
/* Space Beats: 67.37% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    static const int MOD = 1e9 + 7;
    int memo[100001]; // constraints allow up to 1e5 length

public:
    int numberOfArrays(string s, int k)
    {
        memset(memo, -1, sizeof(memo));
        return solve(s, k, 0);
    }

private:
    int solve(string& s, long k, int index)
    {
        const int N = s.size();

        if (index == N)
            return 1;

        if (s[index] == '0')
            return 0;

        if (memo[index] != -1)
            return memo[index];

        long value = 0;
        long ways  = 0;

        for (int end = index; end < N; end++)
        {
            value = value * 10 + (s[end] - '0');

            if (value > k)
                break;

            ways = (ways + solve(s, k, end + 1)) % MOD;
        }

        return memo[index] = ways;
    }
};
