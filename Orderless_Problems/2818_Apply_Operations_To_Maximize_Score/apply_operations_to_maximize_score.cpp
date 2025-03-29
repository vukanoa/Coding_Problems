/*
    ============
    === HARD ===
    ============

    ========================================
    2818) Apply Operations to Maximize Score
    ========================================

    ============
    Description:
    ============

    You are given an array nums of n positive integers and an integer k.

    Initially, you start with a score of 1. You have to maximize your score by
    applying the following operation at most k times:

        + Choose any non-empty subarray nums[l, ..., r] that you haven't chosen
          previously.

        + Choose an element x of nums[l, ..., r] with the highest prime score.
          If multiple such elements exist, choose the one with the smallest
          index.

        + Multiply your score by x.

    Here, nums[l, ..., r] denotes the subarray of nums starting at index l and
    ending at the index r, both ends being inclusive.

    The prime score of an integer x is equal to the number of distinct prime
    factors of x. For example, the prime score of 300 is 3 since:

        300 = 2 * 2 * 3 * 5 * 5.

    Return the maximum possible score after applying at most k operations.

    Since the answer may be large, return it modulo 109 + 7.

    =====================================================
    FUNCTION: int maximumScore(vector<int>& nums, int k);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [8,3,9,3,8], k = 2
    Output: 81
    Explanation: To get a score of 81, we can apply the following operations:
    - Choose subarray nums[2, ..., 2]. nums[2] is the only element in this
      subarray. Hence, we multiply the score by nums[2]. The score becomes
      1 * 9 = 9.

    - Choose subarray nums[2, ..., 3]. Both nums[2] and nums[3] have a prime
      score of 1, but nums[2] has the smaller index. Hence, we multiply the
      score by nums[2]. The score becomes 9 * 9 = 81.

    It can be proven that 81 is the highest score one can obtain.


    --- Example 2 ---
    Input: nums = [19,12,14,6,10,18], k = 3
    Output: 4788
    Explanation: To get a score of 4788, we can apply the following operations:
    - Choose subarray nums[0, ..., 0]. nums[0] is the only element in this
       subarray. Hence, we multiply the score by nums[0]. The score becomes
       1 * 19 = 19.

    - Choose subarray nums[5, ..., 5]. nums[5] is the only element in this
      subarray. Hence, we multiply the score by nums[5]. The score becomes
      19 * 18 = 342.

    - Choose subarray nums[2, ..., 3]. Both nums[2] and nums[3] have a prime
      score of 2, but nums[2] has the smaller index. Hence, we multipy the
      score by nums[2]. The score becomes 342 * 14 = 4788.

    It can be proven that 4788 is the highest score one can obtain.



    *** Constraints ***
    1 <= nums.length == n <= 10^5
    1 <= nums[i] <= 10^5
    1 <= k <= min(n * (n + 1) / 2, 10^9)

*/

#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Don't even bother, it's too difficult. If someone asks this in an interview
    they likely don't expect you to solve it completely, but rather to see your
    process of thinking and understanding the problem.

*/

/* Time  Beats: 63.41% */
/* Space Beats: 70.73% */

