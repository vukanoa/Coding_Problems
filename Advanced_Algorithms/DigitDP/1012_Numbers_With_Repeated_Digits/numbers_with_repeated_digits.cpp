/*
    ============
    === HARD ===
    ============

    ===============================
    1012) Number of Repeated Digits
    ===============================

    ============
    Description:
    ============

    Given an integer n, return the number of positive integers in the range
    [1, n] that have at least one repeated digit.

    =========================================
    FUNCTION: int numDupDigitsAtMostN(int n);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 20
    Output: 1
    Explanation: The only positive number (<= 20) with at least 1 repeated
                 digit is 11.

    --- Example 2 ---
    Input: n = 100
    Output: 10
    Explanation: The positive numbers (<= 100) with atleast 1 repeated digit
                 are 11, 22, 33, 44, 55, 66, 77, 88, 99, and 100.

    --- Example 3 ---
    Input: n = 1000
    Output: 262


    *** Constraints ***
    1 <= n <= 10^9

*/

#include <cstring>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    DigitDP that uses bitmask as a part of the state. Not very difficult if
    you're already familiar with both Memoization and DigitDP problems in
    general.

    Also, it goes without saying that you have to be comfortable with "Bit
    Manipulation", but since that is NOT very difficult, it's usually assumed
    in more advanced techniques like DigitDP.

*/

/* Time  Beats: 91.83% */
/* Space Beats: 48.40% */

/* Time Complexity:  O(logN * 2 * 1024 * 2 * 10) --> O(logN) */
/* Space Complexity: O(logN * 2 * 1024 * 2)      --> O(logN) */
class Solution {
private:
    //   10 --> Because 10^9 needs 10 digits to be represented
    //    2 --> Because it's    either TIGHT   or not
    //    2 --> Because we have either STARTED or not
    // 1024 --> Because we have 10 digits [0, 9], 1 bit for each -> 2^10 = 1024
    //    2 --> Because either "at least one digit" is already FULFILLED or NOT
    int memo[10][2][2][1024][2];

public:
    int numDupDigitsAtMostN(int n)
    {
        if (n < 11)
            return 0;

        string str_num = to_string(n);

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(str_num, 0, true, false, 0x0000, false);
    }

private:
    int solve(string& str_num, int idx, int tight, int started, int digit_mask, int at_least_one_repeated_digit)
    {
        const int N = str_num.size();

        if (idx == N)
            return started ? (at_least_one_repeated_digit ? 1 : 0) : 0;

        if (memo[idx][tight][started][digit_mask][at_least_one_repeated_digit] != -1)
            return memo[idx][tight][started][digit_mask][at_least_one_repeated_digit];

        int limit_digit = tight ? str_num[idx] - '0' : 9;

        int result = 0;
        for (int curr_digit = 0; curr_digit <= limit_digit; curr_digit++)
        {
            int next_tight  = tight && (curr_digit == limit_digit);
            int repeat_flag = at_least_one_repeated_digit || (digit_mask & (1 << curr_digit));

            if ( ! started && curr_digit == 0)
                result += solve(str_num, idx + 1, next_tight, false, digit_mask                    , false);
            else
                result += solve(str_num, idx + 1, next_tight, true , digit_mask | (1 << curr_digit), repeat_flag);
        }

        return memo[idx][tight][started][digit_mask][at_least_one_repeated_digit] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We can reduce the dimension of the "memo" by removing the "started" state.

    In order to check whether we have started or NOT, in general DP problem we
    utilize "prev_digit" and we're checking if (prev_digit == -1) which
    indicates that we have NOT started yet.

    However, here we do NOT have "prev_digit", instead we're dealing with
    digit_mask.

    We know for a fact that we have NOT yet started only if (digit_mask == 0).

    Therefore, we remove the "started" dimension and therefore the Solution is
    tiny bit more optimized.

*/

/* Time  Beats: 61.10% */
/* Space Beats: 90.50% */

/* Time Complexity:  O(logN * 2 * 1024 * 2 * 10) --> O(logN) */
/* Space Complexity: O(logN * 2 * 1024 * 2)      --> O(logN) */
class Solution_Optimized {
private:
    //   10 --> Because 10^9 needs 10 digits to be represented
    //    2 --> Because it's either TIGHT or not
    // 1024 --> Because we have 10 digits [0, 9], 1 bit for each -> 2^10 = 1024
    //    2 --> Because either "at least one digit" is already FULFILLED or NOT
    int memo[10][2][1024][2];

public:
    int numDupDigitsAtMostN(int n)
    {
        if (n < 11)
            return 0;

        string str_num = to_string(n);

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(str_num, 0, true, 0x0000, false);
    }

private:
    int solve(string& str_num, int idx, int tight, int digit_mask, int at_least_one_repeated_digit)
    {
        const int N = str_num.size();

        if (idx == N)
            return digit_mask != 0x0000 ? (at_least_one_repeated_digit ? 1 : 0) : 0;

        if (memo[idx][tight][digit_mask][at_least_one_repeated_digit] != -1)
            return memo[idx][tight][digit_mask][at_least_one_repeated_digit];

        int limit_digit = tight ? str_num[idx] - '0' : 9;

        int result = 0;
        for (int curr_digit = 0; curr_digit <= limit_digit; curr_digit++)
        {
            int next_tight  = tight && (curr_digit == limit_digit);
            int repeat_flag = at_least_one_repeated_digit || (digit_mask & (1 << curr_digit));

            if (digit_mask == 0x0000 && curr_digit == 0)
                result += solve(str_num, idx + 1, next_tight, digit_mask                    , false);
            else
                result += solve(str_num, idx + 1, next_tight, digit_mask | (1 << curr_digit), repeat_flag);
        }

        return memo[idx][tight][digit_mask][at_least_one_repeated_digit] = result;
    }
};
