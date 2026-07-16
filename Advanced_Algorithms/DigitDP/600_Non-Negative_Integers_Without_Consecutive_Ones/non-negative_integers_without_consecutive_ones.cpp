/*
    ============
    === HARD ===
    ============

    ====================================================
    600) Non-Negative Integers Without Consecutives Ones
    ====================================================

    ============
    Description:
    ============

    Given a positive integer n, return the number of the integers in the range
    [0, n] whose binary representations do not contain consecutive ones.

    ==================================
    FUNCTION: int findIntegers(int n);
    ==================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5
    Output: 5
    Explanation:
    Here are the non-negative integers <= 5 with their corresponding binary
    representations:
        0 : 0
        1 : 1
        2 : 10
        3 : 11
        4 : 100
        5 : 101
    Among them, only integer 3 disobeys the rule (two consecutive ones) and the
    other 5 satisfy the rule. 


    --- Example 2 ---
    Input: n = 1
    Output: 2


    --- Example 3 ---
    Input: n = 2
    Output: 3


    *** Constraints ***
    1 <= n <= 10^9

*/

#include <algorithm>
#include <cstring>
#include <limits>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  45.71% */

/* Time  Complexity: O(30 * 2 * 3) --> O(logN * 2 * 3) --> O(logN) --> O(D) */
/* Space Complexity: O(30 * 2 * 3) --> O(logN * 2 * 3) --> O(logN) --> O(D) */
class Solution {
private:
    int memo[30][2][3]; // 30 because 10^9 can be represented using 29 bits

public:
    int findIntegers(int n)
    {
        string str_binary_number = to_binary_string(n); // O(log2(N))

        /* Memset */
        memset(memo, 0xff, sizeof(memo)); // O(30 * 2 * 3)

        return solve(str_binary_number, 0, true, -1);
    }

private:
    /* Time  Complexity: O(log2(N)) */
    /* Space Complexity: O(log2(N)) */
    string to_binary_string(unsigned int number)
    {
        if (number == 0)
            return "0";

        int bits = std::numeric_limits<unsigned int>::digits; // C++98

        string binary_string;
        binary_string.reserve(bits); // To prevent repeated reallocations

        while (number > 0)
        {
            binary_string += static_cast<char>((number & 1) + '0'); // Append

            number >>= 1; // Bit Shift to the RIGHT by 1, i.e. divide by 2
        }

        /* Reverse */
        reverse(binary_string.begin(), binary_string.end());

        return binary_string;
    }

    int solve(string& str_binary_number, int idx, int tight, int prev_bit)
    {
        const int N = str_binary_number.size();

        if (idx == N)
            return (prev_bit != -1) ? 1 : 0; // prev_bit != -1 --> started

        if (memo[idx][tight][prev_bit + 1] != -1)
            return memo[idx][tight][prev_bit + 1];

        int limit_bit = tight ? str_binary_number[idx] - '0' : 1;

        int result = 0;
        for (int curr_bit = 0; curr_bit <= limit_bit; curr_bit++)
        {
            int new_tight = tight && (curr_bit == limit_bit);

            if (prev_bit == 1 && curr_bit == 1)
                continue;

            result += solve(str_binary_number, idx+1, new_tight, curr_bit);
        }

        return memo[idx][tight][prev_bit + 1] = result;
    }
};
