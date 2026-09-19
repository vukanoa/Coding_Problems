/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    2761) Prime Pairs With Target SUm
    =================================

    ============
    Description:
    ============

    You are given an integer n. We say that two integers x and y form a prime
    number pair if:

        1 <= x <= y <= n
        x + y == n
        x and y are prime numbers

    Return the 2D sorted list of prime number pairs [xi, yi]. The list should
    be sorted in increasing order of xi. If there are no prime number pairs at
    all, return an empty array.

    =====
    Note: A prime number is a natural number greater than 1 with only two
          factors, itself and 1. 
    =====

    ====================================================
    FUNCTION: vector<vector<int>> findPrimePairs(int n);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10
    Output: [[3,7],[5,5]]
    Explanation: In this example, there are two prime pairs that satisfy the
    criteria. These pairs are [3,7] and [5,5], and we return them in the sorted
    order as described in the problem statement.

    --- Example 2 ---
    Input: n = 2
    Output: []
    Explanation: We can show that there is no prime number pair that gives a
                 sum of 2, so we return an empty array. 


    *** Constraints ***
    1 <= n <= 10^6

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 69.60% */
/* Space Beats: 55.36% */

/* Time  Complexity: O(N * log(logN)) */
/* Space Complexity: O(N)             */
class Solution {
private:
    vector<bool> is_prime;

public:
    vector<vector<int>> findPrimePairs(int n)
    {
        vector<vector<int>> result;

        initialize_sieve_of_eratosthenes(n);

        // 2Sum
        int L_prime = 2;
        int R_prime = n - 2;

        while (L_prime <= R_prime)
        {
            if (is_prime[L_prime] && is_prime[R_prime])
                result.push_back( {L_prime, R_prime} );

            ++L_prime;
            --R_prime;
        }

        return result;
    }

private:
    // Sieve of Eratosthenes: O(N * log(log N))
    void initialize_sieve_of_eratosthenes(int N)
    {
        is_prime = vector<bool>(N + 1, true);

        is_prime[0] = false;
        is_prime[1] = false;

        for (int num = 2; num * num <= N; num++)
        {
            if ( ! is_prime[num])
                continue;

            for (int multiple = num * num; multiple <= N; multiple += num)
                is_prime[multiple] = false;
        }
    }
};
