/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    372) Super Pow
    ===========================

    ============
    Description:
    ============

    Your task is to calculate ab mod 1337 where a is a positive integer and b
    is an extremely large positive integer given in the form of an array.

    ==============================================
    FUNCTION: int superPow(int a, vector<int>& b);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: a = 2, b = [3]
    Output: 8

    --- Example 2 ---
    Input: a = 2, b = [1,0]
    Output: 1024

    --- Example 3 ---
    Input: a = 1, b = [4,3,3,8,5,2]
    Output: 1


    *** Constraints ***
    1 <= a <= 2^31 - 1
    1 <= b.length <= 2000
    0 <= b[i] <= 9
    b does not contain leading zeros.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  19.37% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
    const int MOD = 1337;

    int fast_exponentiation(int base, int exponent)
    {
        int result = 1;
        base %= MOD;

        while (exponent > 0)
        {
            // If the current LSB is set(i.e. 1)
            if (exponent & 1)
                result = (result * base) % MOD;

            base = (base * base) % MOD;

            // Right Shift
            exponent >>= 1;
        }

        return result;
    }

public:
    int superPow(int a, vector<int>& b)
    {
        if (b.empty())
            return 1;

        int last_digit = b.back();
        b.pop_back();

        int part1 = fast_exponentiation(superPow(a, b), 10);
        int part2 = fast_exponentiation(a, last_digit);

        return (part1 * part2) % MOD;
    }
};
