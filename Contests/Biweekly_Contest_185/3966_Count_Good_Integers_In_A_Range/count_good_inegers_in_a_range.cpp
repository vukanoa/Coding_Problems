/*
    ============
    === HARD ===
    ============

    ====================================
    3966) Count Good Integers in a Range
    ====================================

    ============
    Description:
    ============

    You are given three integers l, r and k.

    A number is considered good if the absolute difference between every pair
    of adjacent digits is at most k.

    Return the number of good integers in the range [l, r] (inclusive).

    The absolute difference between values x and y is defined as abs(x - y).

    ==================================================================
    FUNCTION: long long goodIntegers(long long l, long long r, int k);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: l = 10, r = 15, k = 1
    Output: 3
    Explanation:
        The good integers in the range are 10, 11, and 12.
        For 10, abs(1 - 0) = 1.
        For 11, abs(1 - 1) = 0.
        For 12, abs(1 - 2) = 1.
        All these differences are at most k = 1. Thus, the answer is 3.

    --- Example 2 ---
    Input: l = 201, r = 204, k = 2
    Output: 2
    Explanation:
        The good integers in the range are 201 and 202.
        For 201, abs(2 - 0) = 2 and abs(0 - 1) = 1.
        For 202, abs(2 - 0) = 2 and abs(0 - 2) = 2.
        Thus, the answer is 2.


    *** Constraints ***
    10 <= l <= r <= 10^15
    0 <= k <= 9

*/

#include <cstring>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Pretty standard DigitDP problem.

*/

/* Time  Beats: 97.70% */
/* Space Beats: 93.39% */

// 16 --> because there are at most 16 digits in 10^15. N=10^15 --> log(N)=16
//  2 --> because it's EITHER tight   or NOT tight.
//  2 --> because it's EITHER started or NOT started.
// 11 --> because there are exactly 10 digits, which is always a CONSTANT!
//        However we have 11 as the dimension because we need to represent a
//        NEGATIVE ONE(-1) as well.
//        Therefore:
//            -1 is at index 0,
//             0 is at index 1,
//             1 is at index 2,
//             ...
//             9 is at index 10

/* Time  Complexity: O(16 * 2 * 2 * 11) --> O(logN * 1) --> O(logN) */
/* Space Complexity: O(16 * 2 * 2 * 11) --> O(logN * 1) --> O(logN) */
class Solution {
private:
    long long memo[16][2][2][11];

public:
    long long goodIntegers(long long l, long long r, int k)
    {
        return count_good_integers(r  , k) -
               count_good_integers(l-1, k);
    }

private:
    long long count_good_integers(long long num, int k)
    {
        string str_num = to_string(num);

        /* Memset */
        memset(memo, -1, sizeof(memo));

        return solve(str_num, 0, true, false, -1, k);
    }

    long long solve(string& str_num, int idx, int tight, int started, int prev_digit, int k)
    {
        const int N = str_num.size();

        if (idx == N)
            return started ? 1 : 0;

        if (memo[idx][tight][started][prev_digit + 1] != -1)
            return memo[idx][tight][started][prev_digit + 1];

        int limit_digit = tight ? str_num[idx] - '0' : 9;

        long long result = 0;

        for (int curr_digit = 0; curr_digit <= limit_digit; curr_digit++)
        {
            int new_tight = tight && (curr_digit == limit_digit);

            if ( ! started && curr_digit == 0)
            {
                result += solve(str_num, idx + 1, new_tight, false, -1, k);
            }
            else
            {
                if (started && abs(curr_digit - prev_digit) > k)
                    continue;

                result += solve(str_num, idx + 1, new_tight, true, curr_digit, k);
            }
        }

        return memo[idx][tight][started][prev_digit + 1] = result;
    }
};
