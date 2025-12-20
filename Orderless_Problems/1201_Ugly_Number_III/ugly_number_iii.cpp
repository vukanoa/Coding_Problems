/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1201) Ugly Number III
    ===========================

    ============
    Description:
    ============

    An ugly number is a positive integer that is divisible by a, b, or c.

    Given four integers n, a, b, and c, return the nth ugly number.

    ========================================================
    FUNCTION: int nthUglyNumber(int n, int a, int b, int c);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, a = 2, b = 3, c = 5
    Output: 4
    Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10... The 3rd is 4.

    --- Example 2 ---
    Input: n = 4, a = 2, b = 3, c = 4
    Output: 6
    Explanation: The ugly numbers are 2, 3, 4, 6, 8, 9, 10, 12... The 4th is 6.

    --- Example 3 ---
    Input: n = 5, a = 2, b = 11, c = 13
    Output: 10
    Explanation: The ugly numbers are 2, 4, 6, 8, 10, 11, 12, 13... The 5th is
                 10.


    *** Constraints ***
    1 <= n, a, b, c <= 10^9
    1 <= a * b * c <= 10^18
    It is guaranteed that the result will be in range [1, 2 * 10^9].

*/

#include <numeric>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Inclusion-Exclusion principle + Binary Search.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  44.42% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
public:    
   int nthUglyNumber(int k, int A, int B, int C)
   {
        int low  = 1;
        int high = 2 * static_cast<int>(1e9);

        long long a = static_cast<long long>(A);
        long long b = static_cast<long long>(B);
        long long c = static_cast<long long>(C);

        long long ab  = a * b  / std::gcd(a, b);
        long long bc  = b * c  / std::gcd(b, c);
        long long ac  = a * c  / std::gcd(a, c);
        long long abc = a * bc / std::gcd(a, bc);

        while (low < high)
        {
            int mid = low + (high - low) / 2; // Left-leaning

            int count = mid/a + mid/b + mid/c - mid/ab - mid/bc - mid/ac + mid/abc;

            if (count < k) 
                low = mid + 1;
            else // the condition: F(N) >= k
                high = mid;
        }

        return low;
    }
};
