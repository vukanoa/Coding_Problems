/*
    ============
    === EASY ===
    ============

    ==============================================
    3591) Check if Any Element Has Prime Frequency
    ==============================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Return true if the frequency of any element of the array is prime,
    otherwise, return false.

    The frequency of an element x is the number of times it occurs in the
    array.

    A prime number is a natural number greater than 1 with only two factors, 1
    and itself.

    ======================================================
    FUNCTION: bool checkPrimeFrequency(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,5,4]
    Output: true
    Explanation:
    4 has a frequency of two, which is a prime number.

    --- Example 2 ---
    Input: nums = [1,2,3,4,5]
    Output: false
    Explanation:
    All elements have a frequency of one.

    --- Example 3 ---
    Input: nums = [2,2,2,4,4]
    Output: true
    Explanation:
    Both 2 and 4 have a prime frequency.


    *** Constraints ***
    1 <= nums.length <= 100
    0 <= nums[i] <= 100

*/

#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Generate all of the primes in first 100 numbers using Sieve of Eratosthenes
    (100 because that is the Constraint of this problem)

    Then, put all of the primes in a Set.
    Then, get frequencies of elements in nums by creating a HashMap.

    Simply go through the HashMap and check if any of the frequencies is
    present in our Set of primes.

*/

/* Time  Beats: 8.63% */
/* Space Beats: 5.76% */

/* Time  Complexity: O(N + sqrt(M) + M * loglogM) */
/* Space Complexity: O(M)                         */
class Solution {
public:
    bool checkPrimeFrequency(vector<int>& nums)
    {
        const int N = nums.size();

        int final_num = 100;
        vector<bool> prime(final_num + 1, true);

        prime[0] = false;  // 0 is not prime
        prime[1] = false;  // 1 is not prime

        // Sieve of Eratosthenes: O(N * log(log N))
        for (int num = 2; num * num <= final_num; num++)
        {
            if ( ! prime[num])
                continue;

            for (int i = num * num; i <= final_num; i += num)
                prime[i] = false;
        }

        unordered_set<int> uset_primes;
        for (int i = 0; i <= 100; i++)
        {
            if (prime[i])
                uset_primes.insert(i);
        }

        unordered_map<int,int> umap;
        for (int i = 0; i < N; i++)
            umap[nums[i]]++;

        for (const auto& [num, freq] : umap)
        {
            if (freq > 1 && uset_primes.find(freq) != uset_primes.end())
                return true;
        }

        return false;
    }
};
