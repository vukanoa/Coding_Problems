/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    3918) Sum of Primes Between NUmber and Its Reverse
    ==================================================

    ============
    Description:
    ============

    You are given an integer n.

    Let r be the integer formed by reversing the digits of n.

    Return the sum of all prime numbers between min(n, r) and max(n, r),
    inclusive.

    ========================================
    FUNCTION: int sumOfPrimesInRange(int n);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 13
    Output: 132
    Explanation:
        The reverse of 13 is 31. Thus, the range is [13, 31].
        The prime numbers in this range are 13, 17, 19, 23, 29, and 31.
        The sum of these prime numbers is 13 + 17 + 19 + 23 + 29 + 31 = 132.

    --- Example 2 ---
    Input: n = 10
    Output: 17
    Explanation:
        The reverse of 10 is 1. Thus, the range is [1, 10].
        The prime numbers in this range are 2, 3, 5, and 7.
        The sum of these prime numbers is 2 + 3 + 5 + 7 = 17.

    --- Example 3 ---
    Input: n = 8
    Output: 0
    Explanation:
        The reverse of 8 is 8. Thus, the range is [8, 8].
        There are no prime numbers in this range, so the sum is 0.


    *** Constraints ***
    1 <= n <= 1000

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If you know about "Sieve of Eratosthenes", the problem is trivial.

*/

/* Time  Beats: 55.88% */
/* Space Beats: 36.62% */

/* Time  Complexity: O(MAX * log(log(MAX))) */
/* Space Complexity: O(MAX)                 */
class Solution {
public:
    int sumOfPrimesInRange(int n)
    {
        int r = 0;

        int tmp_n = n;
        while (tmp_n > 0)
        {
            int digit = tmp_n % 10;

            r = 10 * r + digit;

            // Divide
            tmp_n /= 10;
        }

        const int MIN = min(n, r);
        const int MAX = max(n, r);

        vector<bool> prime(MAX+1, true);
        prime[0] = false;
        prime[1] = false;
        
        for (int i = 2; i * i <= MAX; i++)
        {
            if ( ! prime[i])
                continue;
            
            for (int num = i*i; num <= MAX; num += i)
                prime[num] = false;
        }

        int result = 0;
        for (int i = MIN; i <= MAX; i++)
        {
            if (prime[i])
                result += i;
        }

        return result;
    }
};
