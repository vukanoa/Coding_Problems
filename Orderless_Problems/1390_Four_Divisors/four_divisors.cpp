/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1390) Four Divisors
    ===========================

    ============
    Description:
    ============

    Given an integer array nums, return the sum of divisors of the integers in
    that array that have exactly four divisors. If there is no such integer in
    the array, return 0.

    =================================================
    FUNCTION: int sumFourDivisors(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [21,4,7]
    Output: 32
    Explanation: 
    21 has 4 divisors: 1, 3, 7, 21
    4 has 3 divisors: 1, 2, 4
    7 has 2 divisors: 1, 7
    The answer is the sum of divisors of 21 only.

    --- Example 2 ---
    Input: nums = [21,21]
    Output: 64

    --- Example 3 ---
    Input: nums = [1,2,3,4,5]
    Output: 0


    *** Constraints ***
    1 <= nums.length <= 10^4
    1 <= nums[i] <= 10^5

*/

#include <vector>
#include <bitset>
#include <cmath>
#include <cstring>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 92.20% */
/* Space Beats: 28.54% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(M) */ // M <==> Maximum value of a number
class Solution {
private:
    static constexpr int MAX_PRIME = 316;
    // const int MAX_PRIME = 316;

    bitset<MAX_PRIME + 1> is_prime = 0;
    vector<int> prime_numbers;
    int sum_of_div4[100001];

public:
    int sumFourDivisors(vector<int>& nums)
    {
        Sieve();

        int total_sum = 0;
        for (const int& num : nums)
            total_sum += sum_four_divisors_of_number(num);

        return total_sum;
    }

private:
    // Precompute primes and initialize divisor array
    void Sieve()
    {
        if (is_prime[2])
            return;

        is_prime.set();
        memset(sum_of_div4, -1, sizeof(sum_of_div4));

        is_prime[0] = is_prime[1] = 0;
        sum_of_div4[0] = sum_of_div4[1] = 0;

        const int sqrt_limit = static_cast<int>(sqrt(MAX_PRIME - 1));

        // Sieve of Eratosthenes, step 2 for odd numbers
        for (int p = 2; p <= sqrt_limit; p += 1 + (p & 1))
        {
            if (is_prime[p])
            {
                sum_of_div4[p] = 0; // prime has only 2 divisors
                prime_numbers.push_back(p);

                for (int multiple = p * p; multiple < MAX_PRIME; multiple += p)
                    is_prime[multiple] = 0;
            }
        }

        // Add remaining primes after sqrt_limit
        for (int num = sqrt_limit + ((sqrt_limit & 1) == 0); num < MAX_PRIME; num += 2)
        {
            if (is_prime[num])
                prime_numbers.push_back(num);
        }
    }

    // Compute sum of divisors for numbers with exactly 4 divisors
    int sum_four_divisors_of_number(int number)
    {
        if (sum_of_div4[number] != -1) // Memoization
            return sum_of_div4[number];

        int remaining = number;
        int sum_divisors = 1 + number;
        int prime_factor_count = 0;
        const int sqrt_of_number = static_cast<int>(sqrt(number));

        for (const int& curr_prime : prime_numbers)
        {
            if (curr_prime > sqrt_of_number)
                break;

            if (remaining % curr_prime != 0)
                continue;

            int exponent = 0;
            while (remaining % curr_prime == 0)
            {
                remaining /= curr_prime;
                exponent++;
            }

            prime_factor_count++;

            if (exponent == 3 && remaining == 1 && prime_factor_count == 1)
                return sum_of_div4[number] = 1 + curr_prime +
                                                 curr_prime * curr_prime +
                                                 curr_prime * curr_prime * curr_prime;

            if (exponent > 1 || prime_factor_count > 2)
                return sum_of_div4[number] = 0;

            sum_divisors += curr_prime;
        }

        if (remaining > 1)
        {
            prime_factor_count++;
            sum_divisors += remaining;
        }

        return sum_of_div4[number] = (prime_factor_count == 2) ? sum_divisors : 0;
    }
};
