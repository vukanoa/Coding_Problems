/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    866) Prime Palindrome
    ===========================

    ============
    Description:
    ============

    Given an integer n, return the smallest prime palindrome greater than or
    equal to n.

    An integer is prime if it has exactly two divisors: 1 and itself. Note that
    1 is not a prime number.

        + For example, 2, 3, 5, 7, 11, and 13 are all primes.

    An integer is a palindrome if it reads the same from left to right as it
    does from right to left.

        + For example, 101 and 12321 are palindromes.

    The test cases are generated so that the answer always exists and is in the
    range [2, 2 * 108].

    =====================================
    FUNCTION: int primePalindrome(int n);
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 6
    Output: 7

    --- Example 2 ---
    Input: n = 8
    Output: 11

    --- Example 3 ---
    Input: n = 13
    Output: 101


    *** Constraints ***
    1 <= n <= 10^8

*/

#include <cmath>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 41.08% */
/* Space Beats: 23.24% */

/* Time  Complexity: O(sqrt(N) * 10^5) */
/* Space Complexity: O(logN)           */
class Solution {
public:
    int primePalindrome(int N)
    {
        for (int L = 1; L <= 5; L++)
        {
            // Check for odd-length palindromes
            for (int root = pow(10, L-1); root < pow(10, L); root++)
            {
                string s = to_string(root);

                for (int idx = L-2; idx >= 0; idx--)
                    s += s[idx];

                int palindrome = stoi(s);

                if (palindrome >= N && is_prime(palindrome))
                    return palindrome;
            }

            // Check for even-length palindromes
            for (int root = pow(10, L-1); root < pow(10, L); root++)
            {
                string s = to_string(root);

                for (int idx = L-1; idx >= 0; idx--)
                    s += s[idx];

                int palindrome = stoi(s);

                if (palindrome >= N && is_prime(palindrome))
                    return palindrome;
            }
        }

        return 0;
    }

private:
    bool is_prime(int N)
    {
        if (N < 2)
            return false;

        for (int divisor = 2; divisor * divisor <= N; divisor++)
        {
            if (N % divisor == 0)
                return false;
        }

        return true;
    }
};
