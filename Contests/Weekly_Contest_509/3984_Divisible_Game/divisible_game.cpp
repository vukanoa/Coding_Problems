/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3984) Divisible Game
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    Alice and Bob are playing a game. Alice chooses:

        + An integer k such that k > 1.
        + Two integers l and r such that 0 <= l <= r < n.

    Initially, both Alice's and Bob's scores are 0.

    For each index i in the range [l, r] (inclusive):

        + If nums[i] is divisible by k, Alice's score increases by nums[i].
        + Otherwise, Bob's score increases by nums[i].

    The score difference is Alice's score minus Bob's score.

    Alice wants to maximize the score difference. If there are multiple values
    of k that achieve the maximum score difference, she chooses the smallest
    such k.

    Return the product of the maximum score difference and the chosen value of
    k. Since the result can be large, return it modulo 109 + 7.

    ===============================================
    FUNCTION: int divisibleGame(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,4,6,8]
    Output: 36
    Explanation:
        Alice can choose k = 2, l = 1, and r = 3.
        + All values in nums[1..3] are divisible by 2, so Alice's score is 4 + 6
          + 8 = 18, while Bob's score is 0.

        + The score difference is 18, which is the maximum possible. Among all
          values of k that achieve this score difference, the smallest is 2.

        + Therefore, the answer is 18 * 2 = 36.


    --- Example 2 ---
    Input: nums = [2,1,2]
    Output: 6
    Explanation:
        + Alice can choose k = 2, l = 0, and r = 2.

        + The values nums[0] and nums[2] are divisible by 2, so Alice's score
          is 2 + 2 = 4. The value nums[1] is not divisible by 2, so Bob's score
          is 1.

        + The score difference is 4 - 1 = 3, which is the maximum possible.
          Among all values of k that achieve this score difference, the
          smallest is 2.

        + Therefore, the answer is 3 * 2 = 6.


    --- Example 3 ---
    Input: nums = [1]
    Output: 1000000005
    Explanation:
        + Alice must choose some k > 1. The smallest possible choice is k = 2.

        + Since nums[0] is not divisible by 2, Alice's score is 0, while Bob's
          score is 1.

        + The score difference is -1, which is the maximum possible.

        + Therefore, the answer is -1 * 2 = -2. Modulo 109 + 7, this equals
          1000000005.


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 10^6

*/

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Sieve of Eratosthenes + Factorization + Kadane's Algorithm.

*/

/* Time  Complexity: O(MAX_PRIME log(log(MAX_PRIME)) + N * pi(sqrt(MAX_PRIME)) + K log K + K * N) */
/* Space Complexity: O(K)                                                                         */
class Solution {
private:
    static constexpr int MAX_PRIME = 1000;
    static constexpr int MOD = 1e9 + 7;

    static vector<bool> prime_sieve;
    static vector<int> primes;

    vector<int> prime_divisors;

    struct SieveInit {
        SieveInit()
        {
            if ( ! prime_sieve.empty())
                return;

            prime_sieve.assign(MAX_PRIME + 1, true);

            prime_sieve[0] = false;
            prime_sieve[1] = false;

            for (int num = 2; num * num <= MAX_PRIME; num++)
            {
                if ( ! prime_sieve[num])
                    continue;

                for (int multiple = num * num; multiple <= MAX_PRIME; multiple += num)
                    prime_sieve[multiple] = false;
            }

            for (int num = 2; num <= MAX_PRIME; num++)
            {
                if (prime_sieve[num])
                    primes.push_back(num);
            }
        }
    };

    static SieveInit sieve_init;

    void factorize_number(int number)
    {
        if (number <= MAX_PRIME && prime_sieve[number])
        {
            prime_divisors.push_back(number);
            return;
        }

        int remaining = number;

        for (const int& prime : primes)
        {
            if (prime * prime > remaining)
                break;

            if (remaining % prime != 0)
                continue;

            prime_divisors.push_back(prime);

            while (remaining % prime == 0)
                remaining /= prime;
        }

        if (remaining > 1)
            prime_divisors.push_back(remaining);
    }

    long long kadane(vector<int>& nums, int prime)
    {
        long long best_subarray_sum = LLONG_MIN;
        long long curr_subarray_sum = 0;

        for (const int& num : nums)
        {
            int value = (num % prime == 0) ? num : -num;

            curr_subarray_sum = max(      1LL * value, curr_subarray_sum + value);
            best_subarray_sum = max(best_subarray_sum, curr_subarray_sum        );
        }

        return best_subarray_sum;
    }

public:
    int divisibleGame(vector<int>& nums)
    {
        for (const int& num : nums)
            factorize_number(num);

        if (prime_divisors.empty())
            prime_divisors.push_back(2);

        /* Sort */
        sort(prime_divisors.begin(), prime_divisors.end());

        prime_divisors.erase(
            unique(prime_divisors.begin(), prime_divisors.end()),
            prime_divisors.end()
        );

        long long best_score = LLONG_MIN;
        int best_prime = INT_MAX;

        for (const int& prime : prime_divisors)
        {
            long long curr_score = kadane(nums, prime);

            if (curr_score > best_score)
            {
                best_score = curr_score;
                best_prime = prime;
            }
        }

        long long result = (best_score * best_prime) % MOD;

        return result < 0 ? result + MOD : result;
    }
};
