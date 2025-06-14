/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    313) Super Ugly Number
    ===========================

    ============
    Description:
    ============

    A super ugly number is a positive integer whose prime factors are in the
    array primes.

    Given an integer n and an array of integers primes, return the nth super
    ugly number.

    The nth super ugly number is guaranteed to fit in a 32-bit signed integer.

    =============================================================
    FUNCTION: int nthSuperUglyNumber(int n, vector<int>& primes);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 12, primes = [2,7,13,19]
    Output: 32
    Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first
                 12 super ugly numbers given primes = [2,7,13,19]

    --- Example 2 ---
    Input: n = 1, primes = [2,3,5]
    Output: 1
    Explanation: 1 has no prime factors, therefore all of its prime factors are
                 in the array primes = [2,3,5].


    *** Constraints ***
    1 <= n <= 10^5
    1 <= primes.length <= 100
    2 <= primes[i] <= 1000
    primes[i] is guaranteed to be a prime number.
    All the values of primes are unique and sorted in ascending order.

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 59.10% */
/* Space Beats: 33.02% */

// Where nn is the desired index and kk is the number of primes.
/* Time  Complexity: O(N * logK) */
/* Space Complexity: O(N + K)    */
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int> &primes)
    {
        using Entry = tuple<long long, int, int>; // {value, prime, index}
        auto compare = [](const Entry &a, const Entry &b)
        {
            return get<0>(a) > get<0>(b);
        };
        priority_queue<Entry, vector<Entry>, decltype(compare)> min_heap(compare);

        for (int prime : primes)
        {
            min_heap.emplace(prime, prime, 0);
        }

        vector<int> nums(n + 1);
        nums[0] = 1;

        int i = 1;
        while (i < n)
        {
            auto [value, prime, index] = min_heap.top();
            min_heap.pop();

            if (value != nums[i - 1])
            {
                nums[i] = value;
                i++;
            }

            min_heap.emplace(1LL * prime * nums[index + 1], prime, index + 1);
        }

        return nums[n - 1];
    }
};
