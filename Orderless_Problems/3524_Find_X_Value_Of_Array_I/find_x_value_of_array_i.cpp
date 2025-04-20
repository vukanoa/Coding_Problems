/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    3524) Find X Value of Array I
    =============================

    ============
    Description:
    ============

    You are given an array of positive integers nums, and a positive integer k.

    You are allowed to perform an operation once on nums, where in each
    operation you can remove any non-overlapping prefix and suffix from nums
    such that nums remains non-empty.

    You need to find the x-value of nums, which is the number of ways to
    perform this operation so that the product of the remaining elements leaves
    a remainder of x when divided by k.

    Return an array result of size k where result[x] is the x-value of nums for
    0 <= x <= k - 1.

    A prefix of an array is a

    that starts from the beginning of the array and extends to any point within
    it.

    A suffix of an array is a

    that starts at any point within the array and extends to the end of the array.

    =====
    Note: that the prefix and suffix to be chosen for the operation can be empty
    =====

    ==================================================================
    FUNCTION: vector<long long> resultArray(vector<int>& nums, int k);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,5], k = 3
    Output: [9,2,4]
    Explanation:
        For x = 0, the possible operations include all possible ways to remove
                   non-overlapping prefix/suffix that do not remove nums[2] == 3.
        For x = 1, the possible operations are:
            Remove the empty prefix and the suffix [2, 3, 4, 5]. nums becomes [1].
            Remove the prefix [1, 2, 3] and the suffix [5]. nums becomes [4].
        For x = 2, the possible operations are:
            Remove the empty prefix and the suffix [3, 4, 5]. nums becomes [1, 2].
            Remove the prefix [1] and the suffix [3, 4, 5]. nums becomes [2].
            Remove the prefix [1, 2, 3] and the empty suffix. nums becomes [4, 5].
            Remove the prefix [1, 2, 3, 4] and the empty suffix. nums becomes [5].


    --- Example 2 ---
    Input: nums = [1,2,4,8,16,32], k = 4
    Output: [18,1,2,0]
    Explanation:
        For x = 0, the only operations that do not result in x = 0 are:
            Remove the empty prefix and the suffix [4, 8, 16, 32]. nums becomes [1, 2].
            Remove the empty prefix and the suffix [2, 4, 8, 16, 32]. nums becomes [1].
            Remove the prefix [1] and the suffix [4, 8, 16, 32]. nums becomes [2].
        For x = 1, the only possible operation is:
            Remove the empty prefix and the suffix [2, 4, 8, 16, 32]. nums becomes [1].
        For x = 2, the possible operations are:
            Remove the empty prefix and the suffix [4, 8, 16, 32]. nums becomes [1, 2].
            Remove the prefix [1] and the suffix [4, 8, 16, 32]. nums becomes [2].
        For x = 3, there is no possible way to perform the operation.


    --- Example 3 ---
    Input: nums = [1,1,2,1,1], k = 2
    Output: [9,6]


    *** Constraints ***
    1 <= nums[i] <= 10^9
    1 <= nums.length <= 10^5
    1 <= k <= 5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Memoization for "subarrays".

*/

/* Time  Beats: 8.32% */
/* Space Beats: 9.49% */

/* Time  Complexity: O(N * K * K) */ // Since: 1<= k <=5 it's effectively O(N)
/* Space Complexity: O(N * K)     */ // Since: 1<= k <=5 it's effectively O(N)
class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k)
    {
        int N = nums.size();
        vector<long long> result(k, 0);

        // Reduce all numbers modulo k
        for (int& num : nums)
            num %= k;

        // Try to count subsequences for each required mod value
        for (int required_mod = 0; required_mod < k; required_mod++)
        {
            vector<vector<long long>> dp(N, vector<long long>(k + 1, -1));

            result[required_mod] = countSubsequences(0, required_mod, -1, k, nums, dp);
        }

        return result;
    }

private:
    long long countSubsequences(int index, int target_mod, int curr_product_mod, int k, const vector<int>& nums, vector<vector<long long>>& dp)
    {
        if (index == nums.size())
            return 0;

        if (dp[index][curr_product_mod + 1] != -1)
            return dp[index][curr_product_mod + 1];

        long long take = 0;
        long long skip = 0;

        long long count = 0;

        if (curr_product_mod == -1)
        {
            // Start a new subsequence
            if (nums[index] == target_mod)
                count = 1;

            take = count + countSubsequences(index + 1, target_mod, nums[index], k, nums, dp);
            skip =   0   + countSubsequences(index + 1, target_mod,          -1, k, nums, dp);
        }
        else
        {
            // Extend existing subsequence
            int new_product_mod = (curr_product_mod * nums[index]) % k;

            if (new_product_mod == target_mod)
                count = 1;

            take = count + countSubsequences(index + 1, target_mod, new_product_mod, k, nums, dp);
            skip = 0; // No option to skip after starting
        }

        return dp[index][curr_product_mod + 1] = take + skip;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    This one is INFINITELY more difficult for me than the one above.

    Even though I can come up with this one as I did here, it's NOT intuitive
    AT ALL!

*/

/* Time  Beats: 50.84% */
/* Space Beats: 45.15% */

/* Time  Complexity: O(N * K) */ // Since: 1<= k <=5 it's effectively O(N)
/* Space Complexity: O(K)     */ // Since: 1<= k <=5 it's effectively O(1)
class Solution_Tabulation {
public:
    vector<long long> resultArray(vector<int>& nums, int k)
    {
        const int N = nums.size();

        // Reduce each element modulo k
        for (int i = 0; i < N; i++)
            nums[i] %= k;

        vector<long long> last_produced_products (k, 0);
        vector<long long> total_produced_products(k, 0);

        for (int i = 0; i < N; i++)
        {
            int current = nums[i];
            vector<long long> tmp(k, 0);

            // Increment the count for the current number itself
            total_produced_products[current]++;

            // Update temp and total_produced_products based on last_produced_products
            for (int required_mod = 0; required_mod < k; required_mod++)
            {
                int new_product = (required_mod * current) % k;

                tmp[new_product]                     += last_produced_products[required_mod];
                total_produced_products[new_product] += last_produced_products[required_mod];
            }

            // Include the current element as a single product
            tmp[current]++;
            last_produced_products = tmp;
        }

        return total_produced_products;
    }
};
