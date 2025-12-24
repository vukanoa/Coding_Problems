/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    400) Nth digit
    ===========================

    ============
    Description:
    ============

    Given an integer n, return the nth digit of the infinite integer sequence
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...].

    ==================================
    FUNCTION: int findNthDigit(int n);
    ==================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3
    Output: 3

    --- Example 2 ---
    Input: n = 11
    Output: 0
    Explanation: The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                 11, ... is a 0, which is part of the number 10.


    *** Constraints ***
    1 <= n <= 2^31 - 1

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

        From 1    to  9   include    9 one   digit  number;
        From 10   to  99  include   90 two   digits number;
        From 100  to  999 include  900 three digits number;
        From 1000 to 9999 include 9000 four  digits number;
        ...

*/

/* Time  Beats: 100.00% */
/* Space Beats:  34.06% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
public:
    int findNthDigit(int n)
    {
        int digit_len = 1;

        long long numbers_in_block = 9;
        int block_start_value = 1;

        // Skip entire blocks of numbers with the same digit length
        while (n > digit_len * numbers_in_block)
        {
            n -= digit_len * numbers_in_block;
            digit_len++;

            numbers_in_block *= 10;
            block_start_value *= 10;
        }

        // Identify the exact number that contains the desired digit
        block_start_value += (n - 1) / digit_len;

        // Convert number to string to extract the digit
        string number_as_string = to_string(block_start_value);
        return number_as_string[(n - 1) % digit_len] - '0';
    }
};
