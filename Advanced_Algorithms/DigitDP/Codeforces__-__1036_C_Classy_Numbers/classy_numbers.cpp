/*

    ===========================
    1036 C) Classy Numbers
    ===========================

    ============
    Description:
    ============

    Let's call some positive integer classy if its decimal representation
    contains no more than 3 non-zero digits. For example, numbers 4, 200000,
    10203 are classy and numbers 4231, 102306, 7277420000 are not.

    You are given a segment [L;R].
    Count the number of classy integers x such that L <= x <= R.

    Each testcase contains several segments, for each of them you are required
    to solve the problem separately.


    =============
    === Input ===
    =============
        The first line contains a single integer T (1 <= T <= 10^4) --> the
        number of segments in a testcase.

        Each of the next T lines contains two integers Li and Ri
        (1 <= Li <= Ri <= 10^18).

    ==============
    === Output ===
    ==============
        Print T lines --> the i-th line should contain the number of classy
        integers on a segment [Li;Ri].

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    Input:
    4
    1 1000
    1024 1024
    65536 65536
    999999 1000001

    Output:
    1000
    1
    0
    2


    *** Consraints*** 
    Time   limit per test:   3 seconds
    Memory limit per test: 256 megabytes

*/

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

// Submission #383447654

/* Verdict: Accepted */
/* Time:    140ms    */
/* Memory:  0 KB     */

/* Time  Complexity: O(19 * 2 * 1024 * 11 * 10) */
/* Space Complexity: O(19 * 2 * 1024 * 11)      */

// 19 --> Because Upper-Range is 10^18, which consists of 19 digits
//  2 --> Because it's either TIGHT or not
//  4 --> Because we can have up to 3(inclusive) non-zero digits
long long memo[19][2][4];

long long solve(string& str_num, int idx, int tight, int non_zero_count)
{
    const int N = str_num.size();

    if (idx == N)
        return (non_zero_count > 0) ? 1 : 0; // (non_zero_count > 0) -> started

    if (memo[idx][tight][non_zero_count] != -1)
        return memo[idx][tight][non_zero_count];

    int limit_digit = tight ? str_num[idx] - '0' : 9;

    long long result = 0LL;
    for (int curr_digit = 0; curr_digit <= limit_digit; curr_digit++)
    {
        int next_tight = tight && (curr_digit == limit_digit);

        if (non_zero_count == 0 && curr_digit == 0)
        {
            result += solve(str_num, idx + 1, next_tight, 0);
        }
        else
        {
            if (non_zero_count == 3 && curr_digit > 0)
                continue;

            result += solve(str_num, idx + 1, next_tight, non_zero_count + (curr_digit > 0 ? 1 : 0));
        }
    }

    return memo[idx][tight][non_zero_count] = result;
}

long long classy_numbers(long long number)
{
    string str_num = to_string(number);

    /* Memset */
    memset(memo, 0xff, sizeof(memo));

    return solve(str_num, 0, true, 0);
}

int main()
{
    int T;

    cin >> T;

    for (int i = 0; i < T; i++)
    {
        long long L;
        long long R;

        cin >> L;
        cin >> R;

        long long result = classy_numbers(R) - classy_numbers(L - 1);

        cout << result << "\n";
    }

    return 0;
}
