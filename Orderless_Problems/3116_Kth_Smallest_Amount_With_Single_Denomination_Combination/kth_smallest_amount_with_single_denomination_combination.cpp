/*
    ============
    === HARD ===
    ============

    ==============================================================
    3116) Kth Smallest Amount With Single Denomination Combination
    ==============================================================

    ============
    Description:
    ============

    You are given an integer array coins representing coins of different
    denominations and an integer k.

    You have an infinite number of coins of each denomination. However, you are
    not allowed to combine coins of different denominations.

    Return the kth smallest amount that can be made using these coins.

    ===============================================================
    FUNCTION: long long findKthSmallest(vector<int>& coins, int k);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: coins = [3,6,9], k = 3
    Output: 9
    Explanation: The given coins can make the following amounts:
    Coin 3 produces multiples of 3: 3, 6, 9, 12, 15, etc.
    Coin 6 produces multiples of 6: 6, 12, 18, 24, etc.
    Coin 9 produces multiples of 9: 9, 18, 27, 36, etc.
    All of the coins combined produce: 3, 6, 9, 12, 15, etc.

    --- Example 2 ---
    Input: coins = [5,2], k = 7
    Output: 12
    Explanation: The given coins can make the following amounts:
    Coin 5 produces multiples of 5: 5, 10, 15, 20, etc.
    Coin 2 produces multiples of 2: 2, 4, 6, 8, 10, 12, etc.
    All of the coins combined produce: 2, 4, 5, 6, 8, 10, 12, 14, 15, etc.


    *** Constraints ***
    1 <= coins.length <= 15
    1 <= coins[i] <= 25
    1 <= k <= 2 * 10^9
    coins contains pairwise distinct integers.

*/

#include <cstdint>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 48.98% */
/* Space Beats: 32.65% */

/* Time  Complexity: O(2^N * N * logM) */
/* Space Complexity: O(2^N * N * logM) */
class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k)
    {
        return binary_search(coins, k);
    }

private:
    int64_t gcd(int64_t a, int64_t b)
    {
        return (b == 0 ? a : gcd(b, a % b));
    }

    int64_t lcm(int64_t a, int64_t b)
    {
        return a / gcd(a, b) * b;
    }

    // Count the numbers of integers smaller or equal to x
    // without duplicates.
    int64_t count(vector<int>& coins, int64_t x)
    {
        int size = coins.size();
        int64_t sum = 0;

        for (int mask = 1; mask < (1 << size); mask++)
        {
            // number of bits set on
            int bits = __builtin_popcountll(mask);
            int64_t least_common_multiple = 1;

            for (int j = 0; j < size; j++)
            {
                if (mask & (1 << j))
                    least_common_multiple = lcm(least_common_multiple, coins[j]); // Get the lcm for the subset
            }

            if (bits & 1) // IF it is odd add OTHERWISE subtract
                sum += x / least_common_multiple;
            else
                sum -= x / least_common_multiple;
        }

        return sum;
    }

    int64_t binary_search(vector<int>& coins, int64_t k)
    {
        int64_t left  = 1;
        int64_t right = 25LL * 2e9;

        while (left < right)
        {
            int64_t mid = left + (right - left) / 2;

            if (count(coins, mid) < k)
                left = mid + 1;
            else
                right = mid;
        }

        return left;
    }
};
