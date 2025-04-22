/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    2338) Count the Number of Ideal Arrays
    ======================================

    ============
    Description:
    ============

    You are given two integers n and maxValue, which are used to describe an
    ideal array.

    A 0-indexed integer array arr of length n is considered ideal if the
    following conditions hold:

        + Every arr[i] is a value from 1 to maxValue, for 0 <= i < n.
        + Every arr[i] is divisible by arr[i - 1], for 0 < i < n.

    Return the number of distinct ideal arrays of length n. Since the answer
    may be very large, return it modulo 10^9 + 7.

    ===============================================
    FUNCTION: int idealArrays(int n, int maxValue);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, maxValue = 5
    Output: 10
    Explanation: The following are the possible ideal arrays:
    - Arrays starting with the value 1 (5 arrays): [1,1], [1,2], [1,3], [1,4], [1,5]
    - Arrays starting with the value 2 (2 arrays): [2,2], [2,4]
    - Arrays starting with the value 3 (1 array): [3,3]
    - Arrays starting with the value 4 (1 array): [4,4]
    - Arrays starting with the value 5 (1 array): [5,5]
    There are a total of 5 + 2 + 1 + 1 + 1 = 10 distinct ideal arrays.

    --- Example 2 ---
    Input: n = 5, maxValue = 3
    Output: 11
    Explanation: The following are the possible ideal arrays:
    - Arrays starting with the value 1 (9 arrays):
       - With no other distinct values (1 array): [1,1,1,1,1]
       - With 2nd distinct value 2 (4 arrays): [1,1,1,1,2], [1,1,1,2,2], [1,1,2,2,2], [1,2,2,2,2]
       - With 2nd distinct value 3 (4 arrays): [1,1,1,1,3], [1,1,1,3,3], [1,1,3,3,3], [1,3,3,3,3]
    - Arrays starting with the value 2 (1 array): [2,2,2,2,2]
    - Arrays starting with the value 3 (1 array): [3,3,3,3,3]
    There are a total of 9 + 1 + 1 = 11 distinct ideal arrays.


    *** Constraints ***
    2 <= n <= 10^4
    1 <= maxValue <= 10^4

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 88.99% */
/* Space Beats: 64.22% */

/* Time  Complexity: O((n + w(m)) * w(m)w + m * w(m)) */
/* Space Complexity: O((n + log(m)) * log(m))         */

const int MOD = 1e9 + 7;
const int MAX_N = 1e4 + 10;
const int MAX_P = 15;            // There are up to 15 prime factors

int combinations[MAX_N + MAX_P][MAX_P + 1]; // Binomial coefficients
vector<int> prime_exponent_counts[MAX_N];   // List of prime factor counts
int sieve[MAX_N];                           // Minimum prime factor

class Solution {
public:
    Solution() {
        if (combinations[0][0])
        {
            return;
        }

        // Sieve of Eratosthenes to compute smallest prime factor
        for (int i = 2; i < MAX_N; i++)
        {
            if (sieve[i] == 0)
            {
                for (int j = i; j < MAX_N; j += i)
                {
                    sieve[j] = i;
                }
            }
        }

        // Compute the prime exponent count for every number up to MAX_VALUE
        for (int i = 2; i < MAX_N; i++)
        {
            int number = i;

            while (number > 1)
            {
                int prime = sieve[number];
                int exponent = 0;

                while (number % prime == 0)
                {
                    number /= prime;
                    exponent++;
                }

                prime_exponent_counts[i].push_back(exponent);
            }
        }

        // Compute binomial coefficients: combinations[n][k] = C(n, k)
        combinations[0][0] = 1;
        for (int i = 1; i < MAX_N + MAX_P; i++)
        {
            combinations[i][0] = 1;

            for (int j = 1; j <= min(i, MAX_P); j++)
                combinations[i][j] = (combinations[i - 1][j] + combinations[i - 1][j - 1]) % MOD;
        }
    }
    int idealArrays(int n, int maxValue)
    {
        long long total_ways = 0;

        for (int value = 1; value <= maxValue; value++)
        {
            long long ways_for_value = 1;

            for (int exponent : prime_exponent_counts[value])
                ways_for_value = ways_for_value * combinations[n + exponent - 1][exponent] % MOD;

            total_ways = (total_ways + ways_for_value) % MOD;
        }

        return total_ways;
    }
};
