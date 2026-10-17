/*
    ============
    === HARD ===
    ============

    ==============================================
    4041) Minimum Operations to Form Subset Sum II
    ==============================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer sum.

    In one operation, choose an element with current value x and replace it
    with either 2 * x or floor(x / 2).

    For each element, multiplication and division operations may be performed
    in any order.

    Return the minimum number of operations needed so that some of the
    resulting array has a sum exactly equal to sum. If it is impossible, return
    -1.

    The floor() function returns the integer part of the division.

    ========================================================
    FUNCTION: int minOperations(vector<int>& nums, int sum);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [10,2], sum = 13
    Output: 3
    Explanation:
        Divide nums[0] = 10 once: 10 → 5, costing 1 operation.
        Multiply nums[1] = 2 twice: 2 → 4 → 8, costing 2 operations.
        After these operations, nums = [5, 8]. The subset {5, 8} sums to 13
        using 3 operations in total.


    --- Example 2 ---
    Input: nums = [6,3], sum = 8
    Output: 2
    Explanation:
        Turn nums[1] = 3 into 2 using 2 operations:
            Divide nums[1] to get 1.
            Multiply nums[1] = 1 to get 2.
        After these operations, nums = [6, 2]. The subset {6, 2} sums to 8
        using 2 operations in total.


    --- Example 3 ---
    Input: nums = [2,2], sum = 7
    Output: -1
    Explanation:
        No sequence of operations lets a subset of nums sum to 7, so the answer
        is -1.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 500
    1 <= sum <= 5000

*/

#include <climits>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 45.26% */
/* Space Beats: 97.31% */

/* Time  Complexity: O(N * sum * log(max(nums)) * log(sum)) */
/* Space Complexity: O(N * sum * log(max(nums)) * log(sum)) */
class Solution {
private:
    int memo[101][5001];

public:
    int minOperations(vector<int>& nums, int sum)
    {
        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        int result = solve(0, sum, nums);
        return result == INT_MAX ? -1 : result;
    }

private:
    int solve (int idx, int sum, vector<int>& nums)
    {
        const int N = nums.size();

        if (sum == 0)
            return 0;

        if (idx >= N || sum < 0 || sum > 5000)
            return INT_MAX;

        if (memo[idx][sum] != -1)
            return memo[idx][sum];

        int result = INT_MAX;

        ////////////
        /// Skip ///
        ////////////
        result = min(result, solve(idx+1, sum, nums));



        ////////////
        /// Take ///    (sum - nums[idx]) will be tried twice, but w/e
        ////////////

        int val             = nums[idx];
        int used_operations = 0;
        while (val > 0)
        {
            int subproblem_result = solve(idx+1, sum - val, nums);

            if (subproblem_result != INT_MAX)
                subproblem_result = subproblem_result + used_operations;

            result = min(result, subproblem_result);

            if (val & 1)
            {
                int new_val             = val/2 * 2;
                int new_used_operations = 2 + used_operations;

                // new_val MUST be > 0, since val could've been 1
                //
                // Therefore, we'd be having (1/2 * 2)=0, and then we'd have
                // an INFINITE loop since new_val *= 2 would ALWAYS be 0 and
                // this while-loop would run INFINITELY, thus giving us a TLE
                while (new_val > 0 && new_val <= 5000)
                {
                    int subproblem_result = solve(idx+1, sum - new_val, nums);

                    if (subproblem_result != INT_MAX)
                        subproblem_result = subproblem_result + new_used_operations;

                    result = min(result, subproblem_result);

                    ++new_used_operations;
                    new_val *= 2; // Multiply
                }
            }

            ++used_operations;
            val /= 2; // Divide
        }

        val             = nums[idx];
        used_operations = 0;
        while (val <= 5000)
        {
            int subproblem_result = solve(idx+1, sum - val, nums);

            if (subproblem_result != INT_MAX)
                subproblem_result = subproblem_result + used_operations;

            result = min(result, subproblem_result);

            ++used_operations;
            val *= 2; // Multiply
        }

        return memo[idx][sum] = result;
    }
};
