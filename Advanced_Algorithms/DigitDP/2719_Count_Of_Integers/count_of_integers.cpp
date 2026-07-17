/*
    ============
    === HARD ===
    ============

    ===========================
    2719) Count of INtegers
    ===========================

    ============
    Description:
    ============

    You are given two numeric strings num1 and num2 and two integers max_sum
    and min_sum. We denote an integer x to be good if:

        num1 <= x <= num2
        min_sum <= digit_sum(x) <= max_sum.

    Return the number of good integers. Since the answer may be large, return
    it modulo 10^9 + 7.

    =====
    Note: that digit_sum(x) denotes the sum of the digits of x. 
    =====

    ========================================================================
    FUNCTION: int count(string num1, string num2, int min_sum, int max_sum);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num1 = "1", num2 = "12", min_sum = 1, max_sum = 8
    Output: 11
    Explanation: There are 11 integers whose sum of digits lies between 1 and 8
                 are 1,2,3,4,5,6,7,8,10,11, and 12. Thus, we return 11.

    --- Example 2 ---
    Input: num1 = "1", num2 = "5", min_sum = 1, max_sum = 5
    Output: 5
    Explanation: The 5 integers whose sum of digits lies between 1 and 5 are
                 1,2,3,4, and 5. Thus, we return 5.


    *** Constraints ***
    1 <= num1 <= num2 <= 10^22
    1 <= min_sum <= max_sum <= 400

*/

#include <cstring>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Almost a pretty standard DigitDP, however the MOD part can screw you. Be
    careful with it.

*/

/* Time  Beats: 13.16% */
/* Space Beats: 34.30% */

/* Time  Complexity: O(D * 2 * 11 * S * 10) */ // S --> max_digit_sum
/* Space Complexity: O(D * 2 * 11 * S)      */ // D --> max digits
class Solution_Top_Down__Memoization {
private:
    const int MOD = 1e9 + 7;

    //  23 --> Constraint 10^22 needs 23 digits to be represented
    //   2 --> Either TIGHT or not
    //  11 --> All 10 digits plus "-1" to check whether we've started
    //         -1 at index 0
    //          0 at index 1
    //          1 at index 2
    //          2 at index 3
    //          3 at index 4
    //  ...
    // 208 --> Sum of 9s at each of 23 digit places, i.e. 23 * 9 = 207
    long long memo[23][2][11][401];

public:
    int count(string num1, string num2, int min_sum, int max_sum)
    {
        return (count_integers(num2,               min_sum, max_sum) -
                count_integers(subtract_one(num1), min_sum, max_sum) + MOD) % MOD; // Do NOT forget this part with MOD-ing!!!
    }

private:
    string subtract_one(string number)
    {
        const int N = number.size();
        int idx = N - 1;

        while (idx >= 0 && number[idx] == '0')
        {
            number[idx] = '9';
            idx--;
        }

        if (idx >= 0)
            number[idx]--;

        // Remove leading zeros
        if (number[0] == '0')
            number.erase(0, number.find_first_not_of('0'));

        return number.empty() ? "0" : number;
    }

    int count_integers(string str_num, int min_sum, int max_sum)
    {
        /* Memset */
        memset(memo, 0xff, sizeof(memo)); // 0xff is -1 in 2's complement

        return solve(str_num, 0, true, -1, 0, min_sum, max_sum);
    }

    long long solve(string& str_num, int idx, int tight, int prev_digit, int curr_sum, int min_sum, int max_sum)
    {
        const int N = str_num.size();

        if (idx == N)
            return ((prev_digit != -1) && (min_sum <= curr_sum && curr_sum <= max_sum)) ? 1 : 0;

        if (memo[idx][tight][prev_digit + 1][curr_sum] != -1)
            return memo[idx][tight][prev_digit + 1][curr_sum];

        int limit_digit = tight ? str_num[idx] - '0' : 9;

        long long result = 0LL;
        for (int curr_digit = 0; curr_digit <= limit_digit; curr_digit++)
        {
            int new_tight = tight && (curr_digit == limit_digit);

            if (curr_sum == 0 && curr_digit == 0)
            {
                result = (result + solve(str_num, idx + 1, new_tight, -1, 0, min_sum, max_sum)) % MOD;
            }
            else
            {
                if (curr_sum + curr_digit > max_sum)
                    break;

                result = (result + solve(str_num, idx + 1, new_tight, curr_digit, curr_sum + curr_digit, min_sum, max_sum)) % MOD;
            }
        }

        return memo[idx][tight][prev_digit + 1][curr_sum] = result % MOD;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same Idea, implemented using BOttom-Up Tabulation technqieu.

*/

/* Time  Beats: 27.81% */
/* Space Beats: 54.30% */

/* Time  Complexity: O(D * 2 * 2 * S * 10) */ // S --> max_digit_sum
/* Space Complexity: O(D * 2 * 2 * S)      */ // D --> max digits
class Solution_Bottom_Up__Tabulation {
private:
    const int MOD = 1e9 + 7;

    //  24 --> Constraint 10^22 needs 23 digits to be represented
    //   2 --> Either TIGHT   or not
    //   2 --> Either STARTED or not
    // 401 --> Because max_sum is up to 400
    long long dp[24][2][2][401];

public:
    int count(string num1, string num2, int min_sum, int max_sum)
    {
        return (count_integers(num2,               min_sum, max_sum) -
                count_integers(subtract_one(num1), min_sum, max_sum) + MOD) % MOD;
    }

private:
    string subtract_one(string number)
    {
        const int N = number.size();
        int idx = N - 1;

        while (idx >= 0 && number[idx] == '0')
        {
            number[idx] = '9';
            idx--;
        }

        if (idx >= 0)
            number[idx]--;

        if (number[0] == '0')
            number.erase(0, number.find_first_not_of('0'));

        return number.empty() ? "0" : number;
    }

    int count_integers(string str_num, int min_sum, int max_sum)
    {
        const int N = str_num.size();

        /* Memset */
        memset(dp, 0, sizeof(dp));

        // Initially:
        // No digits processed
        // Tight = true
        // Started = false
        // Sum = 0
        dp[0][1][0][0] = 1;

        for (int idx = 0; idx < N; idx++)
        {
            int curr_limit_digit = str_num[idx] - '0';

            for (int tight = 0; tight <= 1; tight++)
            {
                for (int started = 0; started <= 1; started++)
                {
                    for (int curr_sum = 0; curr_sum <= max_sum; curr_sum++)
                    {
                        long long curr_count = dp[idx][tight][started][curr_sum];

                        if (curr_count == 0)
                            continue;

                        int limit_digit = tight ? curr_limit_digit : 9;

                        for (int curr_digit = 0; curr_digit <= limit_digit; curr_digit++)
                        {
                            int new_tight = tight && (curr_digit == curr_limit_digit);

                            if ( ! started && curr_digit == 0)
                            {
                                dp[idx + 1][new_tight][0][curr_sum] = (dp[idx + 1][new_tight][0][curr_sum] + curr_count) % MOD;
                            }
                            else
                            {
                                if (curr_sum + curr_digit > max_sum)
                                    break;

                                dp[idx + 1][new_tight][1][curr_sum + curr_digit] = (dp[idx + 1][new_tight][1][curr_sum + curr_digit] + curr_count) % MOD;
                            }
                        }
                    }
                }
            }
        }

        long long result = 0LL;
        for (int tight = 0; tight <= 1; tight++)
        {
            for (int curr_sum = min_sum; curr_sum <= max_sum; curr_sum++)
                result = (result + dp[N][tight][1][curr_sum]) % MOD;
        }

        return result;
    }
};
