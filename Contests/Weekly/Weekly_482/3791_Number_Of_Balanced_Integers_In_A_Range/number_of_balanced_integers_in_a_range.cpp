/*
    ============
    === HARD ===
    ============

    ============================================
    3791) Number of Balanced Integers in a Range
    ============================================

    ============
    Description:
    ============

    You are given two integers low and high.

    An integer is called balanced if it satisfies both of the following
    conditions:

        + It contains at least two digits.

        + The sum of digits at even positions is equal to the sum of digits at
          odd positions (the leftmost digit has position 1).

    Return an integer representing the number of balanced integers in the range
    [low, high] (both inclusive).

    =================================================================
    FUNCTION: long long countBalanced(long long low, long long high);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: low = 1, high = 100
    Output: 9
    Explanation:
    The 9 balanced numbers between 1 and 100 are 11, 22, 33, 44, 55, 66, 77,
    88, and 99.

    --- Example 2 ---
    Input: low = 120, high = 129
    Output: 1
    Explanation:
    Only 121 is balanced because the sum of digits at even and odd positions
    are both 2.

    --- Example 3 ---
    Input: low = 1234, high = 1234
    Output: 0
    Explanation:
    1234 is not balanced because the sum of digits at odd positions (1 + 3 = 4)
    does not equal the sum at even positions (2 + 4 = 6).


    *** Constraints ***
    1 <= low <= high <= 10^15

*/

#include <cstring>
#include <string>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    The "at least two digits" condition is enforced IMPLICITLY by the base
    case:

        if (idx == N)
            return (prev_digit != -1 && diff == 0) ? 1 : 0;

    Why does that work?

    prev_digit is -1 ONLY while we're still in the "skip leading zeroes"
    branch, however the moment we place the FIRST digit(a NON-zero digit, or a
    zero after a NON-zero digit), then prev_digit becomes that digit and is
    NEVER -1 again.

    So, if at idx == N, our prev_digit != -1, that means at least ONE digit was
    pleace, i.e. the number as >= 1 digit and it is NOT "all leading zeroes".


    But that guaranteees there are AT LEAST 1 digit and not AT LEAST 2 digits,
    so how do single-digit numbers actually get excluded?

    They're excluded by diff == 0 ombined with we we assign positions.

    They're excluded by diff == 0 combined with how we assign positions. For a
    single-digit number d (with d != 0), the only digit sits at position 1
    (odd). In the recursion: cpp

    if (idx & 1)
        diff -= curr_digit;
    else
        diff += curr_digit;

    Since idx == 0 for the ONLY digit, it goes into diff as +curr_digit. So
    diff is NEVER 0 for a VALID SINGLE DIGIT (i.e. [1..9]). Therefore no
    single-digit number is ever counted.

    Thus we fulfilled the "at least two" digits criterion.




    Why do we allocate 200 dimension for "diff"?

    Because diff CAN be NEGATIVE, and array indices CANNOT be negative.

        diff = even_sum - odd_sum.

    Over a number with up to 16 digits (our memo is sized [16]), each position
    contributes at most +9 or -9:

        + Worst case all odd-position digits are 9 and all even-position digits
          are 0 → diff = +9 * 8 = +72

        + Worst case all even-position digits are 9 and all odd-position digits
          are 0 → diff = -9 * 8 = -72


    Therefore diff can be [-72, 72]


    Example:

        idx = diff + 100

        diff = -72 --> index  28
        diff =   0 --> index 100
        diff = +72 --> index 172

*/

/* Time  Beats: 53.28% */
/* Space Beats: 82.79% */

/* Time  Complexity: O(logN * 2 * 9*logN * 11) */ // N is "high"
/* Space Complexity: O(logN * 2 * 9*logN * 11) */
class Solution {
private:
    //  16 --> because there are at most 16 digits in N=10^15 --> log(N)=16
    //   2 --> because it's EITHER tight   or NOT tight
    // 200 --> [-72, 72] if ALL even digits are 9s and ALL odd digits are 0s
    //  11 --> because there are exactly 10 digits, which is always a CONSTANT!
    long long memo[16][2][200][11];

public:
    long long countBalanced(long long low, long long high)
    {
        return number_of_balanced_integers(high) -
               number_of_balanced_integers(low-1);
    }

private:
    long long number_of_balanced_integers(long long number)
    {
        if (number < 0)
            return 0;

        string str_num = to_string(number);

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(str_num, 0, true, 0, -1);
    }

    long long solve(string& str_num, int idx, int tight, int diff, int prev_digit)
    {
        const int N = str_num.size();

        if (idx == N)
            return (prev_digit != -1 && diff == 0) ? 1 : 0;

        if (memo[idx][tight][diff + 100][prev_digit + 1] != -1)
            return memo[idx][tight][diff + 100][prev_digit + 1];

        int limit_digit = tight ? str_num[idx] - '0' : 9;

        long long result = 0;
        for (int curr_digit = 0; curr_digit <= limit_digit; curr_digit++)
        {
            int new_tight = tight && (curr_digit == limit_digit);

            if (prev_digit == -1 && curr_digit == 0) // Skip
            {
                result += solve(str_num, idx+1, new_tight, diff, -1);
            }
            else // Take
            {
                if (idx & 1)
                    result += solve(str_num, idx+1, new_tight, diff - curr_digit, curr_digit);
                else
                    result += solve(str_num, idx+1, new_tight, diff + curr_digit, curr_digit);
            }
        }

        return memo[idx][tight][diff + 100][prev_digit + 1] = result;
    }
};
