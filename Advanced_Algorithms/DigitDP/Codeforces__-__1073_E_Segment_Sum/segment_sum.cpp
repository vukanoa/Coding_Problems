/*
    ===================================
    === Difficulty: Codeforces 2300 ===
    ===================================

    ===========================
    1073 E)  Segment Sum
    ===========================

    ============
    Description:
    ============

    You are given two integers l and r (l <= r). Your task is to calculate the
    sum of numbers from l to r (including l and r) such that each number
    contains at most k different digits, and print this sum modulo 998244353.

    For example, if k=1 then you have to calculate all numbers from l to r such
    that each number is formed using only one digit. For l=10,r=50 the answer
    is:
        11 + 22 + 33 + 44 = 110.


    =============
    === Input ===
    =============
        The only line of the input contains three integers l, r and k

        (1 <= l <= r < 10^18, 1 <= k <= 10) --> the borders of the segment and
        the maximum number of different digits.


    ==============
    === Output ===
    ==============
        Print one integer --> the sum of numbers from l to r such that each
        number contains at most k different digits, modulo 998244353.


    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    10 50 2

    Output
    1230


    --- Example 2 ---
    Input
    1 2345 10

    Output
    2750685


    --- Example 3 ---
    Input
    101 154 2

    Output
    2189


    *** Constraints ***
    Time limit per test:     1 second
    Memory limit per test: 256 megabytes


    ============
    === Note ===
    ============
    For the first example the answer is just the sum of numbers from l to r
    which equals to 50⋅512−9⋅102=1230. This example also explained in the
    problem statement but for k=1.

    For the second example the answer is just the sum of numbers from l to r
    which equals to 2345⋅23462=2750685.

    For the third example the answer is
    101 + 110 + 111 + 112 + 113 + 114 + 115 + 116 + 117 + 118 + 119 + 121 + 122
    + 131 + 133 + 141 + 144 + 151 = 2189.

*/

#include <cstring>
#include <iostream>
#include <string>
using namespace std;




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

// Submission #383453676

/* Verdict: Accepted */
/* Time:    62ms     */
/* Memory:  6800KB   */

/* Time  Complexity: O(19 * 2 * 1024 * 11 * 10) */
/* Space Complexity: O(19 * 2 * 1024 * 11)      */
const long long MOD = 998244353;

struct State
{
    long long count;
    long long sum;
};

State memo[19][2][1024][11];

long long power_of_10[19];

State solve(string& str_num, int idx, int tight, int digit_mask, int remaining_k)
{
    const int N = str_num.size();

    if (idx == N)
    {
        if (digit_mask == 0x0000)
            return {0, 0};

        return {1, 0};
    }

    if (memo[idx][tight][digit_mask][remaining_k].count != -1)
        return memo[idx][tight][digit_mask][remaining_k];

    const int limit_digit = tight ? str_num[idx] - '0' : 9;

    State result = {0, 0};
    for (int curr_digit = 0; curr_digit <= limit_digit; curr_digit++)
    {
        const int next_tight = tight && (curr_digit == limit_digit);

        State child;

        if (digit_mask == 0x0000 && curr_digit == 0)
        {
            child = solve(str_num, idx + 1, next_tight, 0x0000, remaining_k);
        }
        else
        {
            bool already_used = digit_mask & (1 << curr_digit);

            if ( ! already_used && remaining_k == 0)
                continue;

            const int next_mask        = digit_mask | (1 << curr_digit);
            const int next_remaining_k = already_used ? remaining_k : remaining_k - 1;

            child = solve(str_num, idx + 1, next_tight, next_mask, next_remaining_k);
        }

        result.count += child.count;
        result.count %= MOD;

        result.sum += child.sum;
        result.sum %= MOD;

        result.sum += (curr_digit * power_of_10[N-1 - idx] % MOD) * child.count;
        result.sum %= MOD;
    }

    return memo[idx][tight][digit_mask][remaining_k] = result;
}

long long segment_sum(long long number, int k)
{
    if (number <= 0)
        return 0;

    string str_num = to_string(number);

    /* Memset */
    memset(memo, -1, sizeof(memo));

    return solve(str_num, 0, true, 0x0000, k).sum;
}

int main()
{
    power_of_10[0] = 1;

    for (int idx = 1; idx < 19; idx++)
        power_of_10[idx] = (power_of_10[idx - 1] * 10) % MOD;

    long long L;
    long long R;
    int k;

    cin >> L;
    cin >> R;
    cin >> k;

    long long result = segment_sum(R,     k) -
                       segment_sum(L - 1, k);

    result %= MOD;

    if (result < 0)
        result += MOD;

    cout << result;

    return 0;
}
