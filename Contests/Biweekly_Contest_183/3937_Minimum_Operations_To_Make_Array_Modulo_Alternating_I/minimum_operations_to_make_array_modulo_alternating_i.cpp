/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================================
    3937) Minimum Operations To Make Array Modulo Alternating I
    ===========================================================

    ============
    Description:
    ============

    ou are given an integer array nums and an integer k.

    In one operation, you can increase or decrease any element of nums by 1.

    An array is called modulo alternating if there exist two distinct integers
    x and y (0 <= x, y < k) such that:

        For every even index i, nums[i] % k == x
        For every odd index i,  nums[i] % k == y

    Return the minimum number of operations required to make nums modulo
    alternating.

    ======================================================
    FUNCTION: int minOperations(vector<int>& nums, int k);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,4,2,8], k = 3
    Output: 2
    Explanation:
        Let's choose x = 1 for even indices and y = 2 for odd indices.
        Perform the following operations:
            Increment nums[1] = 4 by 1, giving nums = [1, 5, 2, 8].
            Decrement nums[2] = 2 by 1, giving nums = [1, 5, 1, 8].
        Now, for even indices, nums[i] % k = 1, and for odd indices, nums[i] % k = 2.
        Thus, the total number of operations required is 2.

    --- Example 2 ---
    Input: nums = [1,1,1], k = 3
    Output: 1
    Explanation:
        Incrementing nums[1] by 1 gives nums = [1, 2, 1], which satisfies the
        condition with x = 1 and y = 2. Thus, the total number of operations
        required is 1.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 10^9
    2 <= k <= 100

*/

#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Split arrays in two:
        + even_idx_values and
        + odd_idx_values.


    x --> target_remainder

    A --> even_idx_costs
    B --> odd_idx_costs

    For each possible value of x in [0, k), compute:
        A[x] cost of converting all elements in even vector to remainder x
        B[x] cost of converting all elements in odd  vector to remainder x


    Find the best and 2nd best in B:

        For each x in A, if x is also the best of B then use second best of B.

        Minimise A[x] + best_of_B.

*/

class Solution {
public:
    int minOperations(vector<int>& nums, int k)
    {
        const int N = nums.size();

        vector<int> even_idx_values;
        vector<int> odd_idx_values;

        for (int i = 0; i < N; i++)
        {
            if (i & 1)
                odd_idx_values.push_back(nums[i]);
            else
                even_idx_values.push_back(nums[i]);
        }

        vector<long long> even_index_costs(k, 0);
        vector<long long> odd_index_costs(k, 0);

        for (int target_remainder = 0; target_remainder < k; target_remainder++)
        {
            even_index_costs[target_remainder] = calculate_transformation_cost(even_idx_values, target_remainder, k);
            odd_index_costs[target_remainder]  = calculate_transformation_cost(odd_idx_values, target_remainder, k);
        }

        long long minimum_odd_cost        = LLONG_MAX;
        long long second_minimum_odd_cost = LLONG_MAX;

        int minimum_odd_cost_remainder = -1;

        for (int remainder = 0; remainder < k; remainder++)
        {
            if (odd_index_costs[remainder] < minimum_odd_cost)
            {
                second_minimum_odd_cost = minimum_odd_cost;
                minimum_odd_cost        = odd_index_costs[remainder];
                minimum_odd_cost_remainder = remainder;
            }
            else if (odd_index_costs[remainder] < second_minimum_odd_cost)
            {
                second_minimum_odd_cost = odd_index_costs[remainder];
            }
        }

        long long result = LLONG_MAX;

        for (int even_remainder = 0; even_remainder < k; even_remainder++)
        {
            long long best_odd_cost = (even_remainder == minimum_odd_cost_remainder) ? second_minimum_odd_cost : minimum_odd_cost;

            result = min(result, even_index_costs[even_remainder] + best_odd_cost);
        }

        return result;
    }

private:
    long long calculate_transformation_cost(vector<int>& values, int target_remainder, int k)
    {
        long long total_cost = 0;

        for (const int& value : values)
        {
            int current_remainder = value % k;
            int direct_distance   = abs(current_remainder - target_remainder);

            total_cost += min(direct_distance, k - direct_distance);
        }

        return total_cost;
    }
};
