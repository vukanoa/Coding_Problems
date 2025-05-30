/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    3556) Sum of Largest Prime Substrings
    =====================================

    ============
    Description:
    ============

    Given a string s, find the sum of the 3 largest unique that can be formed
    using any of its substrings.

    Return the sum of the three largest unique prime numbers that can be
    formed. If fewer than three exist, return the sum of all available primes.
    If no prime numbers can be formed, return 0.

    =====
    Note: Each prime number should be counted only once, even if it appears in
          multiple substrings. Additionally, when converting a substring to an
          integer, any leading zeros are ignored.
    =====

    =================================================
    FUNCTION: long long sumOfLargestPrimes(string s);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "12234"
    Output: 1469
    Explanation:
        The unique prime numbers formed from the substrings of "12234" are 2, 3, 23, 223, and 1223.
        The 3 largest primes are 1223, 223, and 23. Their sum is 1469.


    --- Example 2 ---
    Input: s = "111"
    Output: 11
    Explanation:
        The unique prime number formed from the substrings of "111" is 11.
        Since there is only one prime number, the sum is 11.


    *** Constraints ***
    1 <= s.length <= 10
    s consists of only digits.

*/

#include <cmath>
#include <set>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 11.70% */
/* Space Beats: 72.34% */

/* Time  Complexity: O(N^2 * sqrt(K)) */ // Where K is the average magnitude of substring values
/* Space Complexity: O(N^2)           */
class Solution {
public:
    long long sumOfLargestPrimes(string s)
    {
        const int N = s.length();
        long long result = 0;

        set<long long, greater<long long>> set_of_primes;

        for (int i = 0; i < N; i++)
        {
            for (int j = i; j < N; j++)
            {
                int len = j - i + 1;

                string substr = s.substr(i, len);
                long long num = stoll(substr);

                if ( ! set_of_primes.count(num) && is_prime(num))
                    set_of_primes.insert(num);
            }
        }

        if (set_of_primes.empty())
            return 0;

        int count = 0;
        for (const long long& prime : set_of_primes)
        {
            result += prime;
            count++;

            if (count == 3)
                break;
        }

        return result;
    }

private:
    bool is_prime(long long num)
    {
        if (num == 1LL)
            return false;
        else if (num == 2)
            return true;

        for (int factor = 2; factor <= std::sqrt(num); factor++)
        {
            if (num % factor == 0)
                return false;
        }

        return true;
    }
};
