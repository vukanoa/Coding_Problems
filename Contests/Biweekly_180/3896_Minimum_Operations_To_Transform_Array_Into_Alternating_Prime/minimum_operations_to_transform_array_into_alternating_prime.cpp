/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================================
    3896) Minimum Operations to Transform Array into Alternating Prime
    ==================================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    An array is considered alternating prime if:

        + Elements at even indices (0-based) are prime numbers.
        + Elements at odd indices are non-prime numbers.

    In one operation, you may increment any element by 1.

    Return the minimum number of operations required to transform nums into an
    alternating prime array.

    A prime number is a natural number greater than 1 with only two factors, 1
    and itself.

    ===============================================
    FUNCTION: int minOperations(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4]
    Output: 3
    Explanation:
        The element at index 0 must be prime. Increment nums[0] = 1 to 2, using 1 operation.
        The element at index 1 must be non-prime. Increment nums[1] = 2 to 4, using 2 operations.
        The element at index 2 is already prime.
        The element at index 3 is already non-prime.
    Total operations = 1 + 2 = 3.

    --- Example 2 ---
    Input: nums = [5,6,7,8]
    Output: 0
    Explanation:
        The elements at indices 0 and 2 are already prime.
        The elements at indices 1 and 3 are already non-prime.
    No operations are needed.

    --- Example 3 ---
    Input: nums = [4,4]
    Output: 1
    Explanation:
        The element at index 0 must be prime. Increment nums[0] = 4 to 5, using 1 operation.
        The element at index 1 is already non-prime.
    Total operations = 1.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 20.20% */
/* Space Beats: 24.79% */

/* Time  Complexity: O(MAX_NUM * loglogMAX_NUM  +  N * logMAX_NUM) */
/* Space Complexity: O(MAX_NUM)                                    */
class Solution {
private:
    class Sieve {
    private:
        const int MAX_NUM = 1e5 + 100;

    public:
        vector<bool> prime;

        Sieve()
        {
            prime.assign(MAX_NUM + 1, true);
            prime[0] = prime[1] = false;

            for (int i = 2; i * i <= MAX_NUM; i++)
            {
                if ( ! prime[i])
                    continue;

                for (int j = i * i; j <= MAX_NUM; j += i)
                    prime[j] = false;
            }
        }
    };

public:
    int minOperations(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        Sieve sieve;

        vector<int> primes;
        vector<int> non_primes;

        primes.reserve(1e5 + 100);
        non_primes.reserve(1e5 + 100);

        for (unsigned num = 0; num < sieve.prime.size(); num++)
        {
            if (sieve.prime[num])
                primes.push_back(num);
            else
                non_primes.push_back(num);
        }

        for (int i = 0; i < N; i++)
        {
            if (i & 1) // Index 'i' is ODD
            {
                if ( ! sieve.prime[nums[i]]) // It's already NOT a prime
                    continue;

                auto it = upper_bound(non_primes.begin(), non_primes.end(), nums[i]);

                result += *it - nums[i];
            }
            else // Index 'i' is EVEN
            {
                if (sieve.prime[nums[i]]) // It's already a PRIME
                    continue;

                auto it = upper_bound(primes.begin(), primes.end(), nums[i]);

                result += *it - nums[i];
            }
        }

        return result;
    }
};



/* Time  Complexity: O(MAX_NUM * loglogMAX_NUM  +  N) */
/* Space Complexity: O(MAX_NUM)                        */
class Solution_2 {
private:
    static const int MAX_NUM = 1e5 + 100;
    bool sieve[MAX_NUM];

    void create_sieve()
    {
        sieve[0] = sieve[1] = true;

        for (int i = 2; i * i <= MAX_NUM; i++)
        {
            if (sieve[i])
                continue;

            for (int j = i * i; j < MAX_NUM; j += i)
                sieve[j] = true;
        }
    }

public:
    int minOperations(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        create_sieve();

        for (int i = 0; i < N; i++)
        {
            int num = nums[i];

            if (i & 1) // Index 'i' is ODD
            {
                while ( ! sieve[num])
                {
                    ++num;
                    ++result;
                }
            }
            else // Index 'i' is EVEN
            {
                while (sieve[num])
                {
                    ++num;
                    ++result;
                }
            }
        }

        return result;
    }
};
