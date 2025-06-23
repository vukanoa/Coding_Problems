/*
    ============
    === HARD ===
    ============

    =============================
    2081) Sum of k-Mirror Numbers
    =============================

    ============
    Description:
    ============

    A k-mirror number is a positive integer without leading zeros that reads
    the same both forward and backward in base-10 as well as in base-k.

        + For example, 9 is a 2-mirror number. The representation of 9 in
          base-10 and base-2 are 9 and 1001 respectively, which read the same
          both forward and backward.

        + On the contrary, 4 is not a 2-mirror number. The representation of 4
          in base-2 is 100, which does not read the same both forward and
          backward.

    Given the base k and the number n, return the sum of the n smallest
    k-mirror numbers.

    ==========================================
    FUNCTION: long long kMirror(int k, int n);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: k = 2, n = 5
    Output: 25
    Explanation:
    The 5 smallest 2-mirror numbers and their representations in base-2 are
    listed as follows:
      base-10    base-2
        1          1
        3          11
        5          101
        7          111
        9          1001
    Their sum = 1 + 3 + 5 + 7 + 9 = 25. 

    --- Example 2 ---
    Input: k = 3, n = 7
    Output: 499
    Explanation:
    The 7 smallest 3-mirror numbers are and their representations in base-3 are
    listed as follows:
      base-10    base-3
        1          1
        2          2
        4          11
        8          22
        121        11111
        151        12121
        212        21212
    Their sum = 1 + 2 + 4 + 8 + 121 + 151 + 212 = 499.

    --- Example 3 ---
    Input: k = 7, n = 17
    Output: 20379000
    Explanation: The 17 smallest 7-mirror numbers are:
    1, 2, 3, 4, 5, 6, 8, 121, 171, 242, 292, 16561, 65656, 2137312, 4602064,
    6597956, 6958596


    *** Constraints ***
    2 <= k <= 9
    1 <= n <= 30

*/

/*
    ------------
    --- IDEA ---
    ------------

    Way too difficult. An unimportant problem, just skip it, trust me.

*/

/* Time  Beats: 73.68% */
/* Space Beats: 99.12% */

/* Time  Complexity: O(sqrt(10^10)) */
/* Space Complexity: O(1)           */
class Solution {
private:
    int digit[100];

public:
    long long kMirror(int base, int required_palindrome_count)
    {
        int curr_prefix = 1;
        int curr_count_of_valid_numbers = 0;
        long long total_sum_of_valid_numbers = 0;

        while (curr_count_of_valid_numbers < required_palindrome_count)
        {
            int next_prefix_limit = curr_prefix * 10;

            for (int palindrome_type = 0; palindrome_type < 2; palindrome_type++)
            {
                for (int prefix_num = curr_prefix; prefix_num < next_prefix_limit && curr_count_of_valid_numbers < required_palindrome_count; prefix_num++)
                {
                    long long candidate_num = prefix_num;

                    int suffix_seed = (palindrome_type == 0 ? prefix_num / 10 : prefix_num);

                    while (suffix_seed)
                    {
                        candidate_num = candidate_num * 10 + suffix_seed % 10;
                        suffix_seed /= 10;
                    }

                    if (is_palindrome(candidate_num, base))
                    {
                        curr_count_of_valid_numbers++;
                        total_sum_of_valid_numbers += candidate_num;
                    }
                }
            }

            curr_prefix = next_prefix_limit;
        }

        return total_sum_of_valid_numbers;
    }

private:
    bool is_palindrome(long long number, int base)
    {
        int digit_count = -1;

        while (number)
        {
            digit_count++;
            digit[digit_count] = number % base;
            number /= base;
        }

        for (int L = 0, R = digit_count; L < R; L++, R--)
        {
            if (digit[L] != digit[R])
            {
                return false;
            }
        }

        return true;
    }
};
