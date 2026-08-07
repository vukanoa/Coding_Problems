/*
    ============
    === HARD ===
    ============

    =========================================
    3348) Smallest Divisible Digit Product II
    =========================================

    ============
    Description:
    ============

    You are given a string num which represents a positive integer, and an
    integer t.

    A number is called zero-free if none of its digits are 0.

    Return a string representing the smallest zero-free number greater than or
    equal to num such that the product of its digits is divisible by t. If no
    such number exists, return "-1".

    =========================================================
    FUNCTION: string smallestNumber(string num, long long t);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = "1234", t = 256
    Output: "1488"
    Explanation:
    The smallest zero-free number that is greater than 1234 and has the product
    of its digits divisible by 256 is 1488, with the product of its digits
    equal to 256.

    --- Example 2 ---
    Input: num = "12355", t = 50
    Output: "12355"
    Explanation:
    12355 is already zero-free and has the product of its digits divisible by
    50, with the product of its digits equal to 150.

    --- Example 3 ---
    Input: num = "11111", t = 26
    Output: "-1"
    Explanation:
    No number greater than 11111 has the product of its digits divisible by 26.


    *** Constraints ***
    2 <= num.length <= 2 * 10^5
    num consists only of digits in the range ['0', '9'].
    num does not contain leading zeros.
    1 <= t <= 10^14

*/

#include <cstdint>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Too difficult... Do not even bother.

*/

/* Time  Beats: 70.69% */
/* Space Beats: 89.66% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    static constexpr uint8_t GCD[10][10] = {
        {},
        {1},
        {2, 1},
        {3, 1, 1},
        {4, 1, 2, 1},
        {5, 1, 1, 1, 1},
        {6, 1, 2, 3, 2, 1},
        {7, 1, 1, 1, 1, 1, 1},
        {8, 1, 2, 1, 4, 1, 2, 1},
        {9, 1, 1, 3, 1, 1, 3, 1, 1},
    };

    static constexpr int MAX_N = 200001;

    long long remaining_product[MAX_N    ];
    char      result           [MAX_N + 1];

public:
    string smallestNumber(string num, long long t)
    {
        if ( ! contains_only_prime_factors_2_3_5_7(t))
            return "-1";

        const int N = num.size();

        int first_zero_idx = preprocess(num, t);

        if (remaining_product[N] == 1)
            return num;

        for (int idx = first_zero_idx; idx >= 0; idx--)
        {
            while (++num[idx] <= '9')
            {
                long long remaining = consume_digit(remaining_product[idx], num[idx] - '0');

                int largest_digit = 9;
                for (int suffix_idx = N - 1; suffix_idx > idx; suffix_idx--)
                {
                    while (remaining % largest_digit != 0)
                        largest_digit--;

                    remaining /= largest_digit;
                    num[suffix_idx] = largest_digit + '0';
                }

                if (remaining == 1)
                    return num;
            }
        }

        return construct_longer_answer(N, t);
    }

private:
    bool contains_only_prime_factors_2_3_5_7(long long t)
    {
        long long remaining = t >> __builtin_ctzll(t);

        for (int prime : {3, 5, 7})
        {
            while (remaining % prime == 0)
                remaining /= prime;
        }

        return remaining == 1;
    }

    int preprocess(string& num, long long t)
    {
        const int N = num.size();

        remaining_product[0] = t;

        int first_zero_idx = N - 1;

        for (int idx = 0; idx < N; idx++)
        {
            if (num[idx] == '0')
            {
                first_zero_idx = idx;
                break;
            }

            remaining_product[idx + 1] = consume_digit(remaining_product[idx], num[idx] - '0');
        }

        return first_zero_idx;
    }

    long long consume_digit(long long remaining, int digit)
    {
        return remaining / GCD[digit][remaining % digit];
    }

    string construct_longer_answer(int original_length, long long t)
    {
        int write_idx = MAX_N + 1;

        for (int digit = 9; digit >= 2; digit--)
        {
            while (t % digit == 0)
            {
                result[--write_idx] = digit + '0';
                t /= digit;
            }
        }

        while (MAX_N - write_idx < original_length)
            result[--write_idx] = '1';

        return string(result + write_idx, MAX_N + 1 - write_idx);
    }
};
