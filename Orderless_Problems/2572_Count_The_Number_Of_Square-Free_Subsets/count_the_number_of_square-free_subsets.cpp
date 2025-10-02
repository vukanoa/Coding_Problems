/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    2572) Count the Number of Square-Free Subsets
    =============================================

    ============
    Description:
    ============

    You are given a positive integer 0-indexed array nums.

    A subset of the array nums is square-free if the product of its elements is
    a square-free integer.

    A square-free integer is an integer that is divisible by no square number
    other than 1.

    Return the number of square-free non-empty subsets of the array nums.
    Since the answer may be too large, return it modulo 109 + 7.

    A non-empty subset of nums is an array that can be obtained by deleting
    some (possibly none but not all) elements from nums. Two subsets are
    different if and only if the chosen indices to delete are different.

    ===================================================
    FUNCTION: int squareFreeSubsets(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,4,4,5]
    Output: 3
    Explanation: There are 3 square-free subsets in this example:
    - The subset consisting of the 0th element [3]. The product of its elements is 3, which is a square-free integer.
    - The subset consisting of the 3rd element [5]. The product of its elements is 5, which is a square-free integer.
    - The subset consisting of 0th and 3rd elements [3,5]. The product of its elements is 15, which is a square-free integer.
    It can be proven that there are no more than 3 square-free subsets in the given array.

    --- Example 2 ---
    Input: nums = [1]
    Output: 1
    Explanation: There is 1 square-free subset in this example:
    - The subset consisting of the 0th element [1]. The product of its elements is 1, which is a square-free integer.
    It can be proven that there is no more than 1 square-free subset in the given array.


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 30

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 20.09% */
/* Space Beats: 40.64% */

/* Time  Complexity: O(N * 2^P) -->  O(N * 1024) */
/* Space Complexity: O(N * 2^P) -->  O(N * 1024) */
class Solution_Memoization {
private:
    long long memo[1111][1 << 11];
    const int MOD = 1e9 + 7;

    const int PRIMES_COUNT = 10; // There are 10 primes <= 30
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

public:
    int squareFreeSubsets(vector<int>& nums)
    {
        /* Memset */
        memset(memo, -1, sizeof memo);

        // -1 because of the case when we have not taken any number
        return (solve(0, 1, nums) - 1 + MOD) % MOD;
    }

private:
    long long get_mask(long long number)
    {
        long long mask = 0;

        for (int i = 0; i < PRIMES_COUNT; i++)
        {
            int time = 0;
            while (number % primes[i] == 0)
            {
                time++;
                number /= primes[i];
            }

            if (time > 1) 
                return -1; 

            if (time == 1) 
                mask |= (1 << (i + 1));
        }

        return mask;
    }

    long long solve(int idx, long long product_mask, vector<int> &nums)
    {
        const int N = nums.size();
        if (idx >= N)
            return 1;

        if (memo[idx][product_mask] != -1)
            return memo[idx][product_mask];
        
        long long mask   = get_mask(nums[idx]);
        long long result = solve(idx + 1, product_mask, nums);
        
        if ((product_mask & mask) == 0)
            result = (result + solve(idx + 1, product_mask | mask, nums)) % MOD;

        return memo[idx][product_mask] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 70.78% */
/* Space Beats:  9.13% */

/* Time  Complexity: O(N * 2^P) -->  O(N * 1024) */
/* Space Complexity: O(N * 2^P) -->  O(N * 1024) */
class Solution_Bottom_Up {
public:
    int squareFreeSubsets(vector<int>& nums)
    {
        const int N = nums.size(); 
        const int MOD = 1e9 + 7; 

        vector<int> mask(31, -1);
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}; 

        // Precompute mask for each number up to 30
        for (int number = 1; number <= 30; number++)
        {
            int prime_mask = 0;
            int prime_product = 1; 

            for (int prime_index = 0; prime_index < 10; ++prime_index) 
            {
                if (number % primes[prime_index] == 0)
                {
                    prime_product *= primes[prime_index];
                    prime_mask ^= 1 << prime_index; 
                }
            }

            if (prime_product == number) 
                mask[number] = prime_mask; 
        }

        vector<vector<long long>> dp(N + 1, vector<long long>(1 << 10)); 

        // Base case: empty subset
        for (int mask = 0; mask < (1 << 10); mask++)
            dp[N][mask] = 1; 

        for (int index = N-1; index >= 0; index--)
        {
            int current_number_mask = mask[nums[index]]; 

            for (int mask = 0; mask < (1 << 10); mask++)
            {
                // Skip
                dp[index][mask] = dp[index + 1][mask]; 

                // Take, if square-free and no conflict
                if (current_number_mask >= 0 && (mask & current_number_mask) == 0)
                {
                    dp[index][mask] = (dp[index][mask] + dp[index + 1][mask ^ current_number_mask]) % MOD; 
                }
            }
        }

        return (dp[0][0] - 1 + MOD) % MOD; 
    }
};
