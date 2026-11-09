/*
    ==============
    === MEDIUM ===
    ==============

    ============================================================
    4032) Longest Subarray With at Most K Distinct Prime Factors
    ============================================================

    ============
    Description:
    ============

    You are given an integer array nums consisting of positive integers and an
    integer k.

    The prime factor set of a subarray is the union of the distinct prime
    factors of all its elements.

    Return the length of the longest subarray whose prime factor set contains
    at most k distinct prime factors. If no such subarray exists, return 0.

    ========================================================
    FUNCTION: int longestSubarray(vector<int>& nums, int k);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [7,6,10,12,11], k = 3
    Output: 3
    Explanation:
    Consider the subarray [6, 10, 12]:
        The distinct prime factors of 6 are {2, 3}.
        The distinct prime factors of 10 are {2, 5}.
        The distinct prime factors of 12 are {2, 3}.
        The union of these sets is {2, 3, 5}, which contains 3 distinct prime factors.
    No longer subarray satisfies the condition. Therefore, the answer is 3.


    --- Example 2 ---
    Input: nums = [4,6,9,18], k = 4
    Output: 4
    Explanation:
    Consider the entire array [4, 6, 9, 18]:
        The distinct prime factors of 4 are {2}.
        The distinct prime factors of 6 are {2, 3}.
        The distinct prime factors of 9 are {3}.
        The distinct prime factors of 18 are {2, 3}.
        The union of these sets is {2, 3}, which contains 2 distinct prime factors.
    Since 2 <= 4, the entire array is valid. Therefore, the answer is 4.


    --- Example 3 ---
    Input: nums = [6,10,15], k = 2
    Output: 1
    Explanation:
    Every subarray of length at least 2 has prime factor set {2, 3, 5}, which contains 3 distinct prime factors.
    Since 3 > 2, only subarrays of length 1 are valid. Therefore, the answer is 1.


    *** Constraints ***
    1 <= nums.length <= 10^5
    2 <= nums[i] <= 10^5
    1 <= k <= 10^4

*/

#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 30.38% */
/* Space Beats: 31.94% */

// U --> Unique numbers in nums
// P --> Average DISTINCT prime factors per number

/* Time  Complexity: O(N * sqrt(M)  +  N*P  +  FINAL_NUM * loglogFINAL_NUM) */
/* Space Complexity: O(FINAL_NUM  +  U * P)                                 */
class Solution {
private:
    const int FINAL_NUM = 1e5;
    vector<bool> is_prime;

public:
    int longestSubarray(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int result = 0;

        /* Initialize */
        initialize_sieve_of_eratosthenes();

        unordered_map<int, unordered_set<int>> prime_factor_set_of;
        for (const int& num : nums)
        {
            if (prime_factor_set_of.count(num))
                continue;

            prime_factor_set_of[num] = get_all_prime_factors_of_number(num);
        }

        unordered_map<int,int> freq;

        int left  = 0;
        int right = 0;
        while (right < N)
        {
            for (const int& factor : prime_factor_set_of[nums[right]])
            {
                ++freq[factor];
            }

            /* Slide Window */
            while (freq.size() > k)
            {
                for (const int& factor : prime_factor_set_of[nums[left]])
                {
                    --freq[factor];

                    if (freq[factor] == 0)
                        freq.erase(factor);
                }

                ++left;
            }

            result = max(result, right - left + 1);

            // Increment
            ++right;
        }

        return result;
    }

private:
    // TC: O(N * log(logN))
    void initialize_sieve_of_eratosthenes()
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

    unordered_set<int> get_all_prime_factors_of_number(int number)
    {
        unordered_set<int> uset;

        for (int f = 2; f * f <= number; f++)
        {
            if (number % f != 0)
                continue;

            if (is_prime[f])
                uset.insert(f);

            if (is_prime[number / f])
                uset.insert(number / f);
        }

        if (is_prime[number]) // The number itself (if it's a prime)
            uset.insert(number);

        return uset;
    }
};
