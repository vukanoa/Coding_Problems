/*
    ============
    === HARD ===
    ============

    ======================================
    902) Numbers At Most N Given Digit Set
    ======================================

    ============
    Description:
    ============

    Given an array of digits which is sorted in non-decreasing order. You can
    write numbers using each digits[i] as many times as we want. For example,
    if digits = ['1','3','5'], we may write numbers such as '13', '551', and
    '1351315'.

    Return the number of positive integers that can be generated that are less
    than or equal to a given integer n.

    ==================================================================
    FUNCTION: int atMostNGivenDigitSet(vector<string>& digits, int n);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: digits = ["1","3","5","7"], n = 100
    Output: 20
    Explanation: 
    The 20 numbers that can be written are:
    1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.

    --- Example 2 ---
    Input: digits = ["1","4","9"], n = 1000000000
    Output: 29523
    Explanation: 
    We can write 3 one digit numbers, 9 two digit numbers, 27 three digit
    numbers, 81 four digit numbers, 243 five digit numbers, 729 six digit
    numbers, 2187 seven digit numbers, 6561 eight digit numbers, and 19683 nine
    digit numbers. In total, this is 29523 integers that can be written using
    the digits array.

    --- Example 3 ---
    Input: digits = ["7"], n = 8
    Output: 1


    *** Constraints ***
    1 <= digits.length <= 9
    digits[i].length == 1
    digits[i] is a digit from '1' to '9'.
    All the values in digits are unique.
    digits is sorted in non-decreasing order.
    1 <= n <= 10^9

*/

#include <cstring>
#include <string>
#include <vector>
using namespace std;


/* Time  Beats: 100.00% */
/* Space Beats:  24.36% */

/* Time  Complexity: O(10 * 2 * 11) --> O(logN * 1 * D) --> O(logN) */ // D=9
/* Space Complexity: O(10 * 2 * 11) --> O(logN * 1 * 1) --> O(logN) */
class Solution {
private:
    int memo[10][2][11]; // 10^9 can be represened using 10 digits

public:
    int atMostNGivenDigitSet(vector<string>& digits, int n)
    {
        string str_n = to_string(n);

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(str_n, 0, true, -1, digits);
    }

private:
    int solve(string& str_n, int idx, int tight, int prev_digit, vector<string>& digits)
    {
        const int SIZE   = str_n.size();
        const int DIGITS = digits.size();

        if (idx == SIZE)
            return (prev_digit != -1) ? 1 : 0; // If STARTED --> 1

        if (memo[idx][tight][prev_digit + 1] != -1)
            return memo[idx][tight][prev_digit + 1];


        int limit_digit = tight ? str_n[idx] - '0' : 9;

        int result = 0;
        if (prev_digit == -1) // NOT started
            result += solve(str_n, idx + 1, false, -1, digits);

        for (int i = 0; i < DIGITS; i++)
        {
            int curr_digit = stoi(digits[i]);

            if (curr_digit > limit_digit)
                break;

            int new_tight = tight && (curr_digit == limit_digit);

            result += solve(str_n, idx + 1, new_tight, curr_digit, digits);
        }

        return memo[idx][tight][prev_digit + 1] = result;
    }
};