/* Time  Complexity: O(N * (sqrt(m) + logN)) */
/* Space Complexity: O(N)                    */
class Solution {
private:
    const int MOD = 1e9 + 7;

public:
    int maximumScore(vector<int>& nums, int k)
    {
        const int N = nums.size();
        vector<int> prime_scores(N, 0);

        // Calculate the prime score for each number in nums
        for (int i = 0; i < N; i++)
        {
            int num = nums[i];

            // Check for prime factors from 2 to sqrt(n)
            for (int factor = 2; factor <= sqrt(num); factor++)
            {
                if (num % factor == 0)
                {
                    // Increment prime score for each prime factor
                    prime_scores[i]++;

                    // Remove all occurrences of the prime factor from num
                    while (num % factor == 0)
                        num /= factor;
                }
            }

            // If num is still greater than or equal to 2, it's a prime factor
            if (num >= 2)
                prime_scores[i]++;
        }

        // Initialize next and previous dominant index arrays
        vector<int> next_dominant(N, N);
        vector<int> prev_dominant(N, -1);

        // Stack to store indices for monotonic decreasing prime score
        stack<int> stack__decreasing_prime_score;

        // Calculate the next and previous dominant indices for each number
        for (int i = 0; i < N; i++)
        {
            // While the stack is not empty and the current prime score is
            // greater than the stack's top
            while ( ! stack__decreasing_prime_score.empty() && prime_scores[stack__decreasing_prime_score.top()] < prime_scores[i])
            {
                int topIndex = stack__decreasing_prime_score.top();
                stack__decreasing_prime_score.pop();

                // Set the next dominant element for the popped index
                next_dominant[topIndex] = i;
            }

            // If the stack is not empty, set the previous dominant element for
            // the current index
            if ( ! stack__decreasing_prime_score.empty())
                prev_dominant[i] = stack__decreasing_prime_score.top();

            // Push the current index onto the stack
            stack__decreasing_prime_score.push(i);
        }

        // Calculate the number of subarrays in which each element is dominant
        vector<long long> num_of_subarrays(N);
        for (int index = 0; index < N; index++)
            num_of_subarrays[index] = 1LL * (next_dominant[index] - index) * (index - prev_dominant[index]);

        // Priority queue to process elements in decreasing order of their value
        priority_queue<pair<int, int>> processing_queue;

        // Push each number and its index onto the priority queue
        for (int i = 0; i < N; i++)
            processing_queue.push({nums[i], i});

        long long score = 1;

        // Process elements while there are operations left
        while (k > 0)
        {
            // Get the element with the maximum value from the queue
            auto [num, index] = processing_queue.top();
            processing_queue.pop();

            // Calculate the number of operations to apply on the current elem
            long long operations = min((long long)k, num_of_subarrays[index]);

            // Update the score by raising the elem to the power of operations
            score = (score * power(num, operations)) % MOD;

            // Reduce the remaining operations count
            k -= operations;
        }

        return score;
    }

private:
    // Helper function to compute the power of a number modulo MOD
    long long power(long long base, long long exponent)
    {
        long long result = 1;

        // Calculate the exponentiation using binary exponentiation
        while (exponent > 0)
        {
            // If the exponent is odd, multiply the result by the base
            if (exponent % 2 == 1)
                result = ((result * base) % MOD);

            // Square the base and halve the exponent
            base = (base * base) % MOD;
            exponent /= 2;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one uses "Sieve of Eratosthenes". If you've never heard of it, check
    it out. It's a fundamental technique for "prime" Problems.

*/

/* Time  Beats: 46.95% */
/* Space Beats: 48.17% */

/* Time  Complexity: O(N * (logM + logN) + M * loglogM) */
/* Space Complexity: O(max(N, M))                       */
class Solution_Sieve_of_Eratosthenes {
private:
    const int MOD = 1e9 + 7;

public:
    int maximumScore(vector<int>& nums, int k)
    {
        const int N = nums.size();
        vector<int> prime_scores(N, 0);

        // Find the maximum element in nums to determine the range for prime
        // generation
        int max_element = 0;
        for (int i = 0; i < N; i++)
            max_element = max(max_element, nums[i]);

        // Get all prime numbers up to max_element using the Sieve of Eratost.
        vector<int> primes = getPrimes(max_element);

        // Calculate the prime score for each number in nums
        for (int i = 0; i < N; i++)
        {
            int num = nums[i];

            // Iterate over the generated primes to count unique prime factors
            for (int prime : primes)
            {
                if (prime * prime > num)
                    break;  // Stop early if prime^2 exceeds num

                if (num % prime != 0)
                    continue;  // Skip if the prime is not a factor

                prime_scores[i]++;  // Increment prime score for the factor

                while (num % prime == 0)
                    num /= prime;  // Remove all occurrences of this factor
            }

            // If num is still greater than 1, it is a prime number itself
            if (num > 1)
                prime_scores[i]++;
        }

        // Initialize next and previous dominant index arrays
        vector<int> next_dominant(N, N);
        vector<int> prev_dominant(N, -1);

        // Stack to store indices for a monotonic decreasing prime score
        stack<int> stack__decreasing_prime_score;

        // Calculate the next and previous dominant indices for each number
        for (int i = 0; i < N; i++)
        {
            // While the stack is not empty and the current prime score is
            // greater than the stack's top, update nextDominant
            while ( ! stack__decreasing_prime_score.empty() && prime_scores[stack__decreasing_prime_score.top()] < prime_scores[i])
            {
                int top_idx = stack__decreasing_prime_score.top();
                stack__decreasing_prime_score.pop();

                // Set the next dominant element for the popped index
                next_dominant[top_idx] = i;
            }

            // If the stack is not empty, set the previous dominant element for
            // the current index
            if ( ! stack__decreasing_prime_score.empty())
                prev_dominant[i] = stack__decreasing_prime_score.top();

            // Push the current index onto the stack
            stack__decreasing_prime_score.push(i);
        }

        // Calculate the number of subarrays in which each element is dominant
        vector<long long> num_of_subarrays(N);
        for (int i = 0; i < N; i++)
            num_of_subarrays[i] = 1LL * (next_dominant[i] - i) * (i - prev_dominant[i]);

        // Sort elements in decreasing order based on their values
        vector<pair<int, int>> sorted_array(N);

        for (int i = 0; i < N; i++)
            sorted_array[i] = {nums[i], i};

        sort(sorted_array.begin(), sorted_array.end(), greater<>());

        long long score = 1;
        int processing_idx = 0;

        // Process elements while there are operations left
        while (k > 0)
        {
            // Get the element with the maximum value
            auto [num, index] = sorted_array[processing_idx++];

            // Calculate the number of operations to apply on the current
            // element
            long long operations = min((long long)k, num_of_subarrays[index]);

            // Update the score by raising the element to the power of
            // operations
            score = (score * power(num, operations)) % MOD;

            // Reduce the remaining operations count
            k -= operations;
        }

        return score;
    }

private:
    // Helper function to compute the power of a number modulo MOD
    long long power(long long base, long long exponent)
    {
        long long result = 1;

        // Calculate the exponentiation using binary exponentiation
        while (exponent > 0)
        {
            // If the exponent is odd, multiply the result by the base
            if (exponent % 2 == 1)
                result = ((result * base) % MOD);

            // Square the base and halve the exponent
            base = (base * base) % MOD;
            exponent /= 2;
        }

        return result;
    }

    // Function to generate prime numbers up to a given limit using the Sieve
    // of Eratosthenes
    vector<int> getPrimes(int limit)
    {
        vector<bool> is_prime(limit + 1, true);
        vector<int> primes;

        // Start marking from the first prime number (2)
        for (int num = 2; num <= limit; num++)
        {
            if ( ! is_prime[num]) continue;

            // Store the prime number
            primes.push_back(num);

            // Mark multiples of the prime number as non-prime
            for (long long multiple = 1LL * num * num; multiple <= limit; multiple += num)
                is_prime[multiple] = false;
        }

        return primes;
    }
};
