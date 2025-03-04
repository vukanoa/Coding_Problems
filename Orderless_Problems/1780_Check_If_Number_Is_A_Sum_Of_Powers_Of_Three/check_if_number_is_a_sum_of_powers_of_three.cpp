/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    1780) Check if Number is a Sum of Powers of Three
    =================================================

    ============
    Description:
    ============

    Given an integer n, return true if it is possible to represent n as the sum
    of distinct powers of three. Otherwise, return false.

    An integer y is a power of three if there exists an integer x such that
    y == 3x.

    =========================================
    FUNCTION: bool checkPowersOfThree(int n);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 12
    Output: true
    Explanation: 12 = 31 + 32

    --- Example 2 ---
    Input: n = 91
    Output: true
    Explanation: 91 = 30 + 32 + 34

    --- Example 3 ---
    Input: n = 21
    Output: false

    *** Constraints ***
    1 <= n <= 10^7

*/

#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Approach it how you would approach to obtain a binary representation of a
    number.

    You start with the highest power of 2 that is LESS than n, then you
    subtract that power of 2.

    Now start with the highest power of 2 that is LESS than that remainder from
    the previous subtraciton.

    And so on. If at any point you get that "sum" is equal to the starting n,
    return true.

    Otherwise you'll end up finishing the loop and you'll return false.

    Since the Constraint for this problem is 10^7, the highest power of 3 that
    that is LESS than 10^7 is 3^14.

     10^7  = 10000000
      3^14 = 4782969    // Less    than 10^7
      3^15 = 14348907   // Greater than 10^7

     Therefore, we'll have a vector of 16 numbers, i.e. 16 powers of 3.

     [3^0, 3^1, 3^2, ..., 3^15]

    Simply go through it from the back as if you're trying to find out the
    binary representation of a number and that's it.

    Even if the Constraint was 2^64 - 1, which would be the biggest number on
    a 64-bit machine, the Time Complexity would still be O(1). In that case
    we'd have a vector of 42 <long long> numbers instead.


    2^64 - 1 = 18446744073709551616
    3^41     = 36472996377170786403 // Less    than 2^64 - 1
    3^40     = 12157665459056928801 // Greater than 2^64 - 1

*/

/* Time  Beats: 100.00% */
/* Space Beats:  19.48% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool checkPowersOfThree(int n)
    {
        if (n == 1)
            return true;

        vector<long long> power(16, 0);
        power[0] = 1;

        for (int i = 1; i < 16; i++)
            power[i] = pow(3, i);

        int sum = 0;
        for (int i = 15; i >= 0; i--)
        {
            if (sum + power[i] > n)
                continue;

            sum += power[i];

            if (sum == n)
                return true;
        }

        return false;
    }
};
