/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    2523) Closest Prime Numbers in Range
    ====================================

    ============
    Description:
    ============

    Given two positive integers left and right, find the two integers num1 and
    num2 such that:

        + left <= num1 < num2 <= right .

        + Both num1 and num2 are

        num2 - num1 is the minimum amongst all other pairs satisfying the above
        conditions.

    Return the positive integer array ans = [num1, num2]. If there are multiple
    pairs satisfying these conditions, return the one with the smallest num1
    value. If no such numbers exist, return [-1, -1].

    =========================================================
    FUNCTION: vector<int> closestPrimes(int left, int right);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: left = 10, right = 19
    Output: [11,13]
    Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
                 The closest gap between any pair is 2, which can be achieved
                 by [11,13] or [17,19]. Since 11 is smaller than 17, we return
                 the first pair.

    --- Example 2 ---
    Input: left = 4, right = 6
    Output: [-1,-1]
    Explanation: There exists only one prime number in the given range, so the
                 conditions cannot be satisfied.


    *** Constraints ***
    1 <= left <= right <= 10^6

*/

#include <climits>
#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 77.04% */
/* Space Beats: 74.07% */

/* Time  Complexity: O(R * loglogR + R - L) */
/* Space Complexity: O(R)                   */
class Solution {
public:
    vector<int> closestPrimes(int left, int right)
    {
        vector<int> result = {-1,-1};

        vector<bool> prime(right + 1, true);
        prime[0] = false;
        prime[1] = false;

        // Sieve of Eratosthenes: O(N log log N)
        for (int num = 2; num <= sqrt(right); num++)
        {
            if (num >= left)
                break;

            if ( ! prime[num])
                continue;

            for (int i = num; i <= right; i += num)
                prime[i] = false;
        }

        int smallest_diff = INT_MAX;
        int last = -1;

        for (int num = left; num <= right; num++)
        {
            if ( ! prime[num])
                continue;

            if (last != -1)
            {
                if (num - last < smallest_diff)
                {
                    smallest_diff = num - last;

                    result[0] = last;
                    result[1] = num;
                }
            }

            last = num;
        }

        return result;
    }
};
