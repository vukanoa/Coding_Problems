/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    4022) K-th Digit in Infinite String
    ===================================

    ============
    Description:
    ============

    You are given an integer k.

    An infinite string is formed by concatenating the decimal representations
    of the positive integers, without separators.

    For every nonnegative integer b, block b contains the positive integers
    from 10 * b through 10 * b + 9. The integers in each block are appended as
    follows:

        + If b is even, append the integers in increasing order.
        + If b is odd, append the integers in decreasing order.

    Therefore, the string starts with the integers 1 through 9, followed by 19
    through 10, then 20 through 29, then 39 through 30, and so on.

    Return the kth digit (1-indexed) of this string.

    ====================================
    FUNCTION: int kthDigit(long long k);
    ====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: k = 4
    Output: 4
    Explanation:
    The string begins as "123456789..". The 4th digit is '4'.

    --- Example 2 ---
    Input: k = 15
    Output: 7
    Explanation:
    The string begins as "123456789191817..". The 15th digit is '7'.

    --- Example 3 ---
    Input: k = 11
    Output: 9
    Explanation:
    The string begins as "12345678919..". The 11th digit is '9'.


    *** Constraints ***
    1 <= k <= 10^15

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.94% */
/* Space Beats: 5.44% */

/* Time  Complexity: O(log K) */
/* Space Complexity: O(log K) */
class Solution {
public:
    int kthDigit(long long k)
    {
        if (k <= 9)
            return k;

        vector<long long> cumulative_digit_count;
        cumulative_digit_count.push_back(0);

        long long power_of_ten = 1LL;
        long long sum          = 0LL;

        for (int i = 1; i <= 16; i++)
        {
            sum += 9 * power_of_ten * i; // Digits contributed by all 'i' digit
                                         // numbers
            cumulative_digit_count.push_back(sum);

            power_of_ten *= 10;
        }
        cumulative_digit_count.push_back(sum);

        int digit_len = 0;
        for (unsigned i = 0; i < cumulative_digit_count.size(); i++)
        {
            if (cumulative_digit_count[i] >= k)
            {
                digit_len = i; // Our target lies in the "digi_len" digit group
                break;
            }
        }

        k -= cumulative_digit_count[digit_len-1];// remov previous digit groups
        k--;                                     // convert to 0-based indexing

        long long number_offset = k / digit_len;
        long long digit_offset  = k % digit_len;
        long long first_number  = 1;

        for (int i = 0; i < digit_len-1; i++)
            first_number *= 10; // first "digit_len" digit number

        long long number = first_number + number_offset;
        long long block = number / 10;

        if (block % 2)
        {
            number = block*10 + (9 - (number % 10)); // Odd blocks are REVERSED
        }

        string result = to_string(number);

        return result[digit_offset] - '0';
    }
};
