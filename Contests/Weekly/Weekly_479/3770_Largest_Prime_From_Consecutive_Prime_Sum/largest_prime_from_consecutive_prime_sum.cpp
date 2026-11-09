/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    3770) Largest Prime from Consecutive Prime Sum
    ==============================================

    ============
    Description:
    ============

    You are given an integer n.

    Return the largest prime number less than or equal to n that can be
    expressed as the sum of one or more consecutive prime numbers starting from
    2. If no such number exists, return 0.

    ==================================
    FUNCTION: int largestPrime(int n);
    ==================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 20
    Output: 17
    Explanation:
    The prime numbers less than or equal to n = 20 which are consecutive prime
    sums are:
        2 = 2
        5 = 2 + 3
        17 = 2 + 3 + 5 + 7
    The largest is 17, so it is the answer.

    --- Example 2 ---
    Input: n = 2
    Output: 2
    Explanation:
    The only consecutive prime sum less than or equal to 2 is 2 itself.


    *** Constraints ***
    1 <= n <= 5 * 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  7.50% */
/* Space Beats: 39.33% */

/* Time  Complexity: O(N * log(logN)) */
/* Space Complexity: O(N)             */
class Solution {
private:
    static constexpr int FINAL_NUM = 5 * 1e5;
    vector<bool> is_prime;
    
public:
    Solution()
        : is_prime(FINAL_NUM + 1, true)
    {
    }

    int largestPrime(int n)
    {
        if (n < 2) // But no less than 1 can be the case due to Constraints
            return 0;
        
        int result = 0;

        // O(N * log(logN)) since we always go on until sqrt(n)
        // after sqrt(n) the factors are repeating in reciprocal way
        // so we do not need to go further
        initialize_sieve();

        int prefix_sum = 0; // of primes
        for (int num = 2; num <= n; num++)
        {
            if ( ! is_prime[num])
                continue;
            
            prefix_sum += num; // num is 100% a PRIME here

            if (prefix_sum > n)
                break;

            if (is_prime[prefix_sum])
                result = prefix_sum;
        }

        return result;
    }

private:
    // O(N * log(logN))
    void initialize_sieve()
    {
        is_prime[0] = false;
        is_prime[1] = false;

        for (int num = 2; num * num <= FINAL_NUM; num++)
        {
            if ( ! is_prime[num])
                continue;
            
            for (int j = num * num; j <= FINAL_NUM; j += num)
                is_prime[j] = false;
        }
    }
};
