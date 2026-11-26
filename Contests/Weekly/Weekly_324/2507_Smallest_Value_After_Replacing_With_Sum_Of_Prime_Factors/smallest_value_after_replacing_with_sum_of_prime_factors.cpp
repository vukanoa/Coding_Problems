/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================================
    2507) Smallest Value After Replacing With Sum of Prime Factors
    ==============================================================

    ============
    Description:
    ============

    You are given a positive integer n.

    Continuously replace n with the sum of its prime factors.

        Note that if a prime factor divides n multiple times, it should be
        included in the sum as many times as it divides n.

    Return the smallest value n will take on.

    ===================================
    FUNCTION: int smallestValue(int n);
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 15
    Output: 5
    Explanation: Initially, n = 15.
    15 = 3 * 5, so replace n with 3 + 5 = 8.
    8 = 2 * 2 * 2, so replace n with 2 + 2 + 2 = 6.
    6 = 2 * 3, so replace n with 2 + 3 = 5.
    5 is the smallest value n will take on.

    --- Example 2 ---
    Input: n = 3
    Output: 3
    Explanation: Initially, n = 3.
    3 is the smallest value n will take on.


    *** Constraints ***
    2 <= n <= 10^5

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.20% */
/* Space Beats: 12.06% */

/* Time  Complexity: O(N * log(log(N))  +  K * sqrt(N)  +  K * logN) */ // K ~ logN
/* Space Complexity: O(N)                                            */
class Solution {
private:
    const int FINAL_NUM = 1e5;
    vector<bool> is_prime;
    
public:
    int smallestValue(int n)
    {
        int result = n;
        
        /* Initialize Sieve: O(N log log N) */
        initialize_sieve(); 

        /* Repeated Prime Factorization and Summation: O(K * sqrt(N)) */
        while ( ! is_prime[n])
        {
            unordered_map<int,int> prime_factor_freqs;
            prime_factor_freqs = get_prime_factor_freqs(n);

            int new_n = 0;
            for (const auto& [prime, freq] : prime_factor_freqs)
                new_n += prime * freq;

            result = min(result, new_n);

            if (n == new_n)
                break;

            n = new_n;
        }

        return result;
    }

private:
    /* Sieve of Eratosthenes: O(N log log N) */
    void initialize_sieve()
    {
        is_prime.assign(FINAL_NUM + 1, true);
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

    /* Prime Factorization: O(sqrt(N)) */
    unordered_map<int, int> get_prime_factor_freqs(int number)
    {
        unordered_map<int, int> prime_factor_freqs;

        int prime = 2;
        while (number > 1)
        {
            while (number % prime != 0)
            {
                int factor = prime;
                ++factor;
                while ( ! is_prime[factor])
                    ++factor;

                prime = factor;
            }

            ++prime_factor_freqs[prime];

            number /= prime;
        }

        return prime_factor_freqs;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 37.83% */
/* Space Beats: 97.16% */

/* Time  Complexity: O(K * sqrt(N)) */
/* Space Complexity: O(1)           */
class Solution_Cleaner_But_Less_Efficient {
public:
    int smallestValue(int n) 
    {   
        for(;;) // <==> while(true)
        {
            long long sum_of_prime_factors = get_sum_of_prime_factors(n);

            if (n == sum_of_prime_factors)
                break;

            n = sum_of_prime_factors;
        }

        return n;
    }

private:
    long long get_sum_of_prime_factors(int number)
    {
        long long result = 0LL;

        int factor = 2;
        while (number > 1)
        {
            if (number % factor == 0) 
            {
                result += factor;
                number = number / factor;
            }
            else
            {
                ++factor;
            }
        }

        return result;
    }
};
